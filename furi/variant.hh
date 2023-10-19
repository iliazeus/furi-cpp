#pragma once

#include <variant>

namespace furi {
  template<class... Ts> struct match: Ts... { using Ts::operator()...; };
  template<class... Ts> match(Ts...) -> match<Ts...>;

  template<class M, class... Ts> constexpr inline auto operator>>(const std::variant<Ts...> &v, M &&m) {
    return std::visit(m, v);
  }

  template<class M, class... Ts> constexpr inline auto operator>>(std::variant<Ts...> &&v, M &&m) {
    return std::visit(m, v);
  }
}
