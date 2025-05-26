//in this file i want to run my server file.
//then I want to run my control file
//then I want to terminate after running both files
#include <iostream>
#include <windows.h>
int main(){
    const size_t size = 1024;
    char buffer[size];
    getcwd(buffer, size);
    std::string str = "/server.exe";
    strcat(buffer, str.c_str());
    int server = system(exePath)
}