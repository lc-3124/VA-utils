
# C++ 类库使用指南

本 C++ 类库提供了一系列实用功能，帮助开发者在终端环境和系统交互等场景中高效编程。下面将详细介绍类库中各个核心模块的功能、使用方法以及示例代码。

## 一、VaTui::Color - 颜色控制模块

### 1.1 功能概述

该模块主要用于终端文本颜色的控制，包括设置前景色（文本颜色）、背景色以及颜色特效，如闪烁、加粗等，增强终端输出的视觉效果。它提供了多种设置颜色的方式，支持不同颜色模式，还具备颜色转换和特效设置等功能。

### 1.2 方法详解

`fastOutput(const char *str)`：私有方法，用于快速输出文字到终端，是对`系统调用write()向标准输出写数据`的封装。

`_SetColor4bit(int front, int background)`：生成用于设置 4 位颜色模式下文本前景色和背景色的 ansi 转义序列字符串，返回该字符串指针。

`SetColor4bit(int front, int background)`：借助`fastOutput`函数输出`_SetColor4bit`生成的 ansi 转义序列，实现将终端文本的前景色和背景色设置为指定的 4 位颜色模式颜色。

`_SetColor256(int front, int background)`：生成用于设置 16 位颜色模式下文本前景色和背景色的 ansi 转义序列字符串，返回该字符串指针。

`SetColor256(int front, int background)`：借助`fastOutput`函数输出`_SetColor256`生成的 ansi 转义序列，实现将终端文本的前景色和背景色设置为指定的 16 位颜色模式颜色。

`_set_background_color_RGB(int R, int B, int G)`：生成用于设置 RGB 模式下背景色的 ansi 转义序列字符串，返回该字符串指针。

`set_background_color_RGB(int R, int B, int G)`：借助`fastOutput`函数输出`_set_background_color_RGB`生成的 ansi 转义序列，实现将终端文本的背景色设置为指定的 RGB 颜色。

`_set_front_color_RGB(int R, int B, int G)`：生成用于设置 RGB 模式下前景色的 ansi 转义序列字符串，返回该字符串指针。

`set_front_color_RGB(int R, int B, int G)`：借助`fastOutput`函数输出`_set_front_color_RGB`生成的 ansi 转义序列，实现将终端文本的前景色设置为指定的 RGB 颜色。

`_SetEffect(short effect, bool isEnable)`：根据传入的文本显示效果枚举值（`effect`）以及是否启用该效果的布尔值（`isEnable`），生成对应的 ANSI 转义序列字符串，返回该字符串指针。

`SetEffect(short effect, bool isEnable)`：借助`fastOutput`函数输出`_SetEffect`生成的 ansi 转义序列，立即应用设置的文本显示效果。

`_ColorEffectReset()`：生成用于重置颜色特效的 ansi 转义序列字符串，返回该字符串指针。

`ColorEffectReset()`：借助`fastOutput`函数输出`_ColorEffectReset`生成的 ansi 转义序列，重置文本的颜色特效。

`RgbToAnsi256Color(int r, int g, int b)`：将 RGB 颜色值转换为 Ansi 256 色模式下的颜色值。

`Ansi256ColorToRGB(int ansi256Color, int& r, int& g, int& b)`：将 Ansi 256 色模式下的颜色值转换为 RGB 颜色值。

`MixAnsi256Colors(int color1, int color2)`：混合两个 Ansi 256 色模式下的颜色值，返回混合后的颜色值。

`AntiAnsi256Color(int colorcode)`：反转 Ansi 256 色模式下的颜色值，返回反转后的颜色值。

`Ansi16ColorToAnsi256(int ansi16Color)`：将 Ansi 16 色模式下的颜色值转换为 Ansi 256 色模式下的颜色值。

`Ansi256ColorToAnsi16(int ansi256Color)`：将 Ansi 256 色模式下的颜色值转换为 Ansi 16 色模式下的颜色值。

`Ansi256ColorToAnsi4bit(int ansi256Color, bool isFrontOrBack)`：将 Ansi 256 色模式下的颜色值转换为 Ansi 4 位颜色模式下的颜色值，`isFrontOrBack`用于区分前景色和背景色（未实现）。

`Ansi4bitColorToAnsi16(int ansi4bitColor)`：将 Ansi 4 位颜色模式下的颜色值转换为 Ansi 16 色模式下的颜色值（未实现）。

### 1.3 示例代码



