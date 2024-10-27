/*
 * copyright lc3124 release 2024
 * LICENSE (MIT)
 *
 * This file includes a class VaColorControl
 * used to control the ansi color 
 * and other interesting things
 *
 */


#pragma once //avoid re-define

/*include files*/

//C

//std
#include <cmath>

//depened on VA-EC
#include "../../VA-EC/VaEcControl.hpp"

/*
 * VaColorControl
 *
 */
class VaColorControl :public VaEcControl 
{
    private:

    protected:
        
    public:
       /***********************
        * something about     * 
        * ansi 256-color      *
        **********************/

        //turn rgb to 256 color int ansi 
        inline static int RgbToAnsi256Color(int r,int g,int b);
         
        //mix ansi 256 color
        inline static int MixAnsi256Colors(int color1,int color2);
        
        //anit ansi 256 color
        inline static int AntiAnsi256Color(int colorcode);
}
;

typedef VaColorControl vacc;
