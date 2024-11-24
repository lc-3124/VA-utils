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

#include "declare/VaCusor.hpp"
#include "declare/VaColor.hpp"
#include "declare/VaTerm.hpp"
#include "declare/VaSystem.hpp"
#include "declare/VaUtf.hpp"

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
        void submodel_init();

        /*release VaTui*/
    public:
        ~VaTui(){submodels_del();};
    protected:
        void submodels_del();


};

