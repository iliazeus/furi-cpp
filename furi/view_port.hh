#pragma once

#include <gui/gui.h>

#include "furi/callback.hh"
#include "furi/canvas.hh"
#include "furi/input.hh"
#include "furi/macros.hh"
#include "furi/own.hh"

namespace furi {
  using ViewPort = ::ViewPort;
  using ViewPortOwn = Own<::ViewPort, ::view_port_free>;

  namespace view_port {
    enum class Orientation {
      Horizontal = ::ViewPortOrientationHorizontal,
      HorizontalFlip = ::ViewPortOrientationHorizontalFlip,
      Vertical = ::ViewPortOrientationVertical,
      VerticalFlip = ::ViewPortOrientationVerticalFlip,
    };

    FURI_HH_ALIAS alloc = ::view_port_alloc;
    FURI_HH_ALIAS free = ::view_port_free;

    using DrawCallback = ::ViewPortDrawCallback;
    using InputCallback = ::ViewPortInputCallback;

    FURI_HH_ALIAS set_draw_callback = ::view_port_draw_callback_set;
    FURI_HH_ALIAS set_input_callback = ::view_port_input_callback_set;

    inline auto set_draw_callback_cb2(ViewPort *vp, Cb2<Canvas*> cb2) {
      return set_draw_callback(vp, cb2.fn_ptr, cb2.ctx);
    }

    inline auto set_input_callback_cb2(ViewPort *vp, Cb2<InputEvent*> cb2) {
      return set_input_callback(vp, cb2.fn_ptr, cb2.ctx);
    }

    FURI_HH_ALIAS update = ::view_port_update;
  }
}
