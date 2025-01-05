#include <iostream>
#include <string>
#include "VaTui.hpp"

// 函数声明
void test4BitColorMatrix();
void test16BitColorMatrix();
void test256BitColorMatrix();
void testTextEffects();
void displayMenu();

// 测试4位颜色模式下的颜色矩阵
void test4BitColorMatrix() {
    VaTui::Term::Clear();
    std::cout << "4位颜色模式颜色矩阵示例（实际效果需在终端查看）：" << std::endl;
    for (int fg = color4bit::FRONT_BLACK; fg < 8+color4bit::FRONT_BLACK; fg++) {
        for (int bg = color4bit::BACKGROUND_BLACK; bg < 8+color4bit::BACKGROUND_BLACK; bg++) {
            VaTui::Cursor::CursorMoveTo(fg-color4bit::FRONT_BLACK,(bg-color4bit::BACKGROUND_BLACK)*2);
            VaTui::Color::SetColor4bit(fg,bg);
            VaTui::Term::fastOutput("# ");
        }
    }

    //注意，ColorEffectReset方法忘记声明了
    VaTui::Term::fastOutput(VaTui::Color::_ColorEffectReset());

    VaTui::Cursor::CursorMoveTo(17,0);
    VaTui::Term::fastOutput("按任意键继续");
    VaTui::Term::nonBufferedGetKey();
}

// 测试16位颜色模式下的颜色矩阵
void test16BitColorMatrix() {
    VaTui::Term::Clear();
    std::cout << "16位颜色模式颜色矩阵示例（实际效果需在终端查看）：" << std::endl;
    for (int fg = 0; fg < 16; ++fg) {
        for (int bg = 0; bg < 16; ++bg) {
            VaTui::Cursor::CursorMoveTo(fg,bg*2);
            VaTui::Color::SetColor256(fg, bg);
            VaTui::Term::fastOutput("# ");
        }
    }
    //注意，ColorEffectReset方法忘记声明了
    VaTui::Cursor::CursorMoveTo(17,0);
    VaTui::Term::fastOutput(VaTui::Color::_ColorEffectReset());
    VaTui::Term::fastOutput("按任意键继续");
    VaTui::Term::nonBufferedGetKey();
}
int main()
{
  //  test16BitColorMatrix();
  //  VaTui::Term::nonBufferedGetKey();
  //  test4BitColorMatrix();

    VaTui::Term::SaveTerm();
    VaTui::Term::disableEcho();
    std::string a;
    std::cin >> a;
    VaTui::Term::enableEcho();
    VaTui::Term::RestoreTerm();
}
