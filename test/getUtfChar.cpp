#include "VaTui.hpp"
#include <iostream>

int main()
{
    int index = 5 ;
    std::string res = "frfr你好世界，哈哈哈";

    std::string sav ; 

    std::cout<< VaTui::Utf::getUtf8CharaInString( res , sav , index );
    std::cout<< " " << sav << std::endl;

}