```
\#include \<iostream>

\#include "VaTui/Color.h"

int main() {

&#x20;   // 设置4位颜色模式

&#x20;   std::cout << VaTui::Color::\_SetColor4bit(1, 7);

&#x20;   std::cout << "红色前景，白色背景文本" << std::endl;

&#x20;   // 设置256色模式

&#x20;   std::cout << VaTui::Color::SetColor256(210, 150);

&#x20;   std::cout << "粉色前景，淡蓝背景文本" << std::endl;

&#x20;   // 设置RGB颜色模式

&#x20;   std::cout << VaTui::Color::set\_front\_color\_RGB(255, 0, 0);

&#x20;   std::cout << "纯红色前景文本" << std::endl;

&#x20;   // 设置颜色特效

&#x20;   std::cout << VaTui::Color::SetEffect(1, true); // 闪烁效果

&#x20;   std::cout << "闪烁的文本" << std::endl;

&#x20;   // 重置颜色特效

&#x20;   std::cout << VaTui::Color::ColorEffectReset();

&#x20;   std::cout << "特效已重置" << std::endl;

&#x20;   // 颜色转换

&#x20;   int r, g, b;

&#x20;   VaTui::Color::Ansi256ColorToRGB(210, r, g, b);

&#x20;   std::cout << "210对应的RGB值: " << r << ", " << g << ", " << b << std::endl;

&#x20;   return 0;

}
```

## 二、VaTui::Cursor - 光标操作模块

### 2.1 功能概述

用于控制终端光标的位置和显示状态，如移动光标到指定坐标、隐藏或显示光标。通过生成和输出 ANSI 转义序列来实现各种光标操作。

### 2.2 方法详解

`fastOutput(const char *str)`：私有方法，用于快速输出文字到终端，为特效字符串提供输出。

`_CursorMoveTo(int h, int w)`：生成用于将光标移动到指定坐标（`h`为行，`w`为列）的 ANSI 转义序列字符串，返回该字符串指针。

`CursorMoveTo(int h, int w)`：借助`fastOutput`函数输出`_CursorMoveTo`生成的 ansi 转义序列，将光标移动到指定坐标。

`_CursorMove(int dr, int ds)`：根据传入的方向枚举常量参数（`dr`）和移动距离（`ds`）生成用于移动光标的 ANSI 转义序列字符串，返回该字符串指针。

`CursorMove(int dr, int ds)`：借助`fastOutput`函数输出`_CursorMove`生成的 ansi 转义序列，按照指定方向和距离移动光标。

`_CursorReset()`：生成用于将光标重置到默认位置（通常是终端屏幕左上角，即第一行第一列）的 ANSI 转义序列字符串，返回该字符串指针。

`CursorReset()`：借助`fastOutput`函数输出`_CursorReset`生成的 ansi 转义序列，将光标重置到默认位置。

`_CursorHide()`：生成用于隐藏光标的 ANSI 转义序列字符串，返回该字符串指针。

`CursorHide()`：借助`fastOutput`函数输出`_CursorHide`生成的 ansi 转义序列，隐藏光标。

`_CursorShow()`：生成用于显示光标的 ANSI 转义序列字符串，返回该字符串指针。

`CursorShow()`：借助`fastOutput`函数输出`_CursorShow`生成的 ansi 转义序列，显示光标。

### 2.3 示例代码



```
\#include \<iostream>

\#include "VaTui/Cursor.h"

int main() {

&#x20;   // 移动光标到指定位置

&#x20;   std::cout << VaTui::Cursor::\_CursorMoveTo(10, 5);

&#x20;   std::cout << "在(10, 5)位置输出文本" << std::endl;

&#x20;   // 相对移动光标

&#x20;   std::cout << VaTui::Cursor::\_CursorMove(1, 3); // 假设1代表向下移动

&#x20;   std::cout << "在相对位置移动后输出文本" << std::endl;

&#x20;   // 隐藏光标

&#x20;   std::cout << VaTui::Cursor::CursorHide();

&#x20;   std::cout << "光标已隐藏，继续输出文本" << std::endl;

&#x20;   // 显示光标

&#x20;   std::cout << VaTui::Cursor::CursorShow();

&#x20;   std::cout << "光标已显示" << std::endl;

&#x20;   // 重置光标位置

&#x20;   std::cout << VaTui::Cursor::CursorReset();

&#x20;   std::cout << "光标已重置" << std::endl;

&#x20;   return 0;

}
```

## 三、VaTui::System - 系统信息获取模块

### 3.1 功能概述

获取系统相关信息，如用户名、系统时间、运行环境等，方便程序根据系统状态进行个性化设置。

### 3.2 方法详解

`getUserName()`：返回当前用户名。

`getCurrentTime()`：获取系统当前时间。

`getRunningEnvironment(const char* index)`：获取指定环境变量的值，`index`为环境变量名。

`getDeviceName()`：返回设备名称。

`getHostName()`：返回主机名。

`getRunningDirectory()`：返回当前运行目录。

`getSystemOuput(const char* cmd)`：执行指定的系统命令（`cmd`），并返回命令的输出结果。

### 3.3 示例代码



