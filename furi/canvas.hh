#pragma once

#include <gui/canvas.h>

#include "furi/macros.hh"

namespace furi {
  using Canvas = ::Canvas;

  namespace canvas {
    using Color = ::Color;
    namespace color {
      FURI_HH_ALIAS White = ::ColorWhite;
      FURI_HH_ALIAS Black = ::ColorBlack;
      FURI_HH_ALIAS Xor = ::ColorXOR;
    }

    using Font = ::Font;
    namespace font {
      FURI_HH_ALIAS Primary = ::FontPrimary;
      FURI_HH_ALIAS Secondary = ::FontSecondary;
      FURI_HH_ALIAS Keyboard = ::FontKeyboard;
      FURI_HH_ALIAS BigNumbers = ::FontBigNumbers;
    }

    using Align = ::Align;
    namespace align {
      FURI_HH_ALIAS Left = ::AlignLeft;
      FURI_HH_ALIAS Right = ::AlignRight;
      FURI_HH_ALIAS Top = ::AlignTop;
      FURI_HH_ALIAS Bottom = ::AlignBottom;
      FURI_HH_ALIAS Center = ::AlignCenter;
    }

    FURI_HH_ALIAS reset = ::canvas_reset;
    FURI_HH_ALIAS commit = ::canvas_commit;

    FURI_HH_ALIAS width = ::canvas_width;
    FURI_HH_ALIAS height = ::canvas_height;

    FURI_HH_ALIAS current_font_height = ::canvas_current_font_height;

    using FontParameters = ::CanvasFontParameters;
    FURI_HH_ALIAS get_font_params = ::canvas_get_font_params;

    FURI_HH_ALIAS clear = ::canvas_clear;

    FURI_HH_ALIAS set_color = ::canvas_set_color;
    FURI_HH_ALIAS set_font_direction = ::canvas_set_font_direction;
    FURI_HH_ALIAS invert_color = ::canvas_invert_color;
    FURI_HH_ALIAS set_font = ::canvas_set_font;

    FURI_HH_ALIAS draw_str_aligned = ::canvas_draw_str_aligned;
  }
}
