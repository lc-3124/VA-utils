#pragma once
/*
 * copyright lc-3124 release 2024 
 * LICENSE (MIT)
 */

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <codecvt>
#include <locale>

class VaUtf
{

//get the width of a UTF character 
size_t getUtf8CharWidth(const char* s) {
    if (!s ||!*s) return 0;
    unsigned char c = static_cast<unsigned char>(*s);
    if (c < 0x80) return 1;
    else if ((c & 0xE0) == 0xC0) return 2;
    else if ((c & 0xF0) == 0xE0) return 3;
    else if ((c & 0xF8) == 0xF0) return 4;
    else return 0;

}

// recognize a ASCII character 
bool isAscii(char c) {
    return (c & 0x80) == 0;

}

// 判断是否为 UTF-8 多字节序列的开头字节
bool isUtf8StartByte(char c) {
    return (c & 0xC0)!= 0x80 && (c & 0xF0)!= 0xF8 && (c & 0xFE)!= 0xFC;

}

// 判断是否为 UTF-8 编码字符
bool isUtf8Char(const char* bytes, int len) {
    if (len <= 0) return false;
    char firstByte = bytes[0];
    if (isAscii(firstByte)) return true;
    if (isUtf8StartByte(firstByte)) {
	int numBytes;
	if ((firstByte & 0xE0) == 0xC0) numBytes = 2;
	else if ((firstByte & 0xF0) == 0xE0) numBytes = 3;
	else if ((firstByte & 0xF8) == 0xF0) numBytes = 4;
	else return false;
	return len == numBytes;

    }
    return false;

}

// 判断是否为 GBK 编码字符（简单判断，假设连续两个字节都在 GBK 编码范围内）
bool isGbkChar(const char* bytes, int len) {
    if (len!= 2) return false;
    unsigned char firstByte = static_cast<unsigned char>(bytes[0]);
    unsigned char secondByte = static_cast<unsigned char>(bytes[1]);
    return ((firstByte >= 0x81 && firstByte <= 0xFE) && (secondByte >= 0x40 && secondByte <= 0xFE && secondByte!= 0x7F));

}


};
