#pragma once

#include "furi/macros.hh"

namespace furi {
  template<class F> class Defer {
    F _fn;

  public:
    Defer(F &&fn): _fn(fn) {}
    ~Defer() { _fn(); }
  };

  #define defer(code) auto FURI_HH_CONCAT(_defer_, __COUNTER__) = Defer{[&]{ code; }}
}
