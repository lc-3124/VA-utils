/*This file is a part of src of VaTui*/ 

#pragma once 
#include "VaTui.hpp"

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
