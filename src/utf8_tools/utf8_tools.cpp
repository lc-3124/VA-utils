#include <iostream>
#include <iomanip>
#include <string>

// 判断一个字节是否是 UTF-8 编码的多字节序列的一部分
bool isContinuationByte(char byte) {
    return (byte & 0xC0) == 0x80;
}

// 计算一个 UTF-8 编码字符的屏幕宽度
int utf8CharScreenWidth(char byte) {
    if ((byte & 0x80) == 0x00) {
        // ASCII 字符，占一个屏幕宽度
        return 1;
    } else {
        int width = 0;
        while ((byte & 0x80)!= 0x00) {
            byte <<= 1;
            width++;
        }
        return width > 1? 2 : 1;
    }
}

// 计算一个 UTF-8 编码字符的内存宽度并输出字符信息
void processChar(const std::string& str, size_t& index) {
    if ((str[index] & 0x80) == 0x00) {
        // ASCII 字符
        std::cout << "字符: " << str[index] << ", 内存宽度: 1 字节, 屏幕宽度: 1" << std::endl;
        index++;
    } else {
        int charMemoryWidth = 0;
        while (index < str.length() &&!isContinuationByte(str[index])) {
            index++;
            charMemoryWidth++;
        }
        int charScreenWidth = utf8CharScreenWidth(str[index - 1]);
        std::cout << "字符: " << str.substr(index - charMemoryWidth, charMemoryWidth) << ", 内存宽度: " << charMemoryWidth << " 字节, 屏幕宽度: " << charScreenWidth << std::endl;
        index += charMemoryWidth - 1;
    }
}

int main() {
    std::string str = "这是一段包含中文和英文的 UTF-8 字符串。";
    size_t index = 0;
    while (index < str.length()) {
        processChar(str, index);
    }
    return 0;
}
