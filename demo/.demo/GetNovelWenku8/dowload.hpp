#define yes true 
#define no false
#define MAX_NOVELLINDEX 9999


#include "config.hpp"
#include "VaTui.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

// TUI数据获取的数据结构,和某个地方完全对应
struct tuigetdata_struct
{
    int tt, lt, mt;
    int ni;
    std::string nu;
    std::string nn, sn, sd;
    int tlt, tat;
    bool fn;
};

class nvdow
{
private:

    // 索引范围
    int lindex = 0;
    int rindex = 0;

    // 重新下载索引列表
    struct redwIndexer_struct
    {
        int index;
        int least_times;
    };
    std::vector<redwIndexer_struct> ReDownloadList;

    // 最大重新下载次数
    int nmax_redownoad = 7;

    // 目标主 url 这样写的前提是摸清楚了网站 sitemap
    std::string main_url = "https://dl2.wenku8.com/txtutf8/";

    // 当前下载索引值
    int indexNow = 0;

    // 本次下载执行完毕后的值
    std::string filename; // 文件名称

    //** 传递给图形接口的值
    // 文件重新下载的次数，剩余的次数，总共的次数
    int try_times, least_times, max_times;
    // 当前下载中的索引编号和 url
    int now_index;
    std::string now_url;
    // 当前获取到的文件和重命名的目标文件和保持目录
    std::string now_name, save_name, save_dir;
    // 下载任务和剩余
    int task_least_times, task_all_times;
    // 当前在下载还是重新下载？
    bool firstOrnot;
    // 本次下载是否成功？
    bool isdownloadOK;
    //**
    // 是否允许Tui线程获取数据
    bool isOpenTuiDataInterface = 0;
    // 接口开关
    void SetTuiDataInterface(bool opnenOrnot);

    /***/

    // 构建器
    void BuildCmd();
    // 文件处理和重命名 
    void ProcessTxt();
    // 处理图形接口数据
    void FlushInterfaceData();

public:

    // 设置主索引范围
    void SetIndexRan(int begin, int end);
    // 切换下载目标
    void ChangeResource(int index);
    // 启动下载当前目标,返回是否成功下载
    bool StartDownload();
    // 遍历主索引全部下载
    void StartAllDownload();
    // 遍历重新下载索引列表下载
    void reStartAllDownload();

    // 刷新 tui 数据
    void FlushTuiData();
    // 申请数据接口，阻塞
    tuigetdata_struct GetTuiData();

};

