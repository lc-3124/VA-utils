#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <string>
#include <sstream>
#include "VaTui.hpp"

class Reader {
private:
    // 运行目录和当前目录的 list
    static std::string rPath;
    static std::string ListDir;
    static int numMaxListFiles;
    static std::vector<std::string> ListDirName;

    // 小说页缓冲
    static int mcol;
    static int mrow;
    static int nMaxPageBytes;
    static std::string* ThePage;
    static std::vector<std::string> NovelBuffer;

    // 小说路径和状态
    static std::string NovelPath;
    static int nMaxPage;
    static int NowPage;

    // 页数存储在...
    static std::string NovelConfigPath;

public:
    // 读取路径
    inline static void readPath() {
        // 获取程序的运行目录
        rPath = VaTui::System::getRunningDirectory();
        // 获取当前目录的文件列表
        ListDir = VaTui::System::getSystemOuput("ls");

        std::stringstream ss(ListDir);
        std::string item;
        // 将文件列表按行存储到 ListDirName 中
        while (std::getline(ss, item)) {
            ListDirName.push_back(item);
        }
        numMaxListFiles = ListDirName.size();
    }

    // 初始化 Tui 相关数据
    inline static void initTui() {
        // 获取终端的行数和列数
        VaTui::Term::getTerminalSize(mrow, mcol);
        //计算页面字节数
        nMaxPageBytes = mrow * mcol;
    }

    // 让用户选择要看的文件
    inline static void ChooseFile() {
        // 将光标移到左上角
        VaTui::Cursor::CursorMoveTo(0, 0);
        // 重置颜色效果
        VaTui::Color::ColorEffectReset();
        // 清除终端屏幕
        VaTui::Term::Clear();

        std::string buf;
        // 构建用户提示信息
        buf += "Press the index key to choose following options!\n";
        for (int i = 0; i < numMaxListFiles; ++i) {
            // 设置颜色为白色前景色和蓝色背景色
            buf += VaTui::Color::_SetColor256(WHITE, BLUE);
            // 显示选项索引（使用字母表示）
            buf.push_back(static_cast<char>(i + static_cast<int>('a')));
            // 重置颜色效果
            buf += VaTui::Color::_ColorEffectReset();
            buf += " : ";
            // 显示文件名称
            buf += ListDirName.at(i);
            buf += "\n";
        }

        // 输出选项信息
        VaTui::Term::fastOutput(buf.c_str());

        // 等待用户输入选项
        char vk = VaTui::Term::nonBufferedGetKey();

        // 重置颜色效果
        VaTui::Color::ColorEffectReset();
        // 清除终端屏幕
        VaTui::Term::Clear();
        // 将输入的字符转换为选项索引
        int cn = vk - 'a';
        std::cout << cn;
        // 检查选项索引是否越界
        if (cn < 0 || cn >= numMaxListFiles) {
            // 抛出异常或进行错误处理，这里使用输出错误信息
            std::cerr << "Choose File index Out of Range" << std::endl;
            return;
        }

        // 构建用户选择的小说路径
        NovelPath = rPath + "/" + ListDirName.at(cn);
        // 构建小说阅读记录的路径
        NovelConfigPath ="." + rPath + "/" + ListDirName.at(cn) + ".VaRdConfig";
    }

    /*
     * 这个模块块还没有完成
     */
    // 将整个小说加载到缓冲中，按照终端大小来分页
    inline static void LoadNovel()
    {
        // 加载文件
        std::ifstream novelFile(NovelPath);
        if (!novelFile) {
            std::cerr << "Failed to open novel file: " << NovelPath << std::endl;
            return;
        }
        char byte;
        NovelBuffer.push_back("");
        int InCnt=0,PgCnt=0; 
         while (novelFile.get(byte)) {
            if(InCnt < nMaxPageBytes) 
            {
                InCnt++;
                NovelBuffer.at(PgCnt)+=byte;
            }
            else
            {
                PgCnt++;
                InCnt=0;
                NovelBuffer.push_back(" ");
                NovelBuffer.at(PgCnt)+=byte;
            } 
    }
         
    }
    /*
     * 这个也没有完成
     */
    inline static void Read()
    {
        while(1)
        {
            VaTui::Term::nonBufferedGetKey();
            VaTui::Term::Clear();
            VaTui::Term::fastOutput(NovelBuffer.at(NowPage).c_str());
            NowPage++;
        }
    }
};

// 静态成员变量的定义
std::string Reader::rPath;
std::string Reader::ListDir;
int Reader::numMaxListFiles;
std::vector<std::string> Reader::ListDirName;
int Reader::nMaxPageBytes;
std::string* Reader::ThePage;
std::vector<std::string> Reader::NovelBuffer;
std::string Reader::NovelPath;
int Reader::nMaxPage;
int Reader::NowPage;
std::string Reader::NovelConfigPath;
int Reader::mcol;
int Reader::mrow;

int main() {
    // 保存终端状态
    VaTui::Term::SaveTerm();
    // 输出程序准备信息
    VaTui::Term::fastOutput("Program is ready for starting\n");

    // 调用函数读取路径
    Reader::readPath();
    // 初始化 Tui 相关数据
    Reader::initTui();
    // 让用户选择文件
    Reader::ChooseFile();
    // 加载小说
    Reader::LoadNovel();
    Reader::Read();
    // 恢复终端状态
    VaTui::Term::RestoreTerm();
    return 0;
}

