#pragma once

#include <furi.h>

#include "furi/macros.hh"

namespace furi::kernel {
  FURI_HH_ALIAS get_tick_frequency = ::furi_kernel_get_tick_frequency;
}