inline void nvdow::SetIndexRan(int begin, int end)
{
    // 专治乱输入
    if (begin < 0 || end < 0 || begin > end || begin > MAX_NOVELLINDEX || end > MAX_NOVELLINDEX)
    {
        std::cerr << "你应该指定一个你认为可能的范围，哥们" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    // 更新数据
    this->lindex = begin;
    this->rindex = end;
    this->indexNow = lindex;
    this->firstOrnot = true; 
}

inline void nvdow::BuildCmd()
{
    // 按照网站结构来构建
    int part = static_cast<int>(indexNow / 1000);
    this->now_url = "https://dl2.wenku8.com/txtutf8/";
    this->now_url += std::to_string(part) + "/";
    this->now_url += std::to_string(indexNow) + ".txt";
}

inline bool nvdow::StartDownload()
{
    BuildCmd();
    std::string command;
    // wget 指令
    command += "wget -q --no-proxy ";
    // 拼接 url
    command += now_url;

    // 删除现存同名文件
    std::string rm_cmd = "rm -f " + std::to_string(indexNow) + ".txt"; 
    std::system(rm_cmd.c_str());

    // 执行 wget 命令
    int wget_result = std::system(command.c_str());

    // 检查 wget 的返回状态码
    bool wget_return_bool = (wget_result == 0);

    // 测试文件是否真的存在
    std::fstream test;
    test.open(std::to_string(indexNow) + ".txt", std::ios::in); 
    bool file_exists = test.is_open(); 
    test.close();
  if ( wget_return_bool && file_exists )
  {
      ProcessTxt();
  }
    return wget_return_bool && file_exists; 
}

inline void nvdow::ProcessTxt()
{
    // 获取信息
    this->filename = std::to_string(indexNow) + ".txt";
    this->save_dir = "resget/";
    this->save_name = "";

    // **根据下载到的文件处理
    // 只读方式打开文件
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "刚刚文件还在的咧？你别乱动这个目录啊爷爷" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    // 获取文件第三行的小说名称
    std::string tmp_getline3;
    std::getline(file, tmp_getline3);
    std::getline(file, tmp_getline3);
    tmp_getline3 = "";
    std::getline(file, tmp_getline3);

    // 过滤和处理 (linux 不支持带<>()!@等符号的文件）
    std::string tmp_getline3_2;
    for (int i = 1; i < 100; i++)
    {
        if (tmp_getline3[i] == ' ')
        {
            tmp_getline3_2 += "_";
        }
        else if (tmp_getline3[i] == '(' || tmp_getline3[i] == ')')
        {
            tmp_getline3_2 += "_";
        }
        else if (tmp_getline3[i] == '>')
            break;
        else tmp_getline3_2 += tmp_getline3[i];
    }

    // 构建重命名目标文件名称
    this->save_name = tmp_getline3_2 + "_" + std::to_string(indexNow) + ".txt";

    // 重命名文件
    if (std::rename(filename.c_str(), this->save_name.c_str())!= 0)
    {
        std::cerr << "重命名失败了，怎么回事捏?" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // 移动文件位置
    std::string mv_cmd;
    mv_cmd += "mkdir -p " + this->save_dir + " ; "
        + "mv " + this->save_name + " " + this->save_dir + "/" + this->save_name + " ";

    std::system(mv_cmd.c_str());
}

inline void nvdow::ChangeResource(int index)
{
    this->indexNow = index;
}


// StartAllDownload 函数
inline void nvdow::StartAllDownload()
{
    while (true)
    {
        // 判断是否完成了第一次下载
        if (this->indexNow > rindex)
            break;

        // 更新数据
        this->now_index = indexNow;
        // 确认任务进度
        this->task_all_times = rindex - lindex;
        this->task_least_times = rindex - now_index;
        this->firstOrnot = yes;
        this->max_times = nmax_redownoad;

        // 下载 indexNow
        if (!StartDownload())
        {
            this->isdownloadOK = no;
            // 失败则纳入下一次下载
            this->ReDownloadList.push_back(
                {
                    this->indexNow,
                    this->nmax_redownoad
                }
                );
        }
        else
        {
            this->isdownloadOK = yes;
        }

        // 让 Tui 读一次数据
        this->SetTuiDataInterface(yes);

        // 递增索引值
        this->indexNow++;
    }

    // 结束下载
    this->SetTuiDataInterface(yes);
}


inline void nvdow::reStartAllDownload()
{
    for (size_t i = 0; i < ReDownloadList.size(); i++)
    {
        // 尝试重新下载
        this->indexNow = ReDownloadList[i].index;

        if (StartDownload() || ReDownloadList[i].least_times <= 0)
        {
            // 如果下载成功，或者超过次数限制，就移除这个任务
            std::vector<redwIndexer_struct>::iterator it =ReDownloadList.begin() + i ;
            ReDownloadList.erase(it);
        }
        else
        {
            // 下载失败，更新重新下载次数
            ReDownloadList[i].least_times--;
        }
    }
}

inline void nvdow::FlushTuiData()
{
    // 调用处理图形接口数据的函数
    FlushInterfaceData();
}


inline tuigetdata_struct nvdow::GetTuiData()
{
    tuigetdata_struct currentData;
    // 阻塞程序流
    while ( true )
    {
        // 等待开锁
        if (this->isOpenTuiDataInterface == 0)
            continue;

// 人不要吃太饱，否则

 ///*/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**////
 /**/                                                           /**/
 /**/                // Data 赋值,然后返回 //                   /**/
 /**/     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;     /**/
 /**/     ;  currentData.tt   =  this->     try_times     ;     /**/
 /**/     ;  currentData.lt   =  this->    least_times    ;     /**/
 /**/     ;  currentData.mt   =  this->     max_times     ;     /**/
 /**/     ;  currentData.ni   =  this->     now_index     ;     /**/
 /**/     ;  currentData.nu   =  this->      now_url      ;     /**/
 /**/     ;  currentData.nn   =  this->     now_name      ;     /**/
 /**/     ;  currentData.sn   =  this->     save_name     ;     /**/
 /**/     ;  currentData.sd   =  this->     save_dir      ;     /**/
 /**/     ;  currentData.tlt  =  this->  task_least_times ;     /**/
 /**/     ;  currentData.tat  =  this->   task_all_times  ;     /**/
 /**/     ;  currentData.fn   =  this->     firstOrnot    ;     /**/
 /**/     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;     /**/
 /**/                                                           /**/
 ///*/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**////
 
        break;
    }
    return currentData;
}

inline void nvdow::SetTuiDataInterface(bool opnenOrnot)
{
    isOpenTuiDataInterface = opnenOrnot;
}
