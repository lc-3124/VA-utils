/*
 * This file is to test if colormix works well
 *
 */

/*include files*/
//Va
#include "VaColorControl.hpp"
//std
#include <iostream>
//C
#include <unistd.h>

#define NOCOLOR -1

int main()
{
    int colori;
    int colorj;
    while(1){
    for(colori=17;colori<231;colori++)
    {
        for(colorj=17;colorj<231;colorj++)
        {
            vacc::cur_hide();
            usleep(50000);
            vacc::cur_moveto(0,0);
            vacc::set_color(FRONT_BLACK,BACKGROUND_BLACK);
            vacc::set_color256(
                    colori-6,colori
                    ) ;
            for(int i=0;i<5;i++){
                std::cout<<"             "<<colori<<"\n";            
            }
            vacc::set_color256(
                    colorj-6,colorj
                    ) ;
            for(int i=0;i<5;i++){
                std::cout<<"             "<<vacc::MixAnsi256Colors(colori,colorj)<<"\n";            
            }
            vacc::set_color256(
                    vacc::MixAnsi256Colors(colori,colorj)-6,
                    vacc::MixAnsi256Colors(colori,colorj)
                    ) ;
            for(int i=0;i<5;i++){
                std::cout<<"             "<<colorj<<"\n";            
            }
        }
    }
}
}
