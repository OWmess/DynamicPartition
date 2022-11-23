//
// Created by owmess on 2022/11/23.
//

#include "OS.h"
#include <iostream>
#include <fmt/format.h>
using namespace std;
using namespace fmt;
OS::OS(int maxSize):_maxSize(maxSize) {
    _free.push_back({0,maxSize});
    _bind.push_back({0,0});
}

void OS::createPartition() {
    int existTask;
    print("请输入已装入的作业数>");
    cin>>existTask;
    for(int i=0;i<existTask;i++){
        int begin;
        int end;
        print("请输入作业{}的首地址>",i);
        cin>>begin;
        print("请输入作业{}的尾地址>",i);
        cin>>end;
        print("-----------------\n");

    }


}