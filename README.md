# VA-utils
utils for VAWK

# 介绍：
- 这是写我的一组小软件`VAWK`(Visual Ansi Widget kit)的工具类
- VAWK是一个用来再控制台中画一些“窗口”和处理一些用户输入的库，可以实现基于控制台的类图形化用户接口，用cpp编写
- VaTui实际上是VAWK底层实现的一部分，我把它单独拿出来开发
- 如果要让VAWK在不同的机器和操作系统上工作，只要修改VaTui的源代码

# 概述
## 实现了5个模块
#### 可以用来进行支持TUI的各种操作
#### 如光标移动、光标外观、颜色输出、颜色混合、无阻塞输入、
#### 无缓冲输出、封装终端设置、检测utf字节等等......

## 使用样例(样例适用于VAWK,请移步`github.com/lc-3124/VAWK`)
```c++
#include "VaTui.hpp"
int main()
{
    VaTui::Term::fastOutput("Hello world!");    //调用Term子模块下的fastOutput来无缓冲输出
    return 0;
}
```
```bash
g++ -o main main.cpp -lVAWK 
```

# 报告
1. 基本能用了，就是欠一点调教，以及还有几个没有实现的功能
2. 进行一些更改，修复了一些BUG
3. 添加了一个没啥用的测试
4. 添加了中文转拼音的方法，在VAuntils类中

# 任务
- [x] 解决 char2pinyin2方法无法正确返回英文的情况
- [ ] 打算加入VaColor模块生成256色号的程序，通过RGB三个分量(0~5)来指定颜色(VaTui.hpp L127)

## 下阶段任务:
- [x] 完成各个模块源码和声明的分离
- [ ] 编写Windows的实现
- [ ] 整合到VAWK中
