#pragma once

#include <furi/core/event_flag.h>

#include "furi/macros.hh"
#include "furi/own.hh"

namespace furi {
  using EventFlag = ::FuriEventFlag;
  using EventFlagOwn = Own<::FuriEventFlag, ::furi_event_flag_free>;

  namespace event_flag {
    FURI_HH_ALIAS alloc = ::furi_event_flag_alloc;
    FURI_HH_ALIAS free = ::furi_event_flag_free;

    FURI_HH_ALIAS set = ::furi_event_flag_set;
    FURI_HH_ALIAS clear = ::furi_event_flag_clear;
    FURI_HH_ALIAS get = ::furi_event_flag_get;
    FURI_HH_ALIAS wait = ::furi_event_flag_wait;

    FURI_HH_ALIAS WaitAny = ::FuriFlagWaitAny;
    FURI_HH_ALIAS WaitAll = ::FuriFlagWaitAll;
    FURI_HH_ALIAS NoClear = ::FuriFlagNoClear;

    FURI_HH_ALIAS Error = ::FuriFlagError;

    namespace error {
      FURI_HH_ALIAS Unknown = ::FuriFlagErrorUnknown;
      FURI_HH_ALIAS Timeout = ::FuriFlagErrorTimeout;
      FURI_HH_ALIAS Resource = ::FuriFlagErrorResource;
      FURI_HH_ALIAS Parameter = ::FuriFlagErrorParameter;
      FURI_HH_ALIAS ISR = ::FuriFlagErrorISR;
    }
  }
}
