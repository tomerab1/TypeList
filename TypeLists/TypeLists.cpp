#include <iostream>
#include <typeinfo>
#include <type_traits>

#include "TypeList.h"

int main()
{
    using lst = tl::TypeList<char, int, float, double>;
    using newList = tl::algo::PushFront<tl::algo::PushBack<lst, int>::Result, double>::Result;
    using result = tl::algo::RemoveDuplicates<newList>::Result;

    lst::print();
    newList::print();
    result::print();
    

    return 0;
}