#include <iostream>
#include "VaTui.hpp"

// 函数声明
void test4BitColorMatrix();
void test16ColorMatrix();
void test256ColorMatrix();
void testTextEffects();
void displayMenu();

// 声明 _ColorEffectReset 函数，根据之前代码中 VaTui::Color 类的结构来补充声明

// 测试4位颜色模式下的颜色矩阵
void test4BitColorMatrix() {
    VaTui::Term::Clear();
    std::cout << "4位颜色模式颜色矩阵示例（实际效果需在终端查看）：" << std::endl;
    for (int fg = color4bit::FRONT_BLACK; fg < 8 + color4bit::FRONT_BLACK; fg++) {
        for (int bg = color4bit::BACKGROUND_BLACK; bg < 8 + color4bit::BACKGROUND_BLACK; bg++) {
            VaTui::Cursor::CursorMoveTo(fg - color4bit::FRONT_BLACK, (bg - color4bit::BACKGROUND_BLACK) * 2);
            VaTui::Color::SetColor4bit(fg, bg);
            VaTui::Term::fastOutput("# ");
        }
    }

    // 调用 _ColorEffectReset 函数来重置颜色效果，这里使用了正确的调用方式
    VaTui::Term::fastOutput(VaTui::Color::_ColorEffectReset());

    VaTui::Cursor::CursorMoveTo(17, 0);
    VaTui::Term::fastOutput("按任意键继续");
    VaTui::Term::nonBufferedGetKey();
}

// 测试16位颜色模式下的颜色矩阵
void test16ColorMatrix() {
    VaTui::Term::Clear();
    std::cout << "16位颜色模式颜色矩阵示例（实际效果需在终端查看）：" << std::endl;
    for (int fg = 0; fg < 16; ++fg) {
        for (int bg = 0; bg < 16; ++bg) {
            VaTui::Cursor::CursorMoveTo(fg, bg * 2);
            VaTui::Color::SetColor256(fg, bg);
            VaTui::Term::fastOutput("# ");
        }
    }
    // 调用 _ColorEffectReset 函数来重置颜色效果
    VaTui::Cursor::CursorMoveTo(17, 0);
    VaTui::Term::fastOutput(VaTui::Color::_ColorEffectReset());
    VaTui::Term::fastOutput("按任意键继续");
    VaTui::Term::nonBufferedGetKey();
}

// 测试256位颜色模式下的颜色矩阵（补充的函数，和前面测试函数逻辑类似，构建256色的颜色矩阵）
void test256ColorMatrix() {
    VaTui::Term::Clear();
    std::cout << "256位颜色模式颜色矩阵示例（实际效果需在终端查看）：" << std::endl;
    for (int fg = 0; fg < 16; ++fg) {
        for (int bg = 0; bg < 16; ++bg) {
            VaTui::Cursor::CursorMoveTo(fg, bg * 3);
            VaTui::Color::SetColor256(fg + 16 * (bg / 8), bg);
            VaTui::Term::fastOutput("# ");
        }
    }
    VaTui::Cursor::CursorMoveTo(17, 0);
    VaTui::Term::fastOutput(VaTui::Color::_ColorEffectReset());
    VaTui::Term::fastOutput("按任意键继续");
    VaTui::Term::nonBufferedGetKey();
}

// 测试文本效果相关功能（这里只是一个占位函数，你可以根据实际 VaTui 中具体文本效果功能来完善）
void testTextEffects() {
    VaTui::Term::Clear();
    std::cout << "文本效果测试示例（待完善具体测试逻辑）" << std::endl;
    // 示例：假设可以设置加粗效果，这里只是示意，需根据实际功能调整
    VaTui::Color::SetEffect(BOLD, true);
    VaTui::Term::fastOutput("这是加粗效果测试文本");
    VaTui::Color::SetEffect(BOLD, false);
    VaTui::Term::fastOutput(VaTui::Color::_ColorEffectReset());
    VaTui::Term::fastOutput("按任意键继续");
    VaTui::Term::nonBufferedGetKey();
}

// 显示菜单函数，用于展示可测试的功能选项（简单文本菜单示例）
void displayMenu() {
    std::cout << "请选择要测试的功能：" << std::endl;
    std::cout << "a. 测试4位颜色模式颜色矩阵" << std::endl;
    std::cout << "s. 测试16位颜色模式颜色矩阵" << std::endl;
    std::cout << "d. 测试256位颜色模式颜色矩阵" << std::endl;
    std::cout << "f. 测试文本效果" << std::endl;
    std::cout << "g. 退出" << std::endl;
}

int main() {
    VaTui::Term::SaveTerm();

    char choice;

    while(1)
    {
        VaTui::Color::_ColorEffectReset();
        VaTui::Cursor::CursorMoveTo(0,0);
        VaTui::Term::Clear(); 
        std::fflush(stdout);
        displayMenu();
        choice = VaTui::Term::nonBufferedGetKey();
        std::fflush(stdout);
        std::cout<<choice;

        switch (choice)
        {
            case 'a':test4BitColorMatrix();break;
            case 's':test16ColorMatrix();break;
            case 'd':test256ColorMatrix();break;
            case 'f':testTextEffects();break;
            case 'g':
                     {
                         VaTui::Term::RestoreTerm();
                         exit(0);
                     }break;
        }
    }
        return 0;
}
