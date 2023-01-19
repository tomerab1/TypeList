#pragma once

namespace tl {
    template<typename... Args>
    struct TypeList;

    template<typename T, typename... Args>
    struct TypeList<T, Args...>
    {
        using Head = T;
        using Tail = TypeList<Args...>;

        static constexpr void print()
        {
            std::cout << typeid(Head).name() << ", ";
            Tail::print();
        }

        // +1 for T.
        static constexpr std::size_t size() { return sizeof...(Args) + 1; }
    };

    template<typename Last>
    struct TypeList<Last>
    {
        using Head = Last;
        using Tail = void;

        static constexpr void print() { std::cout << typeid(Head).name() << "\b\b\n"; }
    };
}

#include "TypeListAlogs.inl"