#pragma once

/* (C) Lc3124 2024
 * LICENSE (MIT)
 *
 * The functions implemented in this file are the basis for VAWK to perform synthesis,
 * plotting, invoking the system, obtaining system and environment information, 
 * and other underlying functions.
 *
 * This file contains the entire functionality of the other modules of the entire Va-untils,
 * but with a lot of modifications on top of that.
 * I consider this file to be a refactoring of Va-unitls 
 */

#include "src/VaCusor.hpp"
#include "src/VaColor.hpp"
#include "src/VaTerm.hpp"
#include "src/VaSystem.hpp"
#include "src/VaUtf.hpp"

class VaTui 
{
    protected:
        /*there are the submodels*/
        VaCursor *Cursor;
        VaColor *Color;
        VaTerm *Term;
        VaSystem *System;
        VaUtf *Utf;
        /*      submodules       */
        inline void submodel_init();
        inline void submodels_del();

    public:
        /*      init VaTui       */
        VaTui(){submodel_init();};
        /*      release VaTui    */
        ~VaTui(){submodels_del();};


};

void VaTui::submodel_init()
{
    Cursor = new VaCursor;
    Color = new VaColor;
    Term = new VaTerm;
    System = new VaSystem;
    Utf = new VaUtf;
}

void VaTui::submodels_del()
{
    delete this->Cursor;
    delete this->Color;
    delete this->Term;
    delete this->System;
    delete this->Utf;
}
