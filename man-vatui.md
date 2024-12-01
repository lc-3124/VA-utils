# 一、引言
本使用手册旨在帮助开发者了解和使用基于 `VaTui` 相关类实现的终端用户界面（TUI）操作功能库。该库提供了诸如光标控制、颜色设置、终端属性操作以及字符编码相关判断等功能，方便在终端应用开发中实现更丰富和友好的交互界面。

# 二、整体结构概述
整个功能库围绕 `VaTui` 类展开，它整合了多个功能子模块，包括 `VaCursor`（光标操作）、`VaColor`（颜色控制）、`VaTerm`（终端属性与屏幕操作）、`VaSystem`（系统相关功能，目前代码示例中暂未详细体现其具体功能实现）、`VaUtf`（字符编码判断相关功能）。通过创建 `VaTui` 类的实例，可以方便地调用各子模块提供的功能方法来操作终端界面。

# 三、VaTui 类使用说明
## 3.1 类的初始化与释放
`VaTui` 类的构造函数会自动初始化其包含的各个子模块实例，示例代码如下：

```cpp
#include "VaTui.hpp" // 假设包含 VaTui 类定义的头文件

int main() {
    VaTui myTui; // 创建 VaTui 实例，此时内部各个子模块也会被初始化
                 // 后续可以使用 myTui 调用相关功能方法

    return 0;
}
```

而析构函数会在对象生命周期结束时，自动释放各个子模块实例所占用的内存资源，确保不会产生内存泄漏。

# 四、VaColor 类功能使用
## 4.1 颜色设置
- **4 位颜色模式设置**：
可以使用 `SetColor4bit` 方法来设置文本的前景色和背景色，颜色通过 `color4bit` 命名空间下的枚举值指定。示例：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    myTui.Color->SetColor4bit(color4bit::FRONT_RED, color4bit::BACKGROUND_WHITE); // 设置前景为红色，背景为白色
    std::cout << "This text is in red on white background." << std::endl;
    myTui.Color->SetColor4bit(color4bit::FRONT_BLACK, color4bit::BACKGROUND_BLACK); // 恢复默认颜色（黑底黑字）
    return 0;
}
```

- **16 位颜色模式设置**：
通过 `SetColor256` 方法，传入对应颜色代码来设置文本和背景颜色。例如：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    myTui.Color->SetColor256(12, 4); // 设置前景色为亮红色（BRIGHT_RED），背景色为蓝色（BLUE）
    std::cout << "This text has bright red on blue background." << std::endl;
    myTui.Color->SetColor256(7, 0); // 恢复默认颜色（黑底白字）
    return 0;
}
```

- **RGB 颜色模式设置（需终端支持）**：
使用 `set_background_color_RGB` 和 `set_front_color_RGB` 方法来设置背景和前景的全彩色（RGB 模式），传入 `R`、`G`、`B` 三个分量的值（范围通常是 0 - 255）。示例（假设终端支持 RGB 颜色）：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    myTui.Color->set_front_color_RGB(255, 0, 0); // 设置前景色为红色（RGB 全红）
    myTui.Color->set_background_color_RGB(0, 255, 0); // 设置背景色为绿色（RGB 全绿）
    std::cout << "This text is red on green background." << std::endl;
    // 恢复默认颜色设置（这里可调用合适的重置方法，比如后面提到的颜色效果重置）
    return 0;
}
```

## 4.2 文本效果控制
可以利用 `SetEffect` 方法结合 `AnsiEffect` 枚举来设置文本的各种显示效果，如加粗、斜体等，传入效果枚举值和是否启用的布尔值。示例：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    myTui.Color->SetEffect(static_cast<short>(AnsiEffect::BOLD), true); // 启用加粗效果
    std::cout << "This is bold text." << std::endl;
    myTui.Color->SetEffect(static_cast<short>(AnsiEffect::BOLD), false); // 关闭加粗效果
    return 0;
}
```

