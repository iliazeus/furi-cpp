#pragma once

#include <variant>

#include "furi/cb.hh"
#include "furi/message_queue.hh"

namespace furi {
  template<class... Ts> class EventQueue {
  public:
    using Event = std::variant<Ts...>;

  private:
    MessageQueueOwn _mq;
    bool _is_running = false;

  public:
    EventQueue(uint32_t capacity = 8)
      : _mq(message_queue::alloc(capacity, sizeof(Event)))
      {}

    template<class T> Cb<T*> put_cb() {
      return Cb{this, +[](EventQueue *self, T* item) { self->put(*item); }};
    }

    template<class T> Cb2<T*> put_cb2() {
      return Cb2{this, +[](T* item, EventQueue *self) { self->put(*item); }};
    }

    template<class T> ::FuriStatus put(const T& item) {
      Event e{item};
      return message_queue::put(_mq, &e, 0);
    }

    template<class T> ::FuriStatus put(T&& item) {
      Event e{item};
      return message_queue::put(_mq, &e, 0);
    }

    template<class V> ::FuriStatus run(V &&v) {
      Event e;
      ::FuriStatus s;

      _is_running = true;

      while (_is_running) {
        s = message_queue::get(_mq, &e, -1);
        if (s) return s;
        std::visit(v, e);
      }

      return ::FuriStatusOk;
    }

    void stop() {
      _is_running = false;
    }
  };
}
