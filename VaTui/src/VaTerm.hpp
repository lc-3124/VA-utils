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

        ~VaTerm() {
            tcsetattr(STDIN_FILENO, TCSANOW, &originalAttrs);
        }

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

        bool isTerminalFeatureSupported(const char *feature) {
            // to do
            return 0;
        }

        void setLineBuffering(bool enable) {
            if (enable) {
                currentAttrs.c_lflag |= ICANON;
            } else {
                currentAttrs.c_lflag &= ~ICANON;
            }
            tcsetattr(STDIN_FILENO, TCSANOW, &currentAttrs);
        }

        void setCharacterDelay(int milliseconds) {
            // to do
        }

        int getInputSpeed() {
            // to do
            return 0;
        }

        void setInputSpeed(int speed) {
            // to do
        }

        void setOutputSpeed(int speed) {
            // to do
        }

        char getCharacter() {
            disableEcho();
            char c = nonBufferedGetKey();
            enableEcho();
            return c;
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
};
