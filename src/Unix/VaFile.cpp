/*
 * (c) 2025 Lc3124
 * Achievement of class VaFile
 */
#include "VaTui.hpp"
#include "VaUtils.hpp"


// 构造和一些无足轻重的初始化
VaUtils::File::VaFile::VaFile ()
{
    this->pos_col        = 0;
    this->pos_row        = 0;
    this->is_static_read = 0;
    this->is_batch_write = 0;
    this->max_line       = 0;
    this->mPath          = "";
    this->mFileName      = "";
}

VaUtils::File::VaFile::VaFile ( std::string Path )
{
    this->pos_col        = 0;
    this->pos_row        = 0;
    this->is_static_read = 0;
    this->is_batch_write = 0;
    this->max_line       = 0;
    this->mPath          = Path;
    // 尝试打开文件，同时检测文件是否存在

    this->mFileName = "";
}
