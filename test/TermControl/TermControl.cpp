//copy right lc3124 2024
// MIT

/*
 * This file is to test some functios in VaTermControl
 *
 */

//va
#include "VaTermControl.hpp" 
#include "VaColorControl.hpp"
//std
#include "iostream"
#include "cstdio"

//VATC
vatc *myterm = new vatc();


//test disable/enable echo
void test_echo()
{
    printf("now disable the echo , just input something and enter it\n>");

    myterm->disableEcho();

    //once input
    char str[100];
    fgets(str,99,stdin);

    myterm->enableEcho();

    //once print
    vacc::set_color16(_16color::RED,_16color::BLACK);
    printf(str);
    vacc::set_color16(_16color::WHITE,_16color::BLACK);

    //twice input
    printf("now enabled ,just try again\n>");
    vacc::set_color16(_16color::RED,_16color::BLACK);
    fgets(str,99,stdin);

    //twice print
    printf(str);
    vacc::set_color256(_16color::WHITE,_16color::BLACK);
    printf("press any key to continue");
    std::cout<<std::flush;
    myterm->getCharacter();
    printf("\n");
    //clear
    for(int i=0;i<6;i++)
    {
        vacc::cur_move(CUR_UP,1);
        vacc::clear_line();
    }
    fflush(stdout);
}

void output_without_buffering()
{
    myterm->fastOutput("now no use the buffering and outputed this string");
    myterm->getCharacter();
    myterm->fastOutput(vacc::_cur_move(CUR_LEFT,100));
    myterm->fastOutput("                                                    ");
    myterm->fastOutput(vacc::_cur_move(CUR_LEFT,100));
}

int main (int argc ,char **argv )
{
    test_echo();
    output_without_buffering();

    delete myterm;
    return 0;
}
