#pragma once
/*
 * copyright lc-3124 release 2024 
 * LICENSE (MIT)
 */

// std
#include <cstdio>
#include <cstring>
// sys
#include <unistd.h>

/*
 * Enums
 */
enum
{
    CUR_LEFT = 0,
    CUR_RIGHT = 1, 
    CUR_UP = 3,
    CUR_DOWN = 4
};


/*
 * Functions related to cursor actions.
 */
class VaCursor
{
    private:
       inline static void fastOutput(const char *str) {
            write(STDOUT_FILENO, str, strlen(str));
        }
    public:
        /*
         * Functions related to cursor actions.
         */
        // Move the cursor to the specified position (h, w).
        inline static const char* _CursorMoveTo(int h, int w)
        {
            static char escapeCommand[64];
            snprintf(escapeCommand, sizeof(escapeCommand), "\033[%d;%dH", h, w);
            return escapeCommand;
        }
        inline static void CursorMoveTo(int h, int w)
        {
          fastOutput(_CursorMoveTo(h, w));
        }

        // Move the cursor in a given direction by a specified distance.
        // e.g. cout << _move(LEFT, 10);
        inline static const char* _CursorMove(int dr, int ds)
        {
            static char escapeCommand[64];
            switch (dr)
            {
                case CUR_LEFT:
                    {
                        snprintf(escapeCommand, sizeof(escapeCommand), "\033[%dD", ds);
                        return escapeCommand;
                    }
                case CUR_RIGHT:
                    {
                        snprintf(escapeCommand, sizeof(escapeCommand), "\033[%dC", ds);
                        return escapeCommand;
                    }
                case CUR_UP:
                    {
                        snprintf(escapeCommand, sizeof(escapeCommand), "\033[%dA", ds);
                        return escapeCommand;
                    }
                case CUR_DOWN:
                    {     snprintf(escapeCommand, sizeof(escapeCommand), "\033[%dB", ds);
                        return escapeCommand;
                    }default:
                    return nullptr;
            }
        }
        inline static void CursorMove(int dr, int ds)
        {
          fastOutput(_CursorMove(dr, ds));
        }

        // Reset the cursor to its default position.
        inline static const char* _CursorReset()
        {
            return "\033[H";
        }
        inline static void CursorReset()
        {
          fastOutput("\033[H");
        }

        // Hide the cursor.
        inline static const char* _CursorHide()
        {
            return "\033[?25l";
        }
        inline static void CursorHide()
        {
          fastOutput("\033[?25l");
        }

        // Show the cursor.
        inline static const char* _CurShow()
        {
            return "\033[?25h";
        }
        inline static void CurShow()
        {
          fastOutput("\033[?25h");
        }


};
