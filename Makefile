#编译文件
#我只是为了让我的LSP正常工作，所以不要在意这个文件是否能有效完成编译任务

CC=g++
CCFLAGS=-Iinc

SRCPH = $(wildcard src/*.cpp)
OBJPH = $(patsubst src/%.cpp,obj/%.o,$(SRCPH))

all:$(OBJPH)

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CC) $(CCFLAGS) -c $< -o $@ 
