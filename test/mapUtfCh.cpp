/*
 * 这个程序测试VaUtils获取拼音的方法
 */

#include "VaUtils.hpp"
#include <iostream>

using std::string;

int
    main ()
{
    std::vector<std::string> py;
    std::string              res;
    std::cin >> res;
    VaUtils::Chinese::Char2Pinyin2 ( res, py );

    for ( int i = 0; i < py.size (); i++ )
        {
            std::cout << py.at ( i ) << " ";
        }
    std::cout << "\n";

    return 0;
}