## 4.3 颜色效果重置
使用 `_ColorEffectReset` 方法（通常可以通过 `Color` 成员的对应接口调用）来将文本颜色和效果恢复到默认状态，示例：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    // 假设之前设置了各种颜色和效果
    myTui.Color->SetEffect(static_cast<short>(AnsiEffect::ITALIC), true); // 启用斜体效果
    myTui.Color->SetColor256(10, 4); // 设置特定颜色
                                     // 进行其他操作后，想要恢复默认
    myTui.Color->fastOutput(myTui.Color->_ColorEffectReset()); // 重置颜色和效果
    std::cout << "Text is back to default appearance." << std::endl;
    return 0;
}
```

# 五、VaCursor 类功能使用
## 5.1 光标位置移动
- **移动到指定位置**：
使用 `CursorMoveTo` 方法，传入目标位置的行（`h`）和列（`w`）坐标，将光标移动到指定位置。示例：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    myTui.Cursor->CursorMoveTo(5, 10); // 将光标移动到第 5 行第 10 列
    std::cout << "Cursor is now at row 5, column 10." << std::endl;
    return 0;
}
```

- **按方向和距离移动**：
通过 `CursorMove` 方法，传入移动方向的枚举值（如 `CUR_LEFT`、`CUR_RIGHT` 等）以及移动的距离，来按指定方向移动光标。示例：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    myTui.Cursor->CursorMoveTo(3, 5); // 先将光标移动到初始位置
    myTui.Cursor->CursorMove(CUR_RIGHT, 3); // 向右移动 3 个单位
    std::cout << "Cursor has moved 3 positions to the right." << std::endl;
    return 0;
}
```

## 5.2 光标显示控制
- **隐藏光标**：
调用 `CursorHide` 方法可以隐藏光标，适用于一些需要无光标干扰的界面展示场景。示例：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    myTui.Cursor->CursorHide(); // 隐藏光标
                                // 进行一些界面绘制等操作，不需要看到光标
    std::cout << "Cursor is hidden now." << std::endl;
    myTui.Cursor->CurShow(); // 后续如果需要再显示光标
    return 0;
}
```

- **显示光标**：
使用 `CurShow` 方法来重新显示被隐藏的光标，恢复正常的光标可见性。示例代码可参考上述隐藏光标示例中 `myTui.Cursor->CurShow();` 这一行的使用场景。

## 5.3 光标位置重置
调用 `CursorReset` 方法能将光标重置到默认位置（通常是终端界面的左上角，即第一行第一列），示例：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    myTui.Cursor->CursorMoveTo(10, 20); // 移动光标到其他位置
    myTui.Cursor->CursorReset(); // 重置光标到默认位置
    std::cout << "Cursor is reset to the default position." << std::endl;
    return 0;
}
```

# 六、VaTerm 类功能使用
## 6.1 终端屏幕操作
- **清除整个屏幕**：
使用 `Clear` 方法可以快速清除终端屏幕上的所有内容，示例：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    std::cout << "Some text on the screen before clearing." << std::endl;
    myTui.Term->Clear(); // 清除屏幕
    std::cout << "Screen is cleared now." << std::endl;
    return 0;
}
```

- **清除从光标位置到行尾内容**：
调用 `ClearLine` 方法，可清除从光标所在位置到当前行末尾的内容，示例：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    std::cout << "This is a long line of text that we want to partially clear." << std::endl;
    myTui.Term->CursorMoveTo(1, 10); // 将光标移动到第一行第 10 列位置
    myTui.Term->ClearLine(); // 清除从该位置到行尾的内容
    std::cout << "The text after the cursor position on the line is cleared." << std::endl;
    return 0;
}
```

## 6.2 终端属性控制
- **获取终端尺寸**：
通过 `getTerminalSize` 方法可以获取当前终端窗口的行数和列数，示例：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    int rows, cols;
    myTui.Term->getTerminalSize(rows, cols);
    std::cout << "Terminal has " << rows << " rows and " << cols << " columns." << std::endl;
    return 0;
}
```

