#pragma once

/* (C) 2024 Lc3124
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

#include "VaCusor.hpp"
#include "VaColor.hpp"
#include "VaTerm.hpp"
#include "VaSystem.hpp"
#include "VaUtf.hpp"

class VaTui 
{
    public:
        /*there are the submodels*/
        VaCursor Cursor;
        VaColor Color;
        VaTerm Term;
        VaSystem System;
        VaUtf Utf;
    
    private:
    public:

};
