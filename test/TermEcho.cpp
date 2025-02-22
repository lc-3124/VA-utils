#include "VaTui.hpp"
#include "iostream"

int
    main ()
{
    VaTui::Term::SaveTerm ();
    VaTui::Term::disableEcho ();
    int a;
    std::cin >> a;
    VaTui::Term::RestoreTerm ();
    std::cin >> a;
}
