#变量声明
	#g++
CC = g++
	#cflags
IV = -I../VaTui/


#编译所有
all : Userinfo 

#删除编译过的，重新编译
rebuild: clear all

clear : 
	rm -rf build
	mkdir build

Userinfo: Userinfo.cpp 
	${CC} Userinfo.cpp -o Userinfo ${IV}
