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
        int size=end-begin;
        if(!dividePartition(_free, _bind, {begin,end}, firstFit)){
            print("分配失败！");
        }


    }

}

template<typename Comp>
bool OS::dividePartition(PTNList &free, PTNList &bind, PTNNode node, Comp comp) {
    if(divideFree(free, node.size(), comp)){
        divideBind(bind, node);
        return true;
    }
    return false;
}



bool OS::firstFit(PTNNode n1,int size) {
    return n1.size() > size;
}

template<typename Comp>
bool OS::divideFree(PTNList &list, int size, Comp comp) {
    for(auto it=list.begin(); it != list.end(); it++){
        if(comp(*it,size)){
            it->divide(size);
            return true;
        }
    }
    return false;
}

void OS::divideBind(PTNList &list, PTNNode node) {
    auto it=list.begin();
    for(;it!=list.end();it++){
        if(it->_begin == node._end) {
            it->_begin = node._begin;
            break;
        }else if(it->_end == node._begin) {
            it->_end = node._end;
            break;
        }
    }
    if(it==list.end()){
        list.push_back(node);
    }


}





