#pragma once

#include "furi/defer.hh"

#define defer(code) auto FURI_HH_CONCAT(_defer_, __COUNTER__) = ::furi::Defer{[&]{ code; }}
