#pragma once

/* copyright lc-3124 release 2024
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
    private://暂时没有

        /*there are the submodels*/
    protected:
        VaCursor *Cursor;
        VaColor *Color;
        VaTerm *Term;
        VaSystem *System;
        VaUtf *Utf;

        /*init VaTui*/
    public:
        VaTui(){submodel_init();};
    protected:
        inline void submodel_init();

        /*release VaTui*/
    public:
        ~VaTui(){submodels_del();};
    protected:
        inline void submodels_del();


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
