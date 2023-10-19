#pragma once

#include <memory>

namespace furi {
  namespace own {
    template<class T> using Free = void(&)(T*);
  }

  template<class T, own::Free<T> F> class Own {
    struct _Destroy {
      void operator()(T* ptr) { F(ptr); }
    };

    std::unique_ptr<T, _Destroy> _ptr;

  public:
    Own(): _ptr(nullptr, _Destroy{}) {}
    Own(T* ptr): _ptr(ptr, _Destroy{}) {}

    Own(const Own&) = delete;
    Own(Own&&) = default;

    Own& operator=(const Own&) = delete;
    Own& operator=(Own&&) = default;

    operator T*() { return _ptr.get(); }
    operator const T*() const { return _ptr.get(); }

    T* get_mut() const { return _ptr.get(); }
  };
}
