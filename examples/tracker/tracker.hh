#pragma once

#include <array>
#include <cstdint>
#include <cmath>
#include <vector>

#include "furi/defer_macro.hh"
#include "furi/event_flag.hh"
#include "furi/hal/speaker.hh"
#include "furi/timer.hh"

using std::array;
using std::vector;

namespace tracker_app::tracker {
  namespace note {
    constexpr float C  (int octave) { return 16.35160f * (1 << octave); }
    constexpr float Cs (int octave) { return 17.32391f * (1 << octave); }
    constexpr float Db (int octave) { return 17.32391f * (1 << octave); }
    constexpr float D  (int octave) { return 18.35405f * (1 << octave); }
    constexpr float Ds (int octave) { return 19.44544f * (1 << octave); }
    constexpr float Eb (int octave) { return 19.44544f * (1 << octave); }
    constexpr float E  (int octave) { return 20.60172f * (1 << octave); }
    constexpr float F  (int octave) { return 21.82676f * (1 << octave); }
    constexpr float Fs (int octave) { return 23.12465f * (1 << octave); }
    constexpr float Gb (int octave) { return 23.12465f * (1 << octave); }
    constexpr float G  (int octave) { return 24.49971f * (1 << octave); }
    constexpr float Gs (int octave) { return 25.95654f * (1 << octave); }
    constexpr float Ab (int octave) { return 25.95654f * (1 << octave); }
    constexpr float A  (int octave) { return 27.50000f * (1 << octave); }
    constexpr float As (int octave) { return 29.13524f * (1 << octave); }
    constexpr float Bb (int octave) { return 29.13524f * (1 << octave); }
    constexpr float B  (int octave) { return 30.86771f * (1 << octave); }
  }

  struct Command {
    float note = note::A(4);
    uint8_t len32 = 32;
    float vol = 0.8f;
  };

  struct Song {
    uint16_t qpm;
    vector<Command> commands;
  };
}

namespace tracker_app {
  using namespace furi;

  class Tracker {
    struct _Flags {
      constexpr static uint32_t IsUnlocked = 1;
      constexpr static uint32_t IsStopped = 2;
    };

    mutable EventFlagOwn _flags = event_flag::alloc();

    TimerOwn _timer = timer::alloc_cb(timer::type::Periodic, {this, _on_tick});

    const tracker::Song *_song = nullptr;

    int _command_index;
    int _command_counter;

  public:
    Tracker() {
      event_flag::set(_flags, _Flags::IsUnlocked | _Flags::IsStopped);
    }

    bool is_playing() const {
      auto flags = event_flag::get(_flags);
      return !(flags & _Flags::IsStopped);
    }

    void play(const tracker::Song &song) {
      using namespace furi::hal;

      event_flag::wait(_flags, _Flags::IsUnlocked, 0, -1);
      defer (event_flag::set(_flags, _Flags::IsUnlocked));

      if (~event_flag::get(_flags) & _Flags::IsStopped) return;
      event_flag::clear(_flags, _Flags::IsStopped);

      _song = &song;
      _command_index = -1;
      _command_counter = -1;

      auto ticks_per_second = kernel::get_tick_frequency();
      auto ticks_per_32nd = (ticks_per_second * 60) / (8 * (uint32_t)song.qpm);
      timer::start(_timer, ticks_per_32nd);

      event_flag::wait(_flags, _Flags::IsStopped, event_flag::NoClear, -1);

      timer::stop(_timer);
      _song = nullptr;
    }

    void stop() {
      event_flag::set(_flags, _Flags::IsStopped);
    }

  private:
    static void _on_tick(Tracker *self) { self->_on_tick(); };
    void _on_tick() {
      using namespace furi::hal;

      if (_command_index < 0) {
        if (!speaker::acquire(0)) return;
      }

      if (_command_index >= (int)_song->commands.size()) {
        speaker::release();
        event_flag::set(_flags, _Flags::IsStopped);
        return;
      }

      if (_command_counter < 0) _command_index += 1;
      const auto& command = _song->commands[_command_index];

      if (_command_counter < 0) {
        speaker::start(command.note, command.vol);
        _command_counter = command.len32;
      } else {
        _command_counter -= 1;
      }
    }
  };
}
