#define MAXMODULE 5
#include "VaTui.hpp"
#include <cstdio>
#include <functional>
/*****全局变量*********/
VaTui *Tui;
int max_row,max_col;
//默认颜色
static const int koriBC = BLACK;
static const int koriFC = WHITE;

/**初始化和结束时的释放操作*/
void init ()
{
    //初始化VaTui
    Tui = new VaTui;
    //获取控制台信息 
    Tui->Term->getTerminalSize(max_row,max_col);
    //关闭光标
    Tui->Cursor->CursorHide();
}

void release()
{
    //显示光标
    Tui->Cursor->CursorShow();
    //设回默认颜色
    Tui->Color->SetColor256(koriFC,koriBC);
    //释放内存，退出程序
    delete Tui;
}

/**** 一些函数声明 ****/
void print(const char *str);
void mvprint(int h,int w,const char *str);
void mvcolorprint(int h,int w,int front,int back,const char *str);//只支持Ansi256色号

/****** 模块声明 ******/
void main_menu();

void output_4bitcolor();
void output_256color();
void output_realcolor();
void trans_RGB256();
void test_text_effect();

/*
 * 主函数
 */
int main()
{
    init();
    main_menu();
    release();
    return 0;
}

/****** 函数实现 *******/
void print(const char * str)
{
    Tui->Color->SetColor256(koriFC,koriBC);
    Tui->Term->fastOutput(str);
}
void mvprint(int h,int w,const char *str)
{
    Tui->Color->SetColor256(koriFC,koriBC);
    Tui->Cursor->CursorMoveTo(h,w);
    Tui->Term->fastOutput(str);
}
void mvcolorprint(int h,int w,int front,int back,const char *str)
{
    Tui->Color->SetColor256(front,back);
    Tui->Cursor->CursorMoveTo(h,w);
    Tui->Term->fastOutput(str);
}

/***** 模块代码 *****/
void main_menu()
{
    using Callback =std::function<void()>; 
    Callback jumpto[5]=
    {
        output_4bitcolor,
        output_256color,
        output_realcolor,
        trans_RGB256,
        test_text_effect
    };

    std::string funclist[5]=
    {
        " void output_4bitcolor()",
        " void output_256color()",
        " void output_realcolor()",
        " void trans_RGB256()" ,
        " void test_text_effect()"
    };
    Tui->Term->Clear();
    int funcptr=0;
    while(1)
    {
        //draw
        
        Tui->Color->_SetColor256(koriFC,koriBC);
        Tui->Term->Clear();
        mvprint(0,0,"choose the module");
        for(int i=0;i<5;i++)
        {
            if(funcptr == i)
            {
                mvcolorprint(i+2,0,RED,koriBC,funclist[i].c_str());
            }
            else mvprint(i+2,0,funclist[i].c_str());
        }

        char vk = Tui->Term->getCharacter();
        if((vk=='o'||vk=='O'))
        {
            if(funcptr != MAXMODULE-1)funcptr++;
        }
        else if((vk=='0'||vk==')'))
        {
            if(funcptr != 0)funcptr--;
        }

        if(vk== 'p' ||vk=='P')
        {
            jumpto[funcptr]();
        }
        if(vk == 'l'||vk=='L')
        {
            break;
        }
    }
}


void output_4bitcolor()
{
    Tui->Color->_SetColor256(koriFC,koriBC);
    Tui->Term->Clear();
    mvprint(0,0,"Now , test the 4 bit color output!");
#define COLOR4BITSTART 30
#define COLOR4BITEND 37
    for(int i=COLOR4BITSTART;i<=COLOR4BITEND;i++)
    {
    for(int j=COLOR4BITSTART+10;j<=COLOR4BITEND+10;j++)
        {
            Tui->Color->SetColor4bit(i,j);
            Tui->Cursor->CursorMoveTo(i+2-30,1+(j-40)*2);
            Tui->Term->fastOutput("##");
        
        }
    }
    
    mvprint(max_row,0,"Press any key to continue");
    Tui->Term->getCharacter();
}

void output_256color()
{
    Tui->Color->_SetColor256(koriFC,koriBC);
    Tui->Term->Clear();
    mvprint(0,0,"Now , test the 256-color-output!");
    mvprint(max_row,0,"Press any key to continue");
    Tui->Term->getCharacter();
    
    mvprint(0,0,"1: 傻逼东西               ");
    

    mvprint(max_row,0,"Press any key to continue");
    Tui->Term->getCharacter();
    
}
void output_realcolor()
{

}
void trans_RGB256()
{

}
void test_text_effect()
{

}
