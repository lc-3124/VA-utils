#include "VaTui.hpp"
#include <unistd.h>

int
    main ()
{
    VaTui::Term::SaveTerm ();
    VaTui::Term::disableEcho ();
    VaTui::Term::fastOutput ( "hello world!" );

    VaTui::Term::fastOutput ( "\033[?1000h" );
    VaTui::Term::fastOutput ( "\033[?1002h" );
    while ( 1 )
        {
            usleep(10);
            char k;
            int  a = VaTui::Term::getkeyPressed ( k );
            if(a != -1)
            VaTui::Term::fastOutput(&k);
             if(k == 'l')break;

             if(k == '\033')break;
        }
    VaTui::Term::RestoreTerm ();
    return 0;
}
