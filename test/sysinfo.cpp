#include "VaTui.hpp"
#include <iostream>

void print(const char *str) {
    VaTui::Term::fastOutput(str);
    VaTui::Term::fastOutput("\n");
}

int main() {
    print(VaTui::System::getCurrentTime().c_str());
    print(VaTui::System::getDeviceName().c_str());
    print(VaTui::System::getUserName().c_str());
    print(VaTui::System::getHostName().c_str());
    print(VaTui::System::getRunningDirectory().c_str());

    while (true) {
            std::string _input;

        VaTui::Term::fastOutput("(Q:C-c)Index of env: ");

        std::cin >> _input;

        VaTui::Term::fastOutput("Value: ");
        print(VaTui::System::getRunningEnvironment(_input.c_str()).c_str());
    }

    return 0;
}
