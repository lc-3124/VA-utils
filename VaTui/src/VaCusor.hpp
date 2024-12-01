#pragma once
/*
 * copyright lc-3124 release 2024 
 * LICENSE (MIT)
 * 本代码片段主要实现了与终端光标操作相关的一系列功能，包括将光标移动到指定位置、按指定方向和距离移动光标、重置光标到默认位置、隐藏和显示光标等操作，旨在方便在终端应用开发中对光标进行灵活控制，以实现更丰富的用户界面交互效果。
 */

// std
#include <cstdio>
#include <cstring>
// sys
#include <unistd.h>

/*
 * Enums
 * 定义了用于表示光标移动方向的枚举类型，通过这些枚举值可以清晰直观地指定光标在终端屏幕上的移动方向，便于后续光标移动相关函数的参数传递和逻辑处理。
 */
enum
{
    CUR_LEFT = 0,    // 表示光标向左移动的方向枚举值。
    CUR_RIGHT = 1,   // 表示光标向右移动的方向枚举值。
    CUR_UP = 3,       // 表示光标向上移动的方向枚举值。
    CUR_DOWN = 4      // 表示光标向下移动的方向枚举值。
};


/*
 * Functions related to cursor actions.
 * VaCursor 类封装了一系列与终端光标操作相关的函数，通过生成和输出 ANSI 转义序列来控制终端光标的位置、显示状态等，为在终端应用中实现自定义的光标行为提供了便捷的方式。
 */
class VaCursor
{
    private:
       // 一个私有静态函数，用于快速将给定的字符串输出到标准输出（STDOUT），借助系统函数 write 实现，主要在类内部其他函数中用于输出 ANSI 转义序列，从而改变终端上光标的相关状态（如位置、显示与否等）。
       inline static void fastOutput(const char *str) {
            write(STDOUT_FILENO, str, strlen(str));
        }
    public:
        /*
         * Functions related to cursor actions.
         * 以下是与光标操作相关的一系列公共函数，提供了不同类型的光标操作功能，例如移动到指定位置、按方向移动以及控制光标显示隐藏等，方便开发者根据具体需求灵活操控终端光标。
         */
        // Move the cursor to the specified position (h, w).
        // 生成用于将光标移动到指定行（h）和列（w）位置的 ANSI 转义序列字符串，并返回该字符串指针。
        // 根据 ANSI 转义序列中设置光标位置的格式要求，使用 snprintf 函数将行和列参数格式化为相应字符串，存储在 escapeCommand 数组中，供后续输出操作使用，以实现将光标定位到指定坐标位置。
        inline static const char* _CursorMoveTo(int h, int w)
        {
            static char escapeCommand[64];
            snprintf(escapeCommand, sizeof(escapeCommand), "\033[%d;%dH", h, w);
            return escapeCommand;
        }
        // 通过调用 fastOutput 函数输出由 _CursorMoveTo 生成的 ANSI 转义序列，从而在终端上实际将光标移动到指定的（h, w）位置。
        inline static void CursorMoveTo(int h, int w)
        {
          fastOutput(_CursorMoveTo(h, w));
        }

        // Move the cursor in a given direction by a specified distance.
        // 根据给定的光标移动方向（dr，通过之前定义的枚举值表示）和移动距离（ds），生成相应的 ANSI 转义序列字符串，返回该字符串指针，用于控制光标按指定方向移动指定的距离。
        // 通过 switch 语句根据不同的移动方向枚举值，按照 ANSI 转义序列中对应方向移动的格式要求，使用 snprintf 函数构造相应字符串存储在 escapeCommand 数组中，供后续输出操作来实现光标移动。例如，对于向左移动（CUR_LEFT），按照向左移动的格式生成相应的转义序列字符串。
        inline static const char* _CursorMove(int dr, int ds)
        {
            static char escapeCommand[64];
            switch (dr)
            {
                case CUR_LEFT:
                    {
                        // 生成向左移动指定距离（ds）的 ANSI 转义序列字符串，格式为 "\033[%dD"，其中 %d 会被实际移动距离替换。
                        snprintf(escapeCommand, sizeof(escapeCommand), "\033[%dD", ds);
                        return escapeCommand;
                    }
                case CUR_RIGHT:
                    {
                        // 生成向右移动指定距离（ds）的 ANSI 转义序列字符串，格式为 "\033[%dC"。
                        snprintf(escapeCommand, sizeof(escapeCommand), "\033[%dC", ds);
                        return escapeCommand;
                    }
                case CUR_UP:
                    {
                        // 生成向上移动指定距离（ds）的 ANSI 转义序列字符串，格式为 "\033[%dA"。
                        snprintf(escapeCommand, sizeof(escapeCommand), "\033[%dA", ds);
                        return escapeCommand;
                    }
                case CUR_DOWN:
                    {
                        // 生成向下移动指定距离（ds）的 ANSI 转义序列字符串，格式为 "\033[%dB"。
                        snprintf(escapeCommand, sizeof(escapeCommand), "\033[%dB", ds);
                        return escapeCommand;
                    }
                default:
                    // 如果传入的移动方向枚举值不合法（不在预定义的方向枚举范围内），则返回 nullptr，表示无法生成有效的移动转义序列。
                    return nullptr;
            }
        }
        // 通过调用 fastOutput 函数输出由 _CursorMove 生成的 ANSI 转义序列，从而在终端上实际控制光标按指定方向移动指定的距离。
        inline static void CursorMove(int dr, int ds)
        {
          fastOutput(_CursorMove(dr, ds));
        }

        // Reset the cursor to its default position.
        // 返回用于将光标重置到默认位置（通常是终端屏幕左上角，即第一行第一列）的 ANSI 转义序列字符串。
        // 该转义序列固定为 "\033[H"，直接返回此字符串指针，供后续输出操作来实现光标位置的重置。
        inline static const char* _CursorReset()
        {
            return "\033[H";
        }
        // 通过调用 fastOutput 函数输出由 _CursorReset 提供的 ANSI 转义序列，从而在终端上实际将光标重置到默认位置。
        inline static void CursorReset()
        {
          fastOutput("\033[H");
        }

        // Hide the cursor.
        // 返回用于隐藏光标的 ANSI 转义序列字符串，该字符串固定为 "\033[?25l"，直接返回此字符串指针，供后续输出操作来实现隐藏光标功能，常用于一些不需要光标显示干扰的场景，比如全屏展示内容时。
        inline static const char* _CursorHide()
        {
            return "\033[?25l";
        }
        // 通过调用 fastOutput 函数输出由 _CursorHide 提供的 ANSI 转义序列，从而在终端上实际隐藏光标。
        inline static void CursorHide()
        {
          fastOutput("\033[?25l");
        }

        // Show the cursor.
        // 返回用于显示光标的 ANSI 转义序列字符串，其固定为 "\033[?25h"，直接返回此字符串指针，供后续输出操作来实现显示光标功能，可在之前隐藏光标的场景结束后，重新显示光标以便正常交互操作。
        inline static const char* _CurShow()
        {
            return "\033[?25h";
        }
        // 通过调用 fastOutput 函数输出由 _CurShow 提供的 ANSI 转义序列，从而在终端上实际显示光标。
        inline static void CurShow()
        {
          fastOutput("\033[?25h");
        }


};

