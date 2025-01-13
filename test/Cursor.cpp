#include "VaTui.hpp"

int main()
{
    
    int mX , mY ;
    VaTui::Term::getTerminalSize(mY,mX);
    VaTui::Color::ColorEffectReset();
    VaTui::Term::Clear();

    VaTui::Cursor::CursorMoveTo(mY-1,0);
    VaTui::Term::fastOutput("\n Press wasd to move away ! Cr-c to exit!");

    VaTui::Term::SaveTerm();

    int cX = 0 , cY = 0;
    VaTui::Cursor::CursorShow();

    bool isInsertMode=0;
    while(1)
    {
        VaTui::Cursor::CursorMoveTo(cY,cX);
        char ch = VaTui::Term::getCharacter();
        
        switch ( ch ) 
        {
            case 'w' : cY--; break;
            case 's' : cY++; break;
            case 'a' : cX--; break;
            case 'd' : cX++; break;
    
        }

    }

    VaTui::Term::RestoreTerm();
     
}
