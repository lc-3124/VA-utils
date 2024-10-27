#include "VaColorControl.hpp"

//I don't know if it can work ,I will test it
int VaColorControl::RgbToAnsi256Color( int r,int g,int b )
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

int VaColorControl::MixAnsi256Colors( int color1,int color2 )
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

int VaColorControl::AntiAnsi256Color(int colorcode)
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

