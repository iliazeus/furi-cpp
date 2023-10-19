#pragma once

#include <gui/gui.h>

#include "furi/macros.hh"
#include "furi/own.hh"
#include "furi/record.hh"
#include "furi/view_port.hh"

namespace furi {
  using Gui = ::Gui;

  namespace gui {
    inline Gui* open_record() { return static_cast<Gui*>(record::open(RECORD_GUI)); }
    inline void close_record(Gui*) { return record::close(RECORD_GUI); }

    namespace layer {
      FURI_HH_ALIAS Desktop = ::GuiLayerDesktop;
      FURI_HH_ALIAS Window = ::GuiLayerWindow;
      FURI_HH_ALIAS StatusBarLeft = ::GuiLayerStatusBarLeft;
      FURI_HH_ALIAS StatusBarRight = ::GuiLayerStatusBarRight;
      FURI_HH_ALIAS Fullscreen = ::GuiLayerFullscreen;
    };

    FURI_HH_ALIAS add_view_port = ::gui_add_view_port;
    FURI_HH_ALIAS remove_view_port = ::gui_remove_view_port;
  }

  using GuiOwn = Own<Gui, gui::close_record>;
}
