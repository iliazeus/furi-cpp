#pragma once

namespace furi {
  template<class F> class Defer {
    F _fn;

  public:
    Defer(F &&fn): _fn(fn) {}
    ~Defer() { _fn(); }
  };
}
