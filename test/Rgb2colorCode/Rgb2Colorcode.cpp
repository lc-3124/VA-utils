/*
 * This file is to test if Rgb2Colorcode works well
 */

//include files

//Va
#include "VaColorControl.hpp"
//std
#include <cstring>
#include <iostream>


int main( int argc,char **argv )
{
    std::string br,bg,bb;
    int r=0,g=0,b=0;

    while(1)
    {
        //fill the screen with color
    vacc::clear();
    
    std::cout<<
            vacc::RgbToAnsi256Color(
                (r),
                (g),
                (b)
                );
        //move cursor to 0,0
    vacc::cur_moveto(0,0);
        
        //Input R,G,B
    std::cout<<"input:                <Ctrl + C> to exit\n";
    std::cout<<" R:";std::cin>>br;
    std::cout<<" G:";std::cin>>bg;
    std::cout<<" B:";std::cin>>bb;

        //to avoid segment error
    r=std::stoi(br);
    g=std::stoi(bg);
    b=std::stoi(bb);
        
        //set new color
    vacc::set_color256(
            FRONT_WHITE
            ,
            vacc::RgbToAnsi256Color(
                (r),
                (g),
                (b)
                )
            );
    vaec::cur_moveto(7,7);

}
}

