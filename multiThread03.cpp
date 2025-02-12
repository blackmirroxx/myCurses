
#include <iostream>
#include <thread>

void sumUp10Arguments(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j){
    int res = a+b+c+d+e+f+g+h+i+j;
    std::cout << "a+b+c+d+e+f+g+h+i+j= " << res << std::endl;
}

int main(void){
    std::cout << std::endl;

    std::thread calcMe(sumUp10Arguments,1,2,3,4,5,6,7,8,9,10); // 55
    calcMe.join();

    std::cout << std::endl;
}
