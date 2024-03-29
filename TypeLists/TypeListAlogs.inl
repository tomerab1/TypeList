#pragma once

#include "TypeList.h"

namespace tl { namespace algo {

        template<typename TL, unsigned int idx>
        struct TypeAt;

        template<typename T, typename... Args>
        struct TypeAt<TypeList<T, Args...>, 0>
        {
            using Type = T;
        };

        template<typename T, typename... Args, unsigned int i>
        struct TypeAt<TypeList<T, Args...>, i>
        {
            using Type = typename TypeAt<TypeList<Args...>, i - 1>::Type;
        };

        template<typename TL>
        struct PopFront;

        template<typename Front, typename... Args>
        struct PopFront<TypeList<Front, Args...>>
        {
            using Result = TypeList<Args...>;
        };

        template<typename TL, typename T>
        struct PushBack;

        template<typename T, typename... Args>
        struct PushBack<TypeList<Args...>, T>
        {
            using Result = TypeList<Args..., T>;
        };

        template<typename TL, typename T>
        struct PushFront;

        template<typename T, typename... Args>
        struct PushFront<TypeList<Args...>, T>
        {
            using Result = TypeList<T, Args...>;
        };

        template<typename TL>
        struct Reverse;

        template<typename T, typename... Args>
        struct Reverse<TypeList<T, Args...>>
        {
            using Result = typename PushBack<typename Reverse<typename PopFront<TypeList<T, Args...>>::Result>::Result, T>::Result;
        };

        template<typename T>
        struct Reverse<TypeList<T>>
        {
            using Result = TypeList<T>;
        };

        template<typename TL>
        struct PopBack;

        template<typename T, typename... Args>
        struct PopBack<TypeList<T, Args...>>
        {
        private:
            using reversed = typename Reverse<TypeList<T, Args...>>::Result;
        public:
            using Result = typename Reverse<typename PopFront<reversed>::Result>::Result;
        };

        template<typename TL, typename T>
        struct RemoveType;

        template<typename T>
        struct RemoveType<TypeList<>, T>
        {
            using Result = TypeList<>;
        };

        template<typename T, typename... Args>
        struct RemoveType<TypeList<T, Args...>, T>
        {
            using Result = TypeList<Args...>;
        };

        template<typename T, typename Head, typename... Args>
        struct RemoveType<TypeList<Head, Args...>, T>
        {
            using Result = typename PushFront<typename RemoveType<TypeList<Args...>, T>::Result, Head>::Result;
        };

        template<typename TL, typename T>
        struct RemoveAll;

        template<typename T, typename... Args>
        struct RemoveAll<TypeList<T, Args...>, T>
        {
            using Result = typename RemoveType<TypeList<Args...>, T>::Result;
        };

        template<typename Head, typename T, typename... Args>
        struct RemoveAll<TypeList<Head, Args...>, T>
        {
            using Result = typename PushFront<typename RemoveAll<typename RemoveAll<TypeList<Args...>, T>::Result, T>::Result, Head>::Result;
        };

        template<typename T>
        struct RemoveAll<TypeList<>, T>
        {
            using Result = TypeList<>;
        };

        template<typename TL>
        struct RemoveDuplicates;

        template<>
        struct RemoveDuplicates<TypeList<>>
        {
            using Result = TypeList<>;
        };

        template<typename Head, typename... Args>
        struct RemoveDuplicates<TypeList<Head, Args...>>
        {
        private:
            using L1 = typename RemoveDuplicates<TypeList<Args...>>::Result;
            using L2 = typename RemoveType<L1, Head>::Result;

        public:
            using Result = typename PushFront<L2, Head>::Result;
        };

        template<typename TL, typename T, typename U>
        struct Replace;

        template<typename T, typename U, typename... Args>
        struct Replace<TypeList<T, Args...>, T, U>
        {
        private:
            using L1 = typename PopFront<TypeList<T, Args...>>::Result;
        public:
            using Result = typename PushFront<L1, U>::Result;
        };

        template<typename T, typename U>
        struct Replace<TypeList<>, T, U>
        {
            using Result = TypeList<>;
        };

        template<typename Head, typename T, typename U, typename... Args>
        struct Replace<TypeList<Head, Args...>, T, U>
        {
            using Result = typename PushFront<typename Replace<TypeList<Args...>, T, U>::Result, Head>::Result;
        };

        template<typename TL, typename T, typename U>
        struct ReplaceAll;

        template<typename T, typename U, typename... Args>
        struct ReplaceAll<TypeList<T, Args...>, T, U>
        {
        public:
            using Result = typename Replace<TypeList<U, Args...>, T, U>::Result;
        };

        template<typename T, typename U>
        struct ReplaceAll<TypeList<>, T, U>
        {
            using Result = TypeList<>;
        };

        template<typename Head, typename T, typename U, typename... Args>
        struct ReplaceAll<TypeList<Head, Args...>, T, U>
        {
            using Result = typename PushFront<typename ReplaceAll<typename ReplaceAll<TypeList<Args...>, T, U>::Result, T, U>::Result, Head>::Result;
        };

        template<typename TL1, typename TL2>
        struct CompareLists;

        template<typename T1, typename... Args1, typename T2, typename... Args2>
        struct CompareLists<TypeList<T1, Args1...>, TypeList<T2, Args2...>>
        {
            static constexpr bool value = std::is_same_v<T1, T2> && CompareLists<TypeList<Args1...>, TypeList<Args2...>>::value;
        };

        template<typename... Args>
        struct CompareLists<TypeList<Args...>, TypeList<>>
        {
            static constexpr bool value = false;
        };

        template<typename... Args>
        struct CompareLists<TypeList<>, TypeList<Args...>>
        {
            static constexpr bool value = false;
        };

        template<>
        struct CompareLists<TypeList<>, TypeList<>>
        {
            static constexpr bool value = true;
        };

        template<typename TL, typename T>
        struct IndexOf;

        template<typename Head, typename... Args, typename T>
        struct IndexOf<TypeList<Head, Args...>, T>
        {
            static constexpr std::size_t value = IndexOf<TypeList<Args...>, T>::value + 1;
        };

        template<typename T, typename... Args>
        struct IndexOf<TypeList<T, Args...>, T>
        {
            static constexpr std::size_t value = 0;
        };

        template<typename T>
        struct IndexOf<TypeList<>, T>
        {
            static constexpr std::size_t value = 0;
        };

        template<typename TL, typename T>
        struct RIndexOf
        {
        private:
            using reversed = typename algo::Reverse<TL>::Result;
        public:
            static constexpr std::size_t value = reversed::size() - algo::IndexOf<reversed, T>::value - 1;
        };
} }