```
\#include \<iostream>

\#include "VaTui/System.h"

int main() {

&#x20;   std::string username = VaTui::System::getUserName();

&#x20;   std::cout << "当前用户名: " << username << std::endl;

&#x20;   std::string systime = VaTui::System::getCurrentTime();

&#x20;   std::cout << "当前系统时间: " << systime << std::endl;

&#x20;   std::string env = VaTui::System::getRunningEnvironment("PATH");

&#x20;   std::cout << "PATH环境变量: " << env << std::endl;

&#x20;   std::string deviceName = VaTui::System::getDeviceName();

&#x20;   std::cout << "设备名称: " << deviceName << std::endl;

&#x20;   std::string hostName = VaTui::System::getHostName();

&#x20;   std::cout << "主机名: " << hostName << std::endl;

&#x20;   std::string runningDir = VaTui::System::getRunningDirectory();

&#x20;   std::cout << "当前运行目录: " << runningDir << std::endl;

&#x20;   std::string systemOutput = VaTui::System::getSystemOuput("ls -l");

&#x20;   std::cout << "ls -l命令输出: " << systemOutput << std::endl;

&#x20;   return 0;

}
```

## 四、VaTui::Term - 终端控制模块

### 4.1 功能概述

提供对终端输入输出、属性设置和屏幕控制的功能，如获取终端属性、清空屏幕、非缓冲模式获取键盘输入。在 Linux 下是对`terminfo`、`termios`等库的封装。

### 4.2 方法详解

`getTerminalAttributes()`：获取一次终端设置，保存在一个静态变量中。

`setTerminalAttributes(const struct termios &newAttrs)`：设置终端属性。

`setTerminalAttrsSafely(const termios &newAttrs)`：安全地设置终端属性。

`getTerminalAttrsSafely()`：安全地获取终端属性。

`SaveTerm()`：保存（刷新）终端设置。

`RestoreTerm()`：恢复终端设置。

`_Clear()`：生成用来清空屏幕的 Ansi 字符串，返回该字符串指针。

`Clear()`：借助`fastOutput`函数输出`_Clear`生成的 ansi 转义序列，清空屏幕。

`_ClearLine()`：生成用于清除一行的 Ansi 字符串，返回该字符串指针。

`ClearLine()`：借助`fastOutput`函数输出`_ClearLine`生成的 ansi 转义序列，清除一行。

`enableEcho()`：启用回显。

`disableEcho()`：禁用回显。

`enableConsoleBuffering()`：启用控制台缓冲。

`disableConsoleBuffering()`：禁用控制台缓冲。

`getTerminalSize(int &rows, int &cols)`：获取终端大小，`rows`返回行数，`cols`返回列数。

`setCursorPosition(int row, int col)`：设置光标位置。

`saveCursorPosition()`：保存光标位置。

`restoreCursorPosition()`：恢复光标位置。

`fastOutput(const char* str)`：无缓冲输出。

`nonBufferedGetKey()`：类似`getch()`，非缓冲模式下获取键盘按键。

`getTerminalType()`：返回终端类型。

`setLineBuffering(bool enable)`：启、禁用行缓冲。

`getCharacter()`：类似`getch()`，但没有终端回显，副作用是执行完后会把回显打开。

`isTerminalFeatureSupported(const char* feature)`：检查终端是否支持指定的功能（`feature`）。

`setCharacterDelay(int milliseconds)`：设置字符延迟。

`getInputSpeed()`：获取输入速度。

`setInputSpeed(int speed)`：设置输入速度。

`setOutputSpeed(int speed)`：设置输出速度。

`getkeyPressed(char &k)`：无阻塞获取按键，失败就返回 - 1，否则将按键值存入`k`。

`setCursorShape(CursorShape shape)`：根据传入的枚举常量参数来设置光标形状。

`FlushStdOut()`：所有更改终端和`fastOutput`都有可能影响到标准输出，如果你不是在开发一个完全的 TUI 程序，请使用这个函数刷新标准输出。

### 4.3 示例代码



```
\#include \<iostream>

\#include "VaTui/Term.h"

int main() {

&#x20;   // 获取终端属性

&#x20;   VaTui::Term::getTerminalAttributes();

&#x20;   // 清空屏幕

&#x20;   std::cout << VaTui::Term::Clear();

&#x20;   std::cout << "屏幕已清空，重新输出内容" << std::endl;

&#x20;   // 禁用回显

&#x20;   VaTui::Term::disableEcho();

&#x20;   std::cout << "回显已禁用，输入字符不会显示" << std::endl;

&#x20;   // 获取键盘输入

&#x20;   char key = VaTui::Term::nonBufferedGetKey();

&#x20;   std::cout << "你按下的键是: " << key << std::endl;

&#x20;   // 启用回显

&#x20;   VaTui::Term::enableEcho();

&#x20;   // 获取终端大小

&#x20;   int rows, cols;

&#x20;   VaTui::Term::getTerminalSize(rows, cols);

&#x20;   std::cout << "终端大小: " << rows << "行, " << cols << "列" << std::endl;

&#x20;   // 设置光标位置

&#x20;   VaTui::Term::setCursorPosition(5, 10);

&#x20;   std::cout << "在(5, 10)位置输出文本" << std::endl;

&#x20;   return 0;

}
```

