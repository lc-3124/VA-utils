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
 *
 */
class VaUtils::File
{
  public:
    class VaFile;
    class VaIniFile;
    class VaJsonFile;
};

/*************************************/
/*     SubModule definitoin          */
/*************************************/

/*
 * VaFile
 */
class VaUtils::File::VaFile
{
  public:
    void a ();
};

class VaUtils::File::VaIniFile : public VaFile
{
};

class VaUtils::File::VaJsonFile : public VaFile
{
};
#endif
