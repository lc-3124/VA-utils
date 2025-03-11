/*
 * (c) 2025 Lc3124
 * License (MIT)
 * 这是一个工具类
 *
 */
#ifndef _VAUTILS_HPP_
#define _VAUTILS_HPP_

#include <string>
#include <vector>

/*************************************/
/*     MainModule definitoin         */
/*************************************/

/*
 * 这是一个工具类
 * 包括多个模块
 */
class VaUtils
{
  public:
    class Chinese;
    class File;
};

/*
 * 中文模块包括中文转拼音等:
 *
 * Char2Pinyin()方法
 * 可以将一个string类型的utf编码字符串中的第一个有效序列转换成拼音
 * 当然，非中文的utf字符会返回原字符串;
 * Char2Pinyin2() 第2个版本是将一段文字全部转化成拼音，返回一个
 * vector<vector<string>> 容器
 */
class VaUtils::Chinese
{
  public:
    static bool Char2Pinyin ( const std::string resource,
                              std::string &     Pinying );
    static bool Char2Pinyin2 ( const std::string         resource,
                               std::vector<std::string> &Pinyin );
};

/*
 * 专门处理文件的类
 * 你可以用Va*来创建一个文件对象，对他进行读写
 * 正如其名字，VaFile的派生如VaJsonFile可以让你快捷地读取、创建、改写这一类文件
 *
 * 而FileSys封装了文件系统库，可以方便地执行文件的创建、修改、删除等
 */
class VaUtils::File
{
  public:
    class VaFile;
    class VaEditFile;
    class VaIniFile;
    class VaJsonFile;
    class FileSys;
};

/*************************************/
/*     SubModule definitoin          */
/*************************************/

/*
 * VaFile
 * 使用这个类来创建一个文件对象，来方便地进行读写以及重命名
 *
 * 构造函数用来完成实例化时的基本初始化，有2个重载，允许在构造时就打开文件
 *
 *  使用：
 *  // 先实例化，然后打开文件
 *  VaFile myfile;
 *  myfile.openfile( "resource/demo.txt" );
 *  // 或者同时
 *  VaFile myfile( "resource/demo.txt" )
 *  // 动态读取文件 ,VaFile会自动加载那一行
 *  string str = myfile[10]; 
 *  char ch = myfile[10][0];
 *  // 动态写入文件，VaFile会自动写入那一行
 *  myfile[0] = "hello";
 *  // 释放文件，解除打开状态，释放大多数内存
 *  myfile.releasefile();
 *  
 *
 */
#include <fstream>
class VaUtils::File::VaFile
{
  private:
    std::string              mPath;
    std::string              mFileName;
    std::vector<std::string> line_buffer;
    int                      pos_col, pos_row;

    std::fstream RawFile;

    bool is_static_read;
    bool is_batch_write;

    int max_line;

  public:
    VaFile ();
    VaFile ( std::string Path );
    ~VaFile ();
    void openfile ( std::string Path );
    void reload ();
    void changefile ( std::string Path );
    void releasefile ();
    // 设置是否静态读取文件
    void setLoadAll ( bool isLoadAll );
    // 设置是否批量写入文件
    void setBatchWrite ( bool isBatchWrite );
    // 批量写入，只有setBatchWrite为true时才有意义
    void flushwrite ();
    // 编辑工作模式，就是把上面两个set全都设置为true
    void startEditor ();
    // 设置是否使用多线程线程读取和写入,如果启用，自动设置编辑工作模式
    void setMutiThread ( bool isMutiThread );

    // 重命名文件
    void rename ( std::string Neoname );
    // 复制文件
    void cpnew ( std::string neoPath );
    // 在相同目录下cpnew
    void Copy ( std::string Name );

    // 重载[]用来读取和写入行,由于返回的是string对象的引用
    // ，所以无需代理类来重载[][]
    std::string &operator[] ( int index );
    // 在尾部插入
    void push_back(std::string str);
    // 底部插入一行
    void push_newline(std::string str);

    // 数据接口
    int         posCol ();
    int         posRow ();
    bool        isStaticRead ();
    bool        isBatchWrite ();
    std::string FileName ();
    std::string FilePath ();

    // 异常情况报告
    bool open_ok ();    // 正确打开了文件？
    bool file_empty (); // 文件是空的？
    bool bad_pos ();    // 索引坐标越界？
    bool blocking ();   // 读取、写入进程还没完成任务？强制操作会造成阻塞？
};

class VaUtils::File::VaIniFile : public VaFile
{
};

class VaUtils::File::VaJsonFile : public VaFile
{
};
#endif