## 五、VaTui::Utf - UTF 字节处理模块

### 5.1 功能概述

处理 UTF - 8 编码字符串，包括计算字节数、判断字符编码、提取指定位置字符等，还具备检测字符宽度、判断是否为 ASCII 字符等功能。

### 5.2 方法详解

`getUtf8CharWidth(const char* s)`：检测一段含有 UTF 字符的字符串的第一个有效字符的内存宽度。

`getUtf8ByteCount(char c)`：返回 UTF - 8 编码字符的字节数。

`isAscii(char c)`：判断字符是否为 ASCII 字符。

`isUtf8StartByte(char c)`：判断字符是否为 UTF - 8 编码的起始字节。

`isUtf8Char(const char* bytes, int len)`：判断给定字节数组是否为有效的 UTF - 8 字符，`len`为字节数组长度。

`isGbkChar(const char* bytes, int len)`：判断给定字节数组是否为有效的 GBK 字符，`len`为字节数组长度。

`getUtf8CharaInString( std::string resource, std::string &save, int index )`：从一段字符串中获取第`index`个 Utf8 字符，成功返回`true`，并将字符存入`save`。

`getUtf8StringLen( std::string resource )`：统计 UTF - 8 字符串中的字符个数。

### 5.3 示例代码



```
\#include \<iostream>

\#include "VaTui/Utf.h"

int main
```
### 5.3 示例代码



```
\#include \<iostream>

\#include "VaTui/Utf.h"

int main() {

&#x20;   std::string utf8Str = "你好，世界";

&#x20;   // 检测字符宽度

&#x20;   size\_t width = VaTui::Utf().getUtf8CharWidth(utf8Str.c\_str());

&#x20;   std::cout << "第一个字符的内存宽度: " << width << std::endl;

&#x20;   // 计算字节数

&#x20;   char c = '你';

&#x20;   int byteCount = VaTui::Utf::getUtf8ByteCount(c);

&#x20;   std::cout << "字符'你'的字节数: " << byteCount << std::endl;

&#x20;   // 判断是否为ASCII字符

&#x20;   if (VaTui::Utf::isAscii(c)) {

&#x20;       std::cout << "字符'你'是ASCII字符" << std::endl;

&#x20;   } else {

&#x20;       std::cout << "字符'你'不是ASCII字符" << std::endl;

&#x20;   }

&#x20;   // 判断是否为UTF - 8起始字节

&#x20;   if (VaTui::Utf::isUtf8StartByte(c)) {

&#x20;       std::cout << "字符'你'是UTF - 8起始字节" << std::endl;

&#x20;   } else {

&#x20;       std::cout << "字符'你'不是UTF - 8起始字节" << std::endl;

&#x20;   }

&#x20;   // 判断是否为UTF - 8字符

&#x20;   if (VaTui::Utf::isUtf8Char(utf8Str.c\_str(), utf8Str.size())) {

&#x20;       std::cout << "字符串是有效的UTF - 8字符" << std::endl;

&#x20;   } else {

&#x20;       std::cout << "字符串不是有效的UTF - 8字符" << std::endl;

&#x20;   }

&#x20;   // 判断是否为GBK字符

&#x20;   std::string gbkStr = "\xD6\xD0\xB9\xFA"; // "中国"的GBK编码

&#x20;   if (VaTui::Utf::isGbkChar(gbkStr.c\_str(), gbkStr.size())) {

&#x20;       std::cout << "字符串是有效的GBK字符" << std::endl;

&#x20;   } else {

&#x20;       std::cout << "字符串不是有效的GBK字符" << std::endl;

&#x20;   }

&#x20;   // 提取指定位置字符

&#x20;   std::string savedChar;

&#x20;   if (VaTui::Utf::getUtf8CharaInString(utf8Str, savedChar, 1)) {

&#x20;       std::cout << "索引1位置的字符: " << savedChar << std::endl;

&#x20;   } else {

&#x20;       std::cout << "提取字符失败" << std::endl;

&#x20;   }

&#x20;   // 统计字符个数

&#x20;   int charCount = VaTui::Utf::getUtf8StringLen(utf8Str);

&#x20;   std::cout << "UTF - 8字符串中的字符个数: " << charCount << std::endl;

&#x20;   return 0;

}
```
