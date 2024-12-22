#pragma once
/*
 * (C) Lc3124 
 * release in  2024 
 * LICENSE (MIT)
 * 这个文件包含一个类，用来获取各种系统信息
 */

#include <iostream>
#include <ctime>
#include <unistd.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <cstdlib>

class VaSystem {
    public:
        // 获取用户名
        static std::string getUserName() {
            uid_t uid = getuid();
            struct passwd *pw = getpwuid(uid);
            if (pw!= nullptr) {
                return std::string(pw->pw_name);
            }
            return "";

        }

        // 获取当前时间
        static std::string getCurrentTime() {
            time_t now = time(nullptr);
            char buffer[80];
            struct tm *timeinfo = localtime(&now);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
            return std::string(buffer);

        }

        //获取环境变量
        static std::string getRunningEnvironment(const char *index) {
            const char *env = std::getenv(index);
            std::string result = "";
            if (env!= nullptr) {
                result += env;
            }
            return result;

        }

        // 获取设备名称（这里通过utsname结构体获取系统信息中的机器名部分来近似表示设备名称）
        static std::string getDeviceName() {
            struct utsname uts;
            if (uname(&uts)!= -1) {
                return std::string(uts.machine);
            }
            return "";

        }

        // 获取主机名
        static std::string getHostName() {
            char hostname[256];
            if (gethostname(hostname, sizeof(hostname))!= -1) {
                return std::string(hostname);
            }
            return "";
        }

        // 获取运行目录
        static std::string getRunningDirectory() {
            char buffer[256];
            if (getcwd(buffer, sizeof(buffer))!= nullptr) {
                return std::string(buffer);
            }
            return "";

        }

};
