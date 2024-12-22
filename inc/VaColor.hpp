#pragma once
/*
 * (C) Lc3124 2024 
 * LICENSE (MIT)
 * 这段代码主要用于实现终端文本颜色及相关显示效果的控制功能，提供了多种颜色模式（如4位颜色、16位颜色、256色以及RGB颜色模式，尽管RGB模式可能因终端支持情况而异）的操作方法，同时也涵盖了颜色混合、颜色反转以及不同颜色模式之间的转换等功能，旨在方便在终端应用开发中实现丰富多样且灵活的文本颜色呈现效果。
 */


// std
#include <cmath>
#include <cstdio>
#include <cstring>
// sys
#include <unistd.h>

/*
 * Enums
 * 以下定义了不同的枚举类型
 */
namespace color4bit
{
    // 4位颜色模式下的前景色和背景色枚举定义。
    // 这些枚举值对应着 ANSI 转义序列中用于设置前景色和背景色的特定代码，可用于在终端上简单快速地设置文本颜色。
    enum color_4bit 
    {
        FRONT_BLACK = 30,
        FRONT_RED = 31,
        FRONT_GREEN = 32,
        FRONT_YELLOW = 33,
        FRONT_BLUE = 34,
        FRONT_PURPLE = 35,
        FRONT_DEEP_GREEN = 36,
        FRONT_WHITE = 37,
        BACKGROUND_BLACK = 40,
        BACKGROUND_RED = 41,
        BACKGROUND_GREEN = 42,
        BACKGROUND_YELLOW = 43,
        BACKGROUND_BLUE = 44,
        BACKGROUND_PURPLE = 45,
        BACKGROUND_DEEP_GREEN = 46,
        BACKGROUND_WHITE = 47
    };
};

// 16位颜色模式下的颜色枚举定义，涵盖了基本颜色以及对应的亮色版本，同样用于在相应的颜色设置函数中指定具体颜色。
enum color16
{    
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    PURPLE = 5,
    DEEP_GREEN = 6,
    WHITE = 7,
    BRIGHT_BLACK =8,
    BRIGHT_RED =9,
    BRIGHT_GREEN =10,
    BRIGHT_YELLOW =11,
    BRIGHT_BLUE =12,
    BRIGHT_PURPLE =13,
    BRIGHT_DEEP_GREEN =14,
    BRIGHT_WHITE =15
};

// 定义了各种文本显示效果的枚举类型，可用于控制文本的加粗、斜体、下划线、闪烁等特殊显示效果，通过相应的设置函数来启用或禁用这些效果。
enum class AnsiEffect {
    BOLD = 1,     // 加粗效果，使文本显示加粗样式。
    DIM = 2,      // 暗淡效果，让文本看起来颜色变浅、较暗淡（具体效果取决于终端实现）。
    ITALIC = 3,   // 斜体效果，使文本呈现斜体样式（部分终端可能不完全支持）。
    UNDERLINE = 4,// 下划线效果，在文本下方添加下划线。
    BLINK_SLOW = 5,  // 慢速闪烁效果，让文本以较慢频率闪烁（同样依赖终端支持情况）。
    BLINK_FAST = 6,  // 快速闪烁效果，文本闪烁频率比慢速闪烁更快。
    REVERSE = 7,  // 反转效果，用于交换文本的前景色和背景色，实现颜色反转显示。
    CONCEAL = 8,   // 隐藏效果，使文本在终端上不可见（可能有特定触发显示条件，具体依终端而定）。
    DELETE = 9    // 删除行效果，可能会清除文本所在行的内容（不同终端实现可能有差异）。
};

/*
 * VaColor class
 * VaColor 类是用于管理和操作终端文本颜色以及相关显示效果的核心类，
 * 它提供了一系列静态方法来方便地设置文本的颜色、效果等，并且包含了一些用于颜色转换、混合等实用功能的函数 
 * 旨在为终端界面开发中涉及颜色处理的场景提供一站式的解决方案。
 */
