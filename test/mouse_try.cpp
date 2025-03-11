#include "VaTui.hpp"
#include "unistd.h"
#include <vector>
using Term      = VaTui::Term;
using Color     = VaTui::Color;
using Cursor    = VaTui::Cursor;
using MouseInfo = std::vector<std::string>;

void
    EnableMouse ()
{
    Term::fastOutput ( "\033[?1003h\033[?1015h\033[?1006h" );
}

void
    DisableMouse ()
{
    Term::fastOutput ( "\033[?1003l\033[?1015l\033[?1006l" );
}

// TODO
// Process mouse info with a CsiCode . NOTE: only \033[?1006m mode
MouseInfo
    get_mouse_info ( std::string CsiCode )
{
    MouseInfo info;
    // 针对1006模式的报告相应进行处理

    return info;
}

// 启动原始输入模式 (初始化)
void
    OpenRawMode ()
{
    Term::SaveTerm ();
    Term::disableEcho ();
    Term::setLineBuffering ( false );
}

// 恢复终端设置
void
    RestoreTerm ()
{
    Term::RestoreTerm();
}

// TODO
// 一个周期的键盘数据流读取
std::string listen_kbd_pd()
{
    std::string data;
    return data;
}

// TODO
/* 代替main
 * 轮询读取输入，打包成键盘、鼠标事件
 * 必要的TUI绘制
 */
void mainloop ()
{

}

// MAIN 
int main()
{

}
