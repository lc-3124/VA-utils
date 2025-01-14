#include <iostream>
#include <string>

#include <fstream>
#include <string>
#include <cstdlib>
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
