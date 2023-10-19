#pragma once

#include <cstdio>

#include "furi.hh"

namespace app {
  using namespace furi;
  using namespace furi::timer;
  using namespace furi::timer::type;

  class SecondTimer {
  public:
    int32_t seconds_left = 0;
    Cb<> on_second;
    Cb<> on_finish;

    SecondTimer() {
      _timer = timer::alloc_cb(
        Periodic,
        Ctx{this} >> +[](SecondTimer *self) { self->_on_tick(); }
      );
    }

    void start() {
      timer::start(_timer, kernel::get_tick_frequency());
    }

    void start(int32_t sec) {
      seconds_left = sec; start();
    }

    void stop() {
      timer::stop(_timer);
    }

    bool is_running() {
      return timer::is_running(_timer);
    }

    auto snprintf(char *buf, size_t n) const {
      return std::snprintf(buf, n, "%02ld:%02ld", seconds_left / 60, seconds_left % 60);
    }

  private:
    TimerOwn _timer;

    void _on_tick() {
      if (seconds_left <= 0) return;

      seconds_left -= 1;
      on_second();

      if (seconds_left <= 0) {
        stop();
        seconds_left = 0;
        on_finish();
      }
    }
  };
}
