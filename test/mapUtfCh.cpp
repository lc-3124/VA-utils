/* 
 * 这个程序测试VaUtils获取拼音的方法
 */

#include "VaUtils.hpp"
#include <iostream>

using std::string ;

int main () 
{
std::vector<std::string> py ;
std::string res;
std::cin>>res ;
VaUtils::Char2Pinyin2( res , py  );
std::cout<< py[3];
   return 0;
}
