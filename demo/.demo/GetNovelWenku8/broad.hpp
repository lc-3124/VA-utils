#include "dowload.hpp"
#include "VaTui.hpp"
#include <thread>
#include <unistd.h> // 妈的，我得把usleep加到VaTui才行

class nvbroad
{
    private:
        tuigetdata_struct nvdow_data;

        // 一个下载器实例
        nvdow nvdow_ins;

        // 关于输出绘制
        void mvprint_color(int frontcolor , int backcolor , const char *string);
        void flush_diasplay();
        std::string displaybuffer;
        void cleardisplaybuffer();

        // 主动申请数据
        void getNvdowData();

        // 
    public:
        // 设置下载参数
        void NvdowConfig();
        // 启动绘图线程和下载线程
        void RunNovelReader(); 
};
