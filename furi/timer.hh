#pragma once

#include <furi.h>

#include "furi/callback.hh"
#include "furi/macros.hh"
#include "furi/own.hh"

namespace furi {
  using Timer = ::FuriTimer;
  using TimerOwn = Own<::FuriTimer, ::furi_timer_free>;

  namespace timer {
    using Callback = ::FuriTimerCallback;
    using PendingCallback = ::FuriTimerPendigCallback;

    using Type = ::FuriTimerType;
    namespace type {
      FURI_HH_ALIAS Once = ::FuriTimerTypeOnce;
      FURI_HH_ALIAS Periodic = ::FuriTimerTypePeriodic;
    }

    FURI_HH_ALIAS alloc = ::furi_timer_alloc;
    FURI_HH_ALIAS free = ::furi_timer_free;
    FURI_HH_ALIAS start = ::furi_timer_start;
    FURI_HH_ALIAS stop = ::furi_timer_stop;
    FURI_HH_ALIAS is_running = ::furi_timer_is_running;
    FURI_HH_ALIAS pending_callback = ::furi_timer_pending_callback;

    inline auto alloc_cb(Type type, Cb<> cb) {
      return alloc(cb.fn_ptr, type, cb.ctx);
    }

    inline auto pending_callback_cb(uint32_t arg, Cb<uint32_t> cb) {
      return pending_callback(cb.fn_ptr, cb.ctx, arg);
    }
  }
}
