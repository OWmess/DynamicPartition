//
// Created by owmess on 2022/11/23.
//

#include "OS.h"
#include <iostream>
#include <fmt/format.h>
using namespace std;
using namespace fmt;
OS::OS(int maxSize):_maxSize(maxSize-1) {
    _free.push_back({0,maxSize});
    _bind.push_back({0,0});
}

bool OS::createPartition() {
    int existTask;
    PTNList initList;
    print("请输入已装入的作业数>");
    cin>>existTask;
    if(existTask==0)
        return true;
    for(int i=0;i<existTask;i++){
        int begin;
        int end;
        print("请输入作业{}的首地址>",i);
        cin>>begin;
        print("请输入作业{}的尾地址>",i);
        cin>>end;
        print("-----------------\n");
        initList.push_back({begin,end});
    }
    if(!initPartition(initList)){
        print("输入的作业地址有误,地址最大值为{}\n",_maxSize);
        return false;
    }

    return true;
}

template<typename Comp>
bool OS::dividePartition(PTNList &free, PTNList &bind, PTNNode node, Comp comp) {
    if(divideFree(free, node.size(), comp)){
        mergeBind(bind, node);
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

void OS::mergeBind(PTNList &list, PTNNode node) {
    auto it=list.begin();
    for(;it!=list.end();it++){
        if(it->mergeNode(node))
            break;
    }
    if(it==list.end()){
        list.push_back(node);
    }

}

bool OS::initPartition(PTNList initList) {
    auto initNode=initList.begin();
    auto freeNode=_free.begin();

    for(;initNode!=initList.end();initNode++){
        for(;freeNode!=_free.end();freeNode++){

            if(firstFit(*freeNode,initNode->size())&&freeNode->_begin<=initNode->_begin&&freeNode->_end>=initNode->_end) {
                auto tmp = *freeNode;
                //分离空闲表
                int state=freeNode->divideNode(*initNode);
                if(state==0)
                    _free.erase(freeNode);
                if (state == 3) {
                    _free.push_back({tmp._begin, initNode->_begin - 1});
                }
                //添加占用表
                mergeBind(_bind, *initNode);
                break;
            }
        }
        freeNode=_free.begin();
        if(freeNode==_free.end())
            return false;

    }



//
//    for(auto initNode:initList){
//        bool state=false;
//        for(auto &freeNode:_free){
//            if(firstFit(freeNode,initNode.size())&&freeNode._begin<=initNode._begin&&freeNode._end>=initNode._end) {
//                auto tmp = freeNode;
//                //分离空闲表
//                int state=freeNode.divideNode(initNode);
//                if(state==0)
//                    _free.erase(initNode);
//                if (state == 3) {
//                    _free.push_back({tmp._begin, initNode._begin - 1});
//                }
//                //添加占用表
//                mergeBind(_bind, initNode);
//                state=true;
//            }
//        }
//        if(!state)
//            return false;
//    }



    return true;

}





