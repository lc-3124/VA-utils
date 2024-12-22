#pragma once
/*
 * copyright lc-3124 release 2024 
 * LICENSE (MIT)
 *
 * 这是VaTerm的类声明文件，
 *  具体实现在src中，在VAWK编译时会根据操作系统来决定
 *  让哪些文件参与编译
 *
 * 文件包含一个类，最终实现的功能是类似于unix下termios,terminfo等库的封装
 *
 */


// 定义不同的光标形状常量
enum CursorShape {
    CURSOR_BLOCK = 0,
    CURSOR_UNDERLINE = 1,
    CURSOR_VERTICAL_BAR = 2

};

class VaTerm
{
    private:
    public:
        VaTerm();

        //释放时会恢复终端设置
        ~VaTerm();

        /*
         * 以下的各功能几乎只是输出一些字符
         * 和对termios等库的封装
         */

        // Clear the entire screen.
        inline static const char* _Clear();
        inline static void Clear();

        // Clear the area from the cursor's position to the end of the line.
        inline static const char* _ClearLine();
        inline static void ClearLine();

        void getTerminalAttributes();

        void setTerminalAttributes(const struct termios &newAttrs);

        void enableEcho();

        void disableEcho();

        void enableConsoleBuffering();

        void disableConsoleBuffering();

        void getTerminalSize(int &rows, int &cols);

        void setCursorPosition(int row, int col);

        void saveCursorPosition();

        void restoreCursorPosition();

        inline static void fastOutput(const char *str);

        char nonBufferedGetKey();

        const char *getTerminalType();


        void setLineBuffering(bool enable);

        char getCharacter();
        
        //判断终端是否支持某一功能 
            bool isTerminalFeatureSupported(const char *feature);

        // 设置字符输入延迟
        void setCharacterDelay(int milliseconds);

        // 获取输入速度
        int getInputSpeed();

        // 设置输入速度
        void setInputSpeed(int speed);

        // 设置输出速度
        void setOutputSpeed(int speed);
        
        //无阻塞获取字符，获取到的字符赋值给k,返回是否成功获取字符，失败返回-1,成功返回获取的字符
        int getkeyPressed(char &k);
       
        // 函数用于设置光标形状
        void setCursorShape(CursorShape shape);
};
