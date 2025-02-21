/*
 *  这个文件包含一个程序
 *
 */
#include <string>
#include <vector>

#include "VaTui.hpp"

const int emptycolor = -1;

namespace FileReader
{
};

class Ui
{
  private:
    int         nMaxHeight, nMaxWidth;
    std::string DisPlayingBuffer;
    int         nDefaultFrontColor, nDefaultBackColor;
    int         nCompletedCharColor, nIncorrentCharColor, nToInputCharColor,
        nHelpTextColor, nZhTextColor;
    int nButtonColor, nButtonTextColor;

    int  nCursorPlace = 0;
    int *a;

  public:
    // 初始化TUI
    inline void
        initTui ()
    {
        /* 设置默认值 */
        nDefaultFrontColor  = color16::WHITE;
        nDefaultBackColor   = color16::BLACK;
        nCompletedCharColor = color16::BRIGHT_BLUE;
        nIncorrentCharColor = color16::BRIGHT_RED;
        nToInputCharColor   = color16::PURPLE;
        nHelpTextColor      = color16::BRIGHT_DEEP_GREEN;
        nZhTextColor        = color16::BRIGHT_PURPLE;
        nButtonColor        = color16::DEEP_GREEN;
        nButtonTextColor    = color16::BRIGHT_WHITE;
        /* 设置终端 */
        VaTui::Term::disableEcho ();       //关闭终端回显
        VaTui::Color::ColorEffectReset (); //重置终端效果
        VaTui::Term::Clear ();             //清除终端
        VaTui::Cursor::CursorHide ();      //隐藏光标
    }
    inline void
        endTui ()
    {
        VaTui::Term::RestoreTerm ();
    }
    // 向显示缓冲写入内容
    inline void
        MovePrint ( int frontcolor, int backcolor, int Ystart, int Xstart,
                    std::string oneline )
    {
        /* 暂时写成这样，之后应该加入转义序列的过滤 */
        if ( frontcolor == emptycolor ) frontcolor = this->nDefaultFrontColor;
        if ( backcolor == emptycolor ) backcolor = this->nDefaultBackColor;
        this->DisPlayingBuffer
            += static_cast<std::string> (
                   VaTui::Color::_SetColor256 ( frontcolor, backcolor ) )
               + static_cast<std::string> (
                   VaTui::Cursor::_CursorMoveTo ( Ystart, Xstart ) );
    }

    inline void
        flush ()
    {
        VaTui::Color::ColorEffectReset ();
        VaTui::Term::Clear ();
        VaTui::Cursor::CursorMoveTo ( 0, 0 );
        VaTui::Term::fastOutput ( this->DisPlayingBuffer.c_str () );
        this->DisPlayingBuffer = "";
        VaTui::Color::ColorEffectReset ();
    }

} Tui;

namespace Mainloop
{
};

int
    main ()
{
    VaTui::Term::SaveTerm (); //保存终端设置
    // 初始化Tui
    Tui.initTui ();
    // #绘制测试#
    Tui.MovePrint ( BRIGHT_WHITE, BLUE, 10, 10, "Hello" );
    Tui.flush ();
    // 退出
    Tui.endTui ();
    VaTui::Term::enableEcho ();
    VaTui::Term::RestoreTerm ();
    VaTui::Term::FlushStdOut ();
}

