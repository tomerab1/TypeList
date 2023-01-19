#include <iostream>
#include <typeinfo>
#include <type_traits>

#include "TypeList.h"

int main()
{
    using lst = tl::TypeList<char, int, float, double>;
    using newList = tl::algo::PushFront<lst, double>::Result;
    using result = tl::algo::ReplaceAll<newList, double, const char const&>::Result;

    lst::print();
    newList::print();
    result::print();
    

    return 0;
}