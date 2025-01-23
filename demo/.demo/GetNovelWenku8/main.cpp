/*
 * 噢，
 * 我想说这是一个用bash写的爬虫，尽管这玩意是用cpp写的 
 * 这听起来很矛盾，
 * 准确来说是利用cpp构建bash指令来执行
 *
 * 这需要系统安装了wget，因为下载相关的操作是wget写的
 * 
 * 这个爬虫程序之前帮我将整个轻小说文库的小说爬了个精光
 * 我使用VaTui来增强这个程序的视觉体验 
 *
 *      .
 *      broad.hpp     与显示相关的类
 *      dowload.hpp   构建wget指令来进行下载的类，以及文件操作也封装于此
 *      config.hpp    宏和变量们
 *
 *          config  被 dowload 包含
 *          dowload 被 broad   包含  
 *          broad   被 main    包含
 */

/* 
 * main.cpp
 * 2025 main.cpp
 *
 * 程序的主函数被包含在这个文件中
 */


#include "broad.hpp"

int main()
{
nvdow nvtask;
nvtask.SetIndexRan(1,10);
nvtask.StartAllDownload();

nvtask.reStartAllDownload();

return 0;
}
