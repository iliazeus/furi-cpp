#pragma once

#define FURI_HH_ALIAS constexpr inline const auto&

#define FURI_HH_CONCAT_IMPL(x,y) x##y
#define FURI_HH_CONCAT(x,y) FURI_HH_CONCAT_IMPL(x,y)