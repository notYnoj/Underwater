#include <iostream>
#include <cstdlib>

int main(){
    int server = system("./server"); //begins server on our end
    //int controller = system("./controller.out"); <- on PI? should make calls
    //int plot = system("python3 plotting.py");
    if(!server){
        return -1;
    }
    else{
        //wait until input
        int t;
        std::cin>>t;
    }
}