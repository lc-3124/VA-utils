#include "VaTui.hpp"

/*
 * 全局变量
 */
VaTui *Tui;
int max_row,max_col;

/*
 * 初始化和结束时的释放操作
 */
void init ()
{
    //初始化VaTui
    Tui = new VaTui;
    //初始化信息 
}

void release()
{
    delete Tui;
    //释放内存，退出程序
}

/**** 一些函数声明 ****/
void mvprint(int h,int w,const char *str);
void mvcolorprint(int h,int w,int front,int back,const char *str);//只支持Ansi256色号

/*
 * 主函数
 */
int main()
{
    init();
    release();
}
