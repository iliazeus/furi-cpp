#pragma once

#include <cstdio>

#include "furi/defer_macro.hh"
#include "furi/event_queue.hh"
#include "furi/gui.hh"
#include "furi/input.hh"
#include "furi/mutex.hh"
#include "furi/notification.hh"
#include "furi/variant.hh"
#include "furi/view_port.hh"

#include "examples/timer/second_timer.hh"

namespace timer_app {
  using namespace furi;

  namespace event {
    using KeyPressed = input::Event;
    struct SecondPassed {};
    struct TimerFinished {};

    using Queue = EventQueue<KeyPressed, SecondPassed, TimerFinished>;
  }

  class App {
  public:
    static void main() {
      App app;
      app.run();
    }

    void run() {
      _setup();
      _loop();
      _teardown();
    }

  private:
    GuiOwn _gui = gui::open_record();
    ViewPortOwn _vp = view_port::alloc();

    NotificationAppOwn _ntf = notification::open_record();

    MutexOwn _mutex = mutex::alloc(mutex::type::Normal);
    event::Queue _queue;
  
    SecondTimer _timer;

    void _setup() {
      using namespace furi::gui;
      using namespace furi::input;
      using namespace furi::view_port;
      using namespace timer_app::event;

      mutex::acquire(_mutex, -1);
      defer (mutex::release(_mutex));

      _timer.on_second = Ctx{this} >> +[](App *self) {
        self->_queue.put(SecondPassed {});
      };

      _timer.on_finish = Ctx{this} >> +[](App *self) {
        self->_queue.put(TimerFinished {});
      };

      set_draw_callback_cb2(_vp, {this, _draw});
      set_input_callback_cb2(_vp, _queue.put_cb2<input::Event>());

      add_view_port(_gui, _vp, layer::Fullscreen);
    }

    static void _draw(Canvas *cv, App *self) { return self->_draw(cv); }
    void _draw(Canvas *cv) {
      using namespace furi::canvas;
      using namespace furi::canvas::align;

      mutex::acquire(_mutex, -1);
      defer (mutex::release(_mutex));

      char s[8];
      _timer.snprintf(s, sizeof(s));

      clear(cv);
      set_color(cv, color::Black);
      set_font(cv, font::BigNumbers);
      draw_str_aligned(cv, width(cv) / 2, height(cv) / 2, Center, Center, s);
      commit(cv);
    }

    void _loop() {
      using namespace furi::input;
      using namespace furi::input::type;
      using namespace furi::view_port;
      using namespace timer_app::event;

      update(_vp);

      _queue.run(match {
        [&](SecondPassed&) {
          update(_vp);
        },

        [&](TimerFinished&) {
          notification::message(_ntf, &::sequence_double_vibro);
        },

        [&](KeyPressed &e) {
          if (e.type != Press && e.type != Repeat) return;

          mutex::acquire(_mutex, -1);
          defer (mutex::release(_mutex));

          switch (e.key) {
            case key::Back:
              _queue.stop();
              return;

            case key::Ok:
              if (_timer.is_running()) _timer.stop(); else _timer.start();
              break;

            case key::Up:
              _timer.seconds_left += 1;
              break;

            case key::Down:
              if (_timer.seconds_left >= 1) _timer.seconds_left -= 1;
              break;

            case key::Right:
              _timer.seconds_left += 60;
              break;

            case key::Left:
              if (_timer.seconds_left >= 60) _timer.seconds_left -= 60;
              else if (_timer.seconds_left >= 1) _timer.seconds_left = 1;
              break;

            default:
              break;
          }

          update(_vp);
        }
      });
    }

    void _teardown() {
      using namespace furi::gui;

      mutex::acquire(_mutex, -1);
      defer (mutex::release(_mutex));

      remove_view_port(_gui, _vp);
    }
  };
}
