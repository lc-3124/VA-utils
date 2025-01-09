#编译文件
#我只是为了让我的LSP正常工作，所以不要在意这个文件是否能有效完成编译任务

# 
# 这个Makefile文件的作用是编译所有源代码为obj，
# 然后以obj和inc为依赖编译所有test源码到build目录下
#

#目录、环境变量
CC=g++
CSTD=-std=c++11
OBJCFLAGS= -I.
TESTCFLAGS=  -Iobj -I. -g

#搜索库源代码，定义obj编译目录
SRCPH = $(wildcard src/Unix/*.cpp)
OBJPH = $(patsubst src/Unix/%.cpp,obj/%.o,$(SRCPH))

#搜索测试源代码，定义build目录
TESTPH = $(wildcard test/*.cpp)
BUILDPH=$(patsubst test/%.cpp,build/%,$(TESTPH))

#主目标:编译OBJ,编译BUILD
all:$(OBJPH) $(BUILDPH)

#obj编译规则
obj/%.o: src/Unix/%.cpp
	mkdir -p obj
	$(CC) $(OBJCFLAGS) -c $< -o $@ 

#BUILD编译规则
build/%: test/%.cpp
	mkdir -p build 
	$(CC) $(TESTCFLAGS) -o $@ $< $(OBJPH)

#伪目标
.PHONY:
	clean
#清除目录
clean:
	rm -rf obj
	rm -rf build
	@echo 2 dirs had been deleted 

debug:
	@echo $(TESTPH)
	@echo $(BUILDPH)
