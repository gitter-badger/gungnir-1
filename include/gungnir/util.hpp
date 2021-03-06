#ifndef GUNGNIR_UTIL_HPP
#define GUNGNIR_UTIL_HPP

#include <type_traits>

namespace gungnir {

namespace detail {

// Convenience alias for `std::decay<T>::type`.
template<typename T>
using Decay = typename std::decay<T>::type;

template<typename>
struct HKT_ {
    static const bool value = false;
};

template<template <typename...> class F, typename A, typename... B>
struct HKT_<F<A, B...>> {
    static const bool value = true;

    template<typename C>
    using H = F<C>;

    using L = A;
};

// Type traits that describe a higher-kinded type.
template<typename FA>
using HKT = HKT_<Decay<FA>>;

// Convenience alias for `std::result_of<Fn(Args...)>::type`.
template<typename Fn, typename... Args>
using Ret = typename std::result_of<Fn(Args...)>::type;

// A pack of bools.
template<bool...>
struct BoolPack;

// Convenience alias for `std::is_same<BoolPack<true, V...>, BoolPack<V..., true>>`.
template<bool... V>
using AllTrue = std::is_same<BoolPack<true, V...>, BoolPack<V..., true>>;

}  // namespace detail

// Convenience identity function.
template<typename T>
auto identity(T &&x) -> decltype(std::forward<T>(x))
{
    return std::forward<T>(x);
}

}  // namespace gungnir

#endif  // GUNGNIR_UTIL_HPP
