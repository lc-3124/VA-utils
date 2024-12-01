#pragma once
/*
 * copyright lc-3124 release 2024 
 * LICENSE (MIT)
 */

// std
#include <cstdio>
#include <cstring>
#include <iostream>
// sys
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

// 定义不同的光标形状常量
enum CursorShape {
    CURSOR_BLOCK = 0,
    CURSOR_UNDERLINE = 1,
    CURSOR_VERTICAL_BAR = 2

};

class VaTerm
{
    private:
        termios originalAttrs;
        termios currentAttrs;
    public:
        VaTerm() {
            tcgetattr(STDIN_FILENO, &originalAttrs);
            currentAttrs = originalAttrs;
        }

        //释放时会恢复终端设置
        ~VaTerm() {
            tcsetattr(STDIN_FILENO, TCSANOW, &originalAttrs);
        }

        /*
         * 以下的各功能几乎只是对termios等库的封装
         */

        // Clear the entire screen.
        inline static const char* _Clear()
        {
            return "\033[2J";
        }
        inline static void Clear()
        {
            fastOutput("\033[2J");
        }

        // Clear the area from the cursor's position to the end of the line.
        inline static const char* _ClearLine()
        {
            return "\033[K";
        }
        inline static void ClearLine()
        {
            fastOutput("\033[K");
        }
        void getTerminalAttributes() {
            tcgetattr(STDIN_FILENO, &currentAttrs);
        }

        void setTerminalAttributes(const termios &newAttrs) {
            currentAttrs = newAttrs;
            tcsetattr(STDIN_FILENO, TCSANOW, &currentAttrs);
        }

        void enableEcho() {
            currentAttrs.c_lflag |= ECHO;
            tcsetattr(STDIN_FILENO, TCSANOW, &currentAttrs);
        }

        void disableEcho() {
            currentAttrs.c_lflag &= ~ECHO;
            tcsetattr(STDIN_FILENO, TCSANOW, &currentAttrs);
        }

        void enableConsoleBuffering() {
            int flags = fcntl(STDIN_FILENO, F_GETFL);
            fcntl(STDIN_FILENO, F_SETFL, flags & ~O_SYNC);
        }

        void disableConsoleBuffering() {
            int flags = fcntl(STDIN_FILENO, F_GETFL);
            fcntl(STDIN_FILENO, F_SETFL, flags | O_SYNC);
        }

        void getTerminalSize(int &rows, int &cols) {
            struct winsize w;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
            rows = w.ws_row;
            cols = w.ws_col;
        }

        void setCursorPosition(int row, int col) {
            std::cout << "\033[" << row << ";" << col << "H";
        }

        void saveCursorPosition() { std::cout << "\033[s"; }

        void restoreCursorPosition() { std::cout << "\033[u"; }

        inline static void fastOutput(const char *str) {
            write(STDOUT_FILENO, str, strlen(str));
        }

        char nonBufferedGetKey() {
            struct termios oldt, newt;
            char c;
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            read(STDIN_FILENO, &c, 1);
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            return c;
        }

        const char *getTerminalType() { return std::getenv("TERM"); }


        void setLineBuffering(bool enable) {
            if (enable) {
                currentAttrs.c_lflag |= ICANON;
            } else {
                currentAttrs.c_lflag &= ~ICANON;
            }
            tcsetattr(STDIN_FILENO, TCSANOW, &currentAttrs);
        }
        
        //禁止回显，然后阻塞，返回获取到的字符，类似于getch()
        char getCharacter() {
            disableEcho();
            char c = nonBufferedGetKey();
            enableEcho();
            return c;
        }
        
        //判断终端是否支持某一功能 
            bool isTerminalFeatureSupported(const char *feature) {
                const char *termType = getTerminalType();
                if (termType == nullptr) {
                    return false;

                }
                    if (strstr(termType, feature)!= nullptr) {
                        return true;
                    }
                return false;
            }

        // 设置字符输入延迟
        void setCharacterDelay(int milliseconds) {
            termios newAttrs = currentAttrs;
                newAttrs.c_cc[VMIN] = 0;
            newAttrs.c_cc[VTIME] = milliseconds / 100;
            setTerminalAttributes(newAttrs);

        }

        // 获取输入速度
        int getInputSpeed() {
            speed_t speed;
            tcgetattr(STDIN_FILENO, &currentAttrs);
            speed = cfgetospeed(&currentAttrs);
            return static_cast<int>(speed);

        }

        // 设置输入速度
        void setInputSpeed(int speed) {
            termios newAttrs = currentAttrs;
            cfsetospeed(&newAttrs, static_cast<speed_t>(speed));
            cfsetispeed(&newAttrs, static_cast<speed_t>(speed));
            setTerminalAttributes(newAttrs);

        }

        // 设置输出速度
        void setOutputSpeed(int speed) {
            termios newAttrs = currentAttrs;
            cfsetospeed(&newAttrs, static_cast<speed_t>(speed));
            setTerminalAttributes(newAttrs);

        }

        int keyPressed(char &k) {
            struct termios oldt, newt;
            int oldf;
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            oldf = fcntl(STDIN_FILENO, F_GETFL);
            fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

            char c;
            int res = read(STDIN_FILENO, &c, 1);
            if (res > 0) {
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                fcntl(STDIN_FILENO, F_SETFL, oldf);
                k=c;
                return 1;
            } else {
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                fcntl(STDIN_FILENO, F_SETFL, oldf);
                k=static_cast<char>(-1);
                return -0;
            }
        }

        // 函数用于设置光标形状
        void setCursorShape(CursorShape shape) {
            termios newAttrs = currentAttrs;

            // 根据传入的光标形状设置相应的c_cflag值
            switch (shape) {
                case CURSOR_BLOCK:
                    newAttrs.c_cflag &= ~(ECHOCTL);
                    break;
                case CURSOR_UNDERLINE:
                    newAttrs.c_cflag |= (ECHOCTL | ECHOE);
                    break;
                case CURSOR_VERTICAL_BAR:
                    newAttrs.c_cflag |= ECHOCTL;
                    break;
            }
            // 设置新的终端属性
            setTerminalAttributes(newAttrs);
        }
};
