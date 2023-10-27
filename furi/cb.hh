#pragma once

namespace furi {
  namespace cb {
    template<class... As> using FnPtr = void(*)(As...);
  }

  template<class... As> struct Cb {
    using FnPtr = cb::FnPtr<void*, As...>;
    
    void* ctx;
    FnPtr fn_ptr;

    Cb(): ctx(nullptr), fn_ptr(nullptr) {}
    Cb(FnPtr fn_ptr): ctx(nullptr), fn_ptr(fn_ptr) {}

    template<class C> Cb(C* ctx, cb::FnPtr<C*, As...> fn_ptr)
      : ctx(static_cast<void*>(ctx))
      , fn_ptr(reinterpret_cast<FnPtr>(fn_ptr))
      {}

    void operator()(As... args) {
      if (fn_ptr) fn_ptr(ctx, args...);
    }
  };

  template<class A1, class... As> struct Cb2 {
    using FnPtr = cb::FnPtr<A1, void*, As...>;

    void* ctx;
    FnPtr fn_ptr;

    Cb2(): ctx(nullptr), fn_ptr(nullptr) {}
    Cb2(FnPtr fn_ptr): ctx(nullptr), fn_ptr(fn_ptr) {}

    template<class C> Cb2(C* ctx, cb::FnPtr<A1, C*, As...> fn_ptr)
      : ctx(static_cast<void*>(ctx))
      , fn_ptr(reinterpret_cast<FnPtr>(fn_ptr))
      {}

    void operator()(A1 a1, As... args) {
      if (fn_ptr) fn_ptr(a1, ctx, args...);
    }
  };

  template<class C> struct Ctx {
    C* ptr;
    Ctx(C* ptr): ptr(ptr) {};

    template<class... As>
    Cb<As...> operator>>(cb::FnPtr<C*, As...> fn_ptr) {
      return { ptr, fn_ptr };
    }

    template<class A1, class... As>
    Cb2<A1, As...> operator>>(cb::FnPtr<A1, C*, As...> fn_ptr) {
      return { ptr, fn_ptr };
    }
  };
}
