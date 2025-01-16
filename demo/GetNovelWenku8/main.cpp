/*
 * 噢，
 * 我想说这是一个用bash写的爬虫，尽管这玩意是用cpp写的 
 * 这听起来很矛盾，
 * 准确来说是利用cpp构建bash指令来执行
 *
 * 这需要系统安装了wget，因为下载相关的操作是wget写的
 * 
 * 这个爬虫程序之前帮我将整个轻小说文库的小说爬了个精光
 * 我使用VaTui来增强这个程序的视觉体验 
 *
 *      .
 *      broad.hpp     与显示相关的类
 *      dowload.hpp   构建wget指令来进行下载的类，以及文件操作也封装于此
 *      config.hpp    宏和变量们
 *
 *          config  被 dowload 包含
 *          dowload 被 broad   包含  
 *          broad   被 main    包含
 */

/* 
 * main.cpp
 * 2025 main.cpp
 *
 * 程序的主函数被包含在这个文件中
 */

int main()
{

    for (int i = 0 ; i<10 ; i++)
    {
        std::string cmd = "wget -q --no-proxy https://dl2.wenku8.com/txtutf8/0/";
        cmd += std::to_string(i);
        cmd += ".txt";

        std::cout<<"正在下载资源："<<i<<".txt\n";
        system(cmd.c_str());

        std::string rs;
        rs += std::to_string(i);
        rs += ".txt";
        std::ifstream file(rs.c_str());
        if (!file.is_open()) {
            std::cout<<rs<<"下载失败，跳过!\n";
            continue;
        }

        std::string line;

        std::getline(file,line);
        std::getline(file,line);
        line = "";
        std::getline(file,line);

        file.close();

        std::cout<<"获取到文件："<<line<<"\n";

        std::string line2;
            
        for(int i=1;i<100;i++)
        {
            if(line[i] == ' ')    
            {
                line2+="_";
            }
            else if(line[i] == '('
                    || line[i] == ')')
            {
                line2+="_";
            }
            else if(line[i] == '>')
                break;
            else line2+=line[i];
        }

        std::string newFileName = line2 + "-" + std::to_string(i) + ".txt" ;

        if (std::rename(rs.c_str(), newFileName.c_str())!= 0) {
            std::cout<<"重命名失败！\n";
        }

        std::cout << "文件重命名成功为: " << newFileName << std::endl;

        std::string cmdmv;
        cmdmv += "mkdir -p res_get; mv ";
        cmdmv += newFileName + " " + "res_get/" + newFileName;

        system(cmdmv.c_str());
    }

}
