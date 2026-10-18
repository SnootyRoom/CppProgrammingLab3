#pragma once

#include <concepts>
#include <type_traits>

namespace lab3
{
    template <typename T> 
    concept Numeric = (std::integral<T> || std::floating_point<T>)
        && !std::is_same_v<T, bool> && !std::is_same_v<T, char>
        && !std::is_same_v<T, signed char> && !std::is_same_v<T, unsigned char>
        && !std::is_same_v<T, wchar_t> && !std::is_same_v<T, char8_t>
        && !std::is_same_v<T, char16_t> && !std::is_same_v<T, char32_t>; 
}