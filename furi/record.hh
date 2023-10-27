#pragma once

#include <furi/core/record.h>

#include "furi/macros.hh"
#include "furi/own.hh"

namespace furi::record {
  template<const char* S> inline static void _close(void*) { ::furi_record_close(S); };
  template<const char* S> using RecordOwn = Own<void, _close<S>>;

  FURI_HH_ALIAS open = ::furi_record_open;
  FURI_HH_ALIAS close = ::furi_record_close;
}
