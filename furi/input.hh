#pragma once

#include <input/input.h>

#include "furi/macros.hh"
#include "furi/own.hh"

namespace furi::input {
  namespace type {
    FURI_HH_ALIAS Press = ::InputTypePress;
    FURI_HH_ALIAS Release = ::InputTypeRelease;
    FURI_HH_ALIAS Short = ::InputTypeShort;
    FURI_HH_ALIAS Long = ::InputTypeLong;
    FURI_HH_ALIAS Repeat = ::InputTypeRepeat;

    FURI_HH_ALIAS get_name = ::input_get_type_name;
  }

  namespace key {
    FURI_HH_ALIAS Up = ::InputKeyUp;
    FURI_HH_ALIAS Down = ::InputKeyDown;
    FURI_HH_ALIAS Right = ::InputKeyRight;
    FURI_HH_ALIAS Left = ::InputKeyLeft;
    FURI_HH_ALIAS Ok = ::InputKeyOk;
    FURI_HH_ALIAS Back = ::InputKeyBack;

    FURI_HH_ALIAS get_name = ::input_get_key_name;
  }

  using Event = ::InputEvent;
}
