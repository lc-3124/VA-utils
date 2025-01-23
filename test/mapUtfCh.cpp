#include "VaTui.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main()
{
    std::ifstream file;
    file.open("lib.txt");
    // 检查文件是否成功打开
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    std::map<std::string, std::string> CHmap;
    std::string line;
    // 逐行读取文件
    while (std::getline(file, line)) {
        std::string py;
        size_t i = 0;
        // 提取拼音部分
        while (i < line.size() && line[i] != ' ') {
            py += line[i];
            ++i;
        }
        // 跳过空格
        if (i < line.size()) ++i; 

        // 提取汉字部分
        while (i < line.size()) {
            if (VaTui::Utf::isUtf8StartByte(line[i])) {
                std::string ch;
                int byteCount = VaTui::Utf::getUtf8ByteCount(line[i]);
                for (int j = 0; j < byteCount; ++j) {
                    ch += line[i + j];
                }
                CHmap.insert(std::make_pair(ch, py));
                i += byteCount;
            } else {
                ++i;
            }
        }
    }

    while(1)
    {
        std::string a;
        std::cin>>a;
        std::cout<<CHmap[a]<<"\n";
         
    }
    return 0;
}

