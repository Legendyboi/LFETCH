#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <memory>

std::string executeCommand(const std::string& command){
    std::string result;
    std::array<char,128> buffer;
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe){
        throw std::runtime_error("popen() failed!");
    }
        while(!feof(pipe.get())){
            if(fgets(buffer.data(), 128, pipe.get()) != nullptr){ result += buffer.data();}
        }
    return result;
}

std::string getSystemInfo(){
    std::string info;
    info += "---- System Information ----\n";
    info += executeCommand("uname -a");
    info += executeCommand("lsb_release -a");
    return info;
}

std::string getCPUInfo(){
    std::string info;
    info += "--- CPU Information ---\n";
    info += executeCommand("lscpu");
    return info;
}

std::string getMemoryInfo(){
    std::string info;
    info += "--- Memory Information ---\n";
    info += executeCommand("free -h");
    return info;
}

std::string getDiskInfo(){
    std::string info;
    info += "--- Disk Information ---\n";
    info += executeCommand("df -h");
    return info;
} 

int main(){

    std::string systemInfo = getSystemInfo();
    std::string cpuInfo = getCPUInfo();
    std::string memoryInfo = getMemoryInfo();
    std::string diskInfo = getDiskInfo();

    std::cout << systemInfo << std::endl;
    std::cout << cpuInfo << std::endl;
    std::cout << memoryInfo << std::endl;
    std::cout << diskInfo << std::endl;

    return 0;
}