class VaColor
{
    private:
        // 一个私有静态函数，用于快速将给定的字符串输出到标准输出（STDOUT），
        // 通过系统函数 write 实现，主要在类内部其他函数中用于输出 ANSI 转义序列等控制字符来改变终端的显示效果。
        inline static void fastOutput(const char *str) {
            write(STDOUT_FILENO, str, strlen(str));
        }
    public:
        /*
         * Functions related to color control.
         * 以下是与颜色控制相关的一系列函数，用于设置文本的前景色、背景色，支持不同的颜色表示模式，方便根据实际需求灵活选择和应用颜色到终端文本显示上。
         */
        // Set the text and background's colors.
        // low bit
        // 生成用于设置4位颜色模式下文本前景色和背景色的 ANSI 转义序列字符串，并返回该字符串指针。
        // 此函数根据传入的前景色和背景色参数，按照 ANSI 转义序列的格式要求，
        // 使用 snprintf 函数将相应代码格式化为字符串存储在 escapeCommand 数组中，供后续输出使用。
        inline static const char* _SetColor4bit(int front, int background)
        {
            static char escapeCommand[64];
            snprintf(escapeCommand, sizeof(escapeCommand), "\033[%dm\033[%dm", front, background);
            return escapeCommand;
        }
        // 通过调用 fastOutput 函数输出由 _SetColor4bit 生成的 ANSI 转义序列，从而在终端上实际设置文本的前景色和背景色为指定的4位颜色模式颜色。
        inline static void SetColor4bit(int front, int background)
        {
            fastOutput(_SetColor4bit(front, background));
        }
        //16 bit
        // 生成用于设置16位颜色模式下文本前景色和背景色的 ANSI 转义序列字符串，返回该字符串指针。
        // 按照 ANSI 转义序列中针对16位颜色模式的特定格式，结合传入的前景色和背景色参数，
        // 使用 snprintf 函数构造相应字符串，存储在 escapecommand 数组中供后续输出到终端来改变颜色显示。
        inline static const char* _SetColor256(int front, int background)
        { 
            static char escapecommand[64];
            snprintf(escapecommand, sizeof(escapecommand),"\033[38;5;%dm\033[48;5;%dm",front,background);
            return escapecommand;
        }
        // 借助 fastOutput 函数输出 _SetColor256 生成的 ANSI 转义序列，实现将终端文本的前景色和背景色设置为指定的16位颜色模式颜色。
        inline static void SetColor256(int front, int background)
        {
            fastOutput(_SetColor256(front, background));
        }

        //full color
        // 生成用于设置全彩色（RGB模式）背景色的 ANSI 转义序列字符串，不过由于作者不确定其所在控制台是否支持 RGB 颜色，所以其实际可用性可能需进一步测试验证。
        // 根据传入的红（R）、绿（G）、蓝（B）三个颜色分量的值（通常范围是0 - 255），
        // 按照 ANSI 转义序列中 RGB 颜色设置的格式要求，
        // 使用 snprintf 函数构造相应字符串并存储在 escapecommand 数组中，返回该数组指针供后续输出操作。
        inline static const char* _set_background_color_RGB(int R,int B,int G)
        {
            static char escapecommand[64];
            snprintf(escapecommand, sizeof(escapecommand),"\033[48;2;%d,%d,%dm",R,G,B);
            return escapecommand;
        }
        // 通过 fastOutput 函数输出由 _set_background_color_RGB 生成的 ANSI 转义序列，尝试在终端上设置背景色为指定的 RGB 颜色，实际效果取决于终端对 RGB 颜色的支持情况。
        inline static void set_background_color_RGB(int R, int B,int G)
        {
            fastOutput(_set_background_color_RGB(R, B, G));
        }

        // 生成用于设置全彩色（RGB模式）前景色的 ANSI 转义序列字符串，同样存在因终端支持情况不确定而需测试其实际可用性的问题。
        // 依据传入的红（R）、绿（G）、蓝（B）三个颜色分量的值，
        // 按照相应的 ANSI 转义序列格式，
        // 使用 snprintf 函数构建字符串并存入 escapecommand 数组，返回该数组指针供后续输出以改变前景色显示。
        inline static const char* _set_front_color_RGB(int R,int B,int G)
        {
            static char escapecommand[64];
            snprintf(escapecommand, sizeof(escapecommand),"\033[38;2;%d,%d,%dm",R,G,B);
            return escapecommand;
        }
        // 利用 fastOutput 函数输出由 _set_front_color_RGB 生成的 ANSI 转义序列，
        // 在终端上设置文本的前景色为指定的 RGB 颜色，其效果依赖终端对 RGB 颜色的支持与否。
        inline static void set_front_color_RGB(int R, int B,int G)
        {
            fastOutput(_set_front_color_RGB(R, G, B));
        }

