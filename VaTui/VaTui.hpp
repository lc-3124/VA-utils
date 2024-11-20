/* copyright lc-3124 release 2024
 * LICENSE (MIT)
 *
 * The functions implemented in this file are the basis for VAWK to perform synthesis,
 * plotting, invoking the system, obtaining system and environment information, 
 * and other underlying functions.
 *
 *
 * This file contains the entire functionality of the other modules of the entire Va-untils,
 * but with a lot of modifications on top of that.
 * I consider this file to be a refactoring of Va-unitls 
 */


class VaTui 
{
    public:

        //there are the submodels' declare
        class VaCursor *Cursor;
        class VaColor *Color;
        class VaTerm *Term;
        class VaSystem *System;
        class VaUtf *Utf;

};
