//
// Created by owmess on 2022/11/23.
//
#include <iostream>
#include "OS.h"
#include <memory>
#define MAXSIZE 1000
using namespace std;
int main(){


    start:
    {
        OS os(MAXSIZE);

        if(!os.createPartition())
            goto start;

        while(true){
            int input;
            cout<<"请输入要到来进程需要的内存大小，输入0则退出程序>";
            cin>>input;
            if(input==0)
                break;
            int choose;
            cout<<"请输入要采用的算法:\n1.最先适应分配\n2.下次适应分配\n3.最优适应分配\n4.最坏适应分配\n5.快速适应分配\n>";
            cin>>choose;
            switch(choose){
                case 1:
                    os.dividePartition(200,FIRST_FIT);
                    break;
                case 2:
                    os.dividePartition(200,NEXT_FIT);
                    break;
                case 3:
                    os.dividePartition(200,BEST_FIT);
                    break;
                case 4:
                    os.dividePartition(200,WORST_FIT);
                    break;
                case 5:break;
                default:break;
            }

        }

    }

    return 0;
}
