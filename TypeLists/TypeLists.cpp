#include <iostream>
#include <typeinfo>
#include <type_traits>

#include "TypeList.h"

int main()
{
    using lst = tl::TypeList<char, int, float, double, char>;

    std::cout << "Size=" << lst::size() << '\n';
    lst::print();
    std::cout << tl::algo::IndexOf<lst, char>::value << '\n';
    std::cout << tl::algo::IndexOf<lst, int>::value << '\n';
    std::cout << tl::algo::IndexOf<lst, float>::value << '\n';
    std::cout << tl::algo::IndexOf<lst, double>::value << '\n';
    std::cout << tl::algo::RIndexOf<lst, char>::value << '\n';

    return 0;
}
