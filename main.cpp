//
// Created by owmess on 2022/11/23.
//
#include <iostream>
#include "OS.h"
#include <memory>
#include <fmt/printf.h>
#define MAXSIZE 1000
using namespace std;
using namespace fmt;
int main(){


    start:
    {
        OS os(MAXSIZE);

        if(!os.createPartition())
            goto start;

        while(true){
            int input;
            print("请输入要到来进程需要的内存大小，输入0则推出程序>");
            cin>>input;
            if(input==0)
                break;
            int choose;
            print("请输入要采用的算法:\n1.最先适应分配\n2.下次适应分配\n3.最优适应分配\n4.最坏适应分配\n5.快速适应分配");
            cin>>choose;
            switch(choose){
                case 1:os.dividePartition(200,OS::firstFit);
                case 2:break;
                case 3:break;
                case 4:break;
                case 5:break;
                default:break;
            }
        }
    }

    return 0;
}