- **控制终端输入回显**：
可以使用 `enableEcho` 和 `disableEcho` 方法来控制终端输入是否回显字符。例如，在需要用户输入密码等不希望显示输入内容的场景下，可先禁用回显，输入完成后再启用回显。示例：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    myTui.Term->disableEcho(); // 禁用输入回显
    std::cout << "Please enter something, it won't be shown on the screen: ";
    char input[100];
    std::cin.getline(input, 100); // 获取用户输入（但不会显示输入内容）
    myTui.Term->enableEcho(); // 启用回显
    std::cout << "You entered: " << input << std::endl;
    return 0;
}
```

- **控制终端输入缓冲机制**：
`enableConsoleBuffering` 和 `disableConsoleBuffering` 方法用于控制终端输入的缓冲行为，示例（简单示意不同缓冲设置下的输入获取情况）：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    myTui.Term->disableConsoleBuffering(); // 禁用缓冲
    std::cout << "Type something quickly without pressing Enter: ";
    char c = myTui.Term->getCharacter(); // 获取单个字符输入（即时获取，无需等待回车）
    std::cout << "You typed: " << c << std::endl;
    myTui.Term->enableConsoleBuffering(); // 启用缓冲
    std::cout << "Now type something and press Enter: ";
    std::string input;
    std::getline(std::cin, input); // 按正常缓冲方式获取一行输入
    std::cout << "You entered: " << input << std::endl;
    return 0;
}
```

- **保存与恢复光标位置**：
使用 `saveCursorPosition` 和 `restoreCursorPosition` 方法可以保存当前光标位置并在后续恢复到该位置，方便在进行一些临时界面操作后回到之前的光标位置，示例：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    myTui.Term->CursorMoveTo(5, 10); // 移动光标到指定位置
    myTui.Term->saveCursorPosition(); // 保存光标位置
    myTui.Term->CursorMoveTo(8, 15); // 移动光标到其他位置进行一些操作
    std::cout << "Doing something at new cursor position." << std::endl;
    myTui.Term->restoreCursorPosition(); // 恢复到之前保存的光标位置
    std::cout << "Cursor is back to the saved position." << std::endl;
    return 0;
}
```

# 七、VaUtf 类功能使用
## 7.1 判断字符编码相关
- **判断是否为 ASCII 字符**：
使用 `isAscii` 方法，传入一个字符，判断其是否为 `ASCII` 字符，示例：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    char c = 'A';
    if (myTui.Utf->isAscii(c)) {
        std::cout << c << " is an ASCII character." << std::endl;
    } else {
        std::cout << c << " is not an ASCII character." << std::endl;
    }
    return 0;
}
```

- **判断是否为 UTF-8 编码字符**：
通过 `isUtf8Char` 方法，传入字节序列及其长度，判断是否为合法的 `UTF-8` 编码字符，示例：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    char bytes[] = {0xC3, 0xA9}; // 示例的 UTF-8 编码字节序列（对应字符 é）
    if (myTui.Utf->isUtf8Char(bytes, sizeof(bytes))) {
        std::cout << "The given bytes represent a UTF-8 character." << std::endl;
    } else {
        std::cout << "The given bytes do not represent a UTF-8 character." << std::endl;
    }
    return 0;
}
```

- **判断是否为 GBK 编码字符（简单判断）**：
利用 `isGbkChar` 方法，传入两个字节序列，依据简单的字节范围判断是否可能为 `GBK` 编码字符，示例：

```cpp
#include "VaTui.hpp"

int main() {
    VaTui myTui;
    char bytes[] = {0xB0, 0xE6}; // 示例的可能符合 GBK 编码范围的字节序列
    if (myTui.Utf->isGbkChar(bytes, sizeof(bytes))) {
        std::cout << "The given bytes might represent a GBK character." << std::endl;
    } else {
        std::cout << "The given bytes do not represent a GBK character." << std::endl;
    }
    return 0;
}
```

# 八、注意事项
- 不同终端对 `ANSI` 转义序列（用于实现颜色、光标控制等功能）的支持程度可能有所不同，部分功能（如 `GB` 颜色设置等）在某些老旧或特殊终端上可能无法正常显示预期效果。
- 在操作终端属性（如输入回显、缓冲控制等）时，需要确保在合适的时机恢复到原始设置，避免影响后续终端的正常使用以及其他应用程序与终端的交互。
- 对于字符编码判断相关功能，`isGbkChar` 方法只是基于简单的字节范围进行判断，并非严格准确的 `GBK` 编码验证，在实际应用中如果需要精确判断 `GBK` 编码，可能需要更复杂的实现逻辑。

希望这份使用手册能够帮助你更好地理解和运用这些类来开发终端用户界面相关的应用程序。如果在使用过程中有任何疑问或者遇到问题，可以进一步查阅相关代码实现以及参考终端编程的相关文档资料。 
