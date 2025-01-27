/*
 * (c) 2025 Lc3124
 * License (MIT)
 * 一口气将一段文字都转换成拼音
 */

#ifndef _VAPINYIN2_CPP_
#define _VAPINYIN2_CPP_

#include "VaTui.hpp"
#include "VaUtils.hpp"

bool VaUtils::Char2Pinyin2(const std::string resource,std::vector<std::string> &Pinyin)
{
    int size = VaTui::Utf::getUtf8StringLen( resource );

    for ( int cnt=0 ; cnt < size ; cnt++ )
    {
        std::string indexChar , py;
        VaTui::Utf::getUtf8CharaInString( resource , indexChar , cnt );
        Char2Pinyin( indexChar , py ); 
        Pinyin.push_back(py);
    }
    if(Pinyin.empty() != 0)
        return true;
    return false;
}

#endif
