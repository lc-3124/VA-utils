#pragma once
/*
 * copyright lc-3124 release 2024 
 * LICENSE (MIT)
 */


// std
#include <cmath>
#include <cstdio>
#include <cstring>
// sys
#include <unistd.h>

/*
 * Enums
 */
namespace color4bit
{
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

enum class AnsiEffect {
    BOLD = 1,     //
    DIM = 2,      //
    ITALIC = 3,   //
    UNDERLINE = 4,//
    BLINK_SLOW = 5,  //
    BLINK_FAST = 6,  //
    REVERSE = 7,  // reverse the front and background's color
    CONCEAL = 8,   //hide the text 
    DELETE = 9    //delete line 
};

/*
 * VaColor class
 */
class VaColor
{
    private:
        inline static void fastOutput(const char *str) {
            write(STDOUT_FILENO, str, strlen(str));
        }
    public:
        /*
         * Functions related to color control.
         */
        // Set the text and background's colors.
        // low bit
        inline static const char* _SetColor4bit(int front, int background)
        {
            static char escapeCommand[64];
            snprintf(escapeCommand, sizeof(escapeCommand), "\033[%dm\033[%dm", front, background);
            return escapeCommand;
        }
        inline static void SetColor4bit(int front, int background)
        {
           fastOutput(_SetColor4bit(front, background));
        }
        //16 bit
        inline static const char* _SetColor256(int front, int background)
        { 
            static char escapecommand[64];
            snprintf(escapecommand, sizeof(escapecommand),"\033[38;5;%dm\033[48;5;%dm",front,background);
            return escapecommand;
        }
        inline static void SetColor256(int front, int background)
        {
            fastOutput(_SetColor256(front, background));
        }

        //full color
        //My console is not supporting RGB,so I don't know if it can work
        inline static const char* _set_background_color_RGB(int R,int B,int G)
        {
            static char escapecommand[64];
            snprintf(escapecommand, sizeof(escapecommand),"\033[48;2;%d,%d,%dm",R,G,B);
            return escapecommand;
        }
        inline static void set_background_color_RGB(int R, int B,int G)
        {
            fastOutput(_set_background_color_RGB(R, B, G));
        }

        inline static const char* _set_front_color_RGB(int R,int B,int G)
        {
            static char escapecommand[64];
            snprintf(escapecommand, sizeof(escapecommand),"\033[38;2;%d,%d,%dm",R,G,B);
            return escapecommand;
        }
        inline static void set_front_color_RGB(int R, int B,int G)
        {
            fastOutput(_set_front_color_RGB(R, G, B));
        }

        /*
         * Functions related to effect cotrol.
         */
        //set the effect of text 
        inline static const char* _SetEffect(short effect ,bool isEnable)
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
        inline void SetEffect(short effect ,bool isEnable)
        {
            fastOutput(_SetEffect(effect,isEnable));
        }
        inline static const char* _ColorEffectReset()
        {
            static char escapecommand[64];
            snprintf(escapecommand,sizeof(escapecommand),"\033[0m");
            return escapecommand;
        }

        /*
         * Other functions 
         */


        //I don't know if it can work ,I will test it
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

};