        /*
         * Functions related to effect cotrol.
         * 以下是与文本显示效果控制相关的函数，用于设置文本的各种特殊显示效果，如加粗、斜体、闪烁等，可根据需要启用或禁用这些效果，增强终端文本显示的丰富性和交互性。
         */
        //set the effect of text 
        // 根据传入的文本显示效果枚举值（effect）以及是否启用该效果的布尔值（isEnable），生成对应的 ANSI 转义序列字符串，返回该字符串指针。
        // 如果 isEnable 为 true，则按照启用效果的 ANSI 转义序列格式，
        // 使用 snprintf 函数构造相应字符串；若为 false，则按照禁用效果的格式构造字符串，存储在 escapecommand 数组中供后续输出使用。
        inline static const char* _SetEffect(short effect,bool isEnable)
        {
            static char escapecommand[64];
            if (isEnable == true){
                snprintf(escapecommand,sizeof(escapecommand),"\033[%dm",effect);
            }
            else {
                snprintf(escapecommand,sizeof(escapecommand),"\033[2%dm",effect);
            }

            return escapecommand;
        }
        // 通过 fastOutput 函数输出由 _SetEffect 生成的 ANSI 转义序列，从而在终端上实际设置文本的显示效果为指定的效果（启用或禁用）。
        inline void SetEffect(short effect,bool isEnable)
        {
            fastOutput(_SetEffect(effect, isEnable));
        }
        // 生成用于重置文本颜色和所有显示效果的 ANSI 转义序列字符串，返回该字符串指针，以便后续可通过输出此序列将文本显示恢复到默认状态（无特殊颜色和效果）。
        inline static const char* _ColorEffectReset()
        {
            static char escapecommand[64];
            snprintf(escapecommand,sizeof(escapecommand),"\033[0m");
            return escapecommand;
        }

        /*
         * Other functions 
         * 以下是一些其他的实用颜色处理相关函数，包括颜色模式之间的转换、颜色混合以及颜色反转等功能，
         * 为更复杂的颜色操作需求提供支持，方便在不同颜色应用场景中进行灵活的颜色调整和处理。
         */


        // 将给定的 RGB 颜色值（r、g、b，范围通常是0 - 255）转换为对应的 ANSI 256 色模式下的颜色代码,
        // 不确定此函数在实际使用中的效果，后续会进行测试验证。
        // 首先计算颜色的灰度值，然后根据颜色是否为灰度（即 r、g、b 相等）以及灰度值范围，
        // 按照特定的算法来确定对应的 ANSI 256 色代码，返回该代码值。
        int RgbToAnsi256Color( int r,int g,int b )
        {
            int gray = 0.299 * r + 0.587 * g + 0.114 * b;
            if (r == g && g == b) {
                if (gray < 8) return 16;
                if (gray > 248) return 231;
                return std::round((gray - 8) / 247.0 * 24) + 232;
            } else {
                int ansiR = std::round((double)r / 51.0);
                int ansiG = std::round((double)g / 51.0);
                int ansiB = std::round((double)b / 51.0);
                return 16 + (ansiR * 36) + (ansiG * 6) + ansiB;
            }
        }

        /*这个函数不是我写的，我也不知道这玩意能不能正常工作，我会测试它的*/
        //将Ansi的256色转换成RGB颜色的三个分量( r , g , b ) 
        void Ansi256ColorToRGB(int ansi256Color, int& r, int& g, int& b)
        {
            if (ansi256Color >= 0 && ansi256Color <= 15) {
                // 处理前16个基本颜色（0 - 15），对应特定的固定RGB值
                switch (ansi256Color) {
                    case 0:  // 黑色
                        r = 0;
                        g = 0;
                        b = 0;
                        break;
                    case 1:  // 红色
                        r = 170;
                        g = 0;
                        b = 0;
                        break;
                    case 2:  // 绿色
                        r = 0;
                        g = 170;
                        b = 0;
                        break;
                    case 3:  // 黄色
                        r = 170;
                        g = 170;
                        b = 0;
                        break;
                    case 4:  // 蓝色
                        r = 0;
                        g = 0;
                        b = 170;
                        break;
                    case 5:  // 紫色
                        r = 170;
                        g = 0;
                        b = 170;
                        break;
                    case 6:  // 深绿色（青色）
                        r = 0;
                        g = 170;
                        b = 170;
                        break;
                    case 7:  // 白色
                        r = 170;
                        g = 170;
                        b = 170;
                        break;
                    case 8:  // 亮黑色（灰色）
                        r = 85;
                        g = 85;
                        b = 85;
                        break;
                    case 9:  // 亮红色
                        r = 255;
                        g = 85;
                        b = 85;
                        break;
                    case 10:  // 亮绿色
                        r = 85;
                        g = 255;
                        b = 85;
                        break;
                    case 11:  // 亮黄色
                        r = 255;
                        g = 255;
                        b = 85;
                        break;
                    case 12:  // 亮蓝色
                        r = 85;
                        g = 85;
                        b = 255;
                        break;
                    case 13:  // 亮紫色
                        r = 255;
                        g = 85;
                        b = 255;
                        break;
                    case 14:  // 亮深绿色（亮青色）
                        r = 85;
                        g = 255;
                        b = 255;
                        break;
                    case 15:  // 亮白色
                        r = 255;
                        g = 255;
                        b = 255;
                        break;
                }
            } else if (ansi256Color >= 16 && ansi256Color <= 231) {
                // 处理 16 - 231 的颜色，通过特定算法从颜色代码计算RGB分量
                int index = ansi256Color - 16;
                r = (index / 36) * 51;
                index %= 36;
                g = (index / 6) * 51;
                b = (index % 6) * 51;
            } else if (ansi256Color >= 232 && ansi256Color <= 255) {
                // 处理 232 - 255 的灰度颜色，根据代码计算灰度对应的RGB值
                int gray = 8 + (ansi256Color - 232) * 10;
                r = gray;
                g = gray;
                b = gray;
            }
        } 
        
