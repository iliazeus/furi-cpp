#pragma once

#include <furi_hal_speaker.h>

#include "furi/macros.hh"

namespace furi::hal::speaker {
  FURI_HH_ALIAS init = ::furi_hal_speaker_init;
  FURI_HH_ALIAS deinit = ::furi_hal_speaker_deinit;

  FURI_HH_ALIAS acquire = ::furi_hal_speaker_acquire;
  FURI_HH_ALIAS release = ::furi_hal_speaker_release;
  FURI_HH_ALIAS is_mine = ::furi_hal_speaker_is_mine;

  FURI_HH_ALIAS start = ::furi_hal_speaker_start;
  FURI_HH_ALIAS set_volume = ::furi_hal_speaker_set_volume;
  FURI_HH_ALIAS stop = ::furi_hal_speaker_stop;
}
