#include "VaUtf8Tools.hpp"
#include <iostream>
#include <cstring>

int main()
{
    char* str = "Hello ,world 你好世界，这是一段带有多字节utf符号的字符串 ha ha 😂 \0";
        int i=0;
    char *pstr=str;
    while(true)
    {
     int num = getUtf8CharWidth(pstr);
        pstr+=num;
        i+=num;
     if(str[i]=='\0')break;
        pstr-=num;
     for(int j=0;j<num;j++)
     {
         std::cout<<pstr[j];
     }
     std::cout<<" "<<num<<"\n";
        pstr+=num;
    }
} 
