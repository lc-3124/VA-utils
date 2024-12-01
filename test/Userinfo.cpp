#include "src/VaSystem.hpp"  // 替换为实际包含VaSystem类定义的文件名
#include <iostream>
using namespace std;

int main() {
    // 测试获取用户名功能
    std::string userName = VaSystem::getUserName();
    std::cout << "获取用户名测试：" << std::endl;
    if (userName.empty()) {
        std::cout << "获取用户名失败，返回空字符串" << std::endl;
    } else {
        std::cout << "用户名: " << userName << std::endl;
    }

    // 测试获取当前时间功能
    std::string currentTime = VaSystem::getCurrentTime();
    std::cout << "获取当前时间测试：" << std::endl;
    if (currentTime.empty()) {
        std::cout << "获取当前时间失败，返回空字符串" << std::endl;
    } else {
        std::cout << "当前时间: " << currentTime << std::endl;
    }

    // 测试获取环境变量功能（以PATH环境变量为例）
    const char* index = "PATH";
    std::string env = VaSystem::getRunningEnvironment(index);
    std::cout << "获取环境变量（PATH）测试：" << std::endl;
    if (env.empty()) {
        std::cout << "获取环境变量失败，返回空字符串" << std::endl;
    } else {
        std::cout << "环境变量（PATH）内容: " << env << std::endl;
    }

    // 测试获取设备名称功能
    std::string deviceName = VaSystem::getDeviceName();
    std::cout << "获取设备名称测试：" << std::endl;
    if (deviceName.empty()) {
        std::cout << "获取设备名称失败，返回空字符串" << std::endl;
    } else {
        std::cout << "设备名称: " << deviceName << std::endl;
    }

    // 测试获取主机名功能
    std::string hostName = VaSystem::getHostName();
    std::cout << "获取主机名测试：" << std::endl;
    if (hostName.empty()) {
        std::cout << "获取主机名失败，返回空字符串" << std::endl;
    } else {
        std::cout << "主机名: " << hostName << std::endl;
    }

    // 测试获取运行目录功能
    std::string runningDirectory = VaSystem::getRunningDirectory();
    std::cout << "获取运行目录测试：" << std::endl;
    if (runningDirectory.empty()) {
        std::cout << "获取运行目录失败，返回空字符串" << std::endl;
    } else {
        std::cout << "运行目录: " << runningDirectory << std::endl;
    }

    return 0;
}