        //混合两个Ansi256色，返回混合的结果
        int MixAnsi256Colors( int color1,int color2 )
        {
            int r1, g1, b1, r2, g2, b2;
            if (color1 >= 16 && color1 <= 231) {
                int index = color1 - 16;
                r1 = index / 36;
                index %= 36;
                g1 = index / 6;
                b1 = index % 6;
                r1 *= 51;
                g1 *= 51;
                b1 *= 51;
            } else if (color1 >= 232 && color1 <= 255) {
                int gray = ((color1 - 232) * 247 / 24) + 8;
                r1 = g1 = b1 = gray;
            }

            if (color2 >= 16 && color2 <= 231) {
                int index = color2 - 16;
                r2 = index / 36;
                index %= 36;
                g2 = index / 6;
                b2 = index % 6;
                r2 *= 51;
                g2 *= 51;
                b2 *= 51;
            } else if (color2 >= 232 && color2 <= 255) {
                int gray = ((color2 - 232) * 247 / 24) + 8;
                r2 = g2 = b2 = gray;
            }

            int r = (r1 + r2) / 2;
            int g = (g1 + g2) / 2;
            int b = (b1 + b2) / 2;

            return RgbToAnsi256Color(r, g, b);
        }

        //将Ansi256色色号反色处理，返回反色结果
        int AntiAnsi256Color(int colorcode)
        {
            int color1 =colorcode;
            int r1, g1, b1;
            if (color1 >= 16 && color1 <= 231) {
                int index = color1 - 16;
                r1 = index / 36;
                index %= 36;
                g1 = index / 6;
                b1 = index % 6;
                r1 *= 51;
                g1 *= 51;
                b1 *= 51;
            } else if (color1 >= 232 && color1 <= 255) {
                int gray = ((color1 - 232) * 247 / 24) + 8;
                r1 = g1 = b1 = gray;
            }
            int r = 250 - r1;
            int g = 250 - g1;
            int b = 250 - b1;

            return RgbToAnsi256Color(r, g, b);
        }

        // 将 ANSI 16 色转换为 ANSI 256 色的函数
        int Ansi16ColorToAnsi256(int ansi16Color)
        {
            if (ansi16Color >= 0 && ansi16Color <= 7) {
                return ansi16Color + 16;  // 前8个基本颜色对应到 256 色中的前16个颜色里，索引偏移16
            } else if (ansi16Color >= 8 && ansi16Color <= 15) {
                return ansi16Color + 232 - 8;  // 后8个亮色对应到 256 色中的特定范围，进行相应索引转换
            }
            return 0;  // 如果传入的 16 色代码不符合规范，返回默认值（这里返回0，可根据实际情况调整）
        }

        // 将 ANSI 256 色转换为 ANSI 16 色的函数
        int Ansi256ColorToAnsi16(int ansi256Color)
        {
            if (ansi256Color >= 16 && ansi256Color <= 231) {
                // 256 色中的前 216 种颜色转换到 16 色中的前 8 种基本色的逻辑
                int index = ansi256Color - 16;
                int r = index / 36;
                index %= 36;
                int g = index / 6;
                int b = index % 6;
                if (r == g && g == b) {
                    return r;
                }
                return 8;  // 如果不是单一颜色，对应到 16 色中的亮黑色（这里简单对应，可根据需求调整更合适的逻辑）
            } else if (ansi256Color >= 232 && ansi256Color <= 255) {
                // 256 色中的灰度范围颜色对应到 16 色中的后 8 种亮色的逻辑
                return (ansi256Color - 232 + 8);
            }
            return 0;  // 如果传入的 256 色代码不符合规范，返回默认值（这里返回0，可根据实际情况调整）
        }
};
