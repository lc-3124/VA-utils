# 编译文件
# 我只是为了让我的 LSP 正常工作，所以不要在意这个文件是否能有效完成编译任务

# 
# 这个 Makefile 文件的作用是编译所有源代码为 obj，
# 然后以 obj 和 inc 为依赖编译所有 test 源码到 build 目录下
#

# 目录、环境变量
CC=g++
CSTD=-std=c++11
OBJCFLAGS= -I. -Iinc  # 增加对 inc 目录的头文件搜索，通常需要将 inc 目录加入到头文件搜索路径
TESTCFLAGS=  -Iobj -I. -Iinc -g  # 增加对 inc 目录的头文件搜索，通常需要将 inc 目录加入到头文件搜索路径

# 搜索库源代码，定义 obj 编译目录
SRCPH = $(wildcard src/Unix/*.cpp)
OBJPH = $(patsubst src/Unix/%.cpp,obj/%.o,$(SRCPH))

# 搜索测试源代码，定义 build 目录
TESTPH = $(wildcard test/*.cpp)
BUILDPH=$(patsubst test/%.cpp,build/%,$(TESTPH))

# 搜索演示源代码，定义 buildDemo 目录
DEMOPH = $(wildcard demo/*/*.cpp)
BUILDDEMOPH=$(patsubst demo/%.cpp,buildDemo/%,$(DEMOPH))

# 主目标: 编译 OBJ, 编译 BUILD
all:pre $(OBJPH) $(BUILDPH) $(BUILDDEMOPH) end

# obj 编译规则
obj/%.o: src/Unix/%.cpp
	@echo  "\n \e[33m现在编译\e[32m$<\e[33m成为 \e[32m$@\e[0m "
	@mkdir -p $(dir $@) 
	$(CC) $(CSTD) $(OBJCFLAGS) -c $< -o $@ 

# BUILD 编译规则 TEST
build/%: test/%.cpp
	@echo  "\n \e[33m现在编译\e[32m$<\e[33m成为 \e[32m$@\e[0m "
	@mkdir -p $(dir $@)  
	$(CC) $(CSTD) $(TESTCFLAGS) -o $@ $< $(OBJPH)

# BUILD 编译规则 DEMO
buildDemo/%: demo/%.cpp
	@echo  "\n \e[33m现在编译\e[32m$<\e[33m成为 \e[32m$@\e[0m "
	@mkdir -p $(dir $@) 
	$(CC) $(CSTD) $(TESTCFLAGS) -o $@ $< $(OBJPH)

# 伪目标
.PHONY: clean pre end install 

# 提示语
pre:
	@echo  "\e[45m 编译开始...... \e[0m\n"
	@echo  "\e[45m 祝你好运哟~    \e[0m"
	@sleep 1

end:
	@echo  "\n\e[45m 编译完成！     \e[0m"
# 清除目录
clean:
	rm -rf obj
	rm -rf build
	rm -rf buildDemo
	@echo 3 dirs had been deleted 

install:
	cp res/lib.txt ~/.pinyinglib.txt

debug:
	@echo $(TESTPH)
	@echo $(BUILDPH)

