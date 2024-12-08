#变量声明
	#g++
CC = g++
	#cflags
IV = -I../VaTui/  #include the vatui



#编译所有
all : Userinfo Colortest 

#删除编译过的，重新编译
rebuild: clear all

clear : 
	rm -rf build
	mkdir build

######模块编译,默认以debug模式######

#VaSystem模块的测试
Userinfo: Userinfo.cpp 
	${CC} Userinfo.cpp -o build/Userinfo -g ${IV}

#Color模块的测试
Colortest: Colortest.cpp
	${CC} Colortest.cpp -o build/Colortest -g ${IV}


#火车
train: 
	sl
