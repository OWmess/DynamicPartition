//
// Created by owmess on 2022/11/23.
//

#include "OS.h"
#include <iostream>
#include <limits>
#include <QDebug>
using namespace std;

OS::OS(int maxSize) : _maxSize(maxSize - 1) {
    _free.push_back({0, _maxSize});
    _bind.push_back({0, 0});
}

bool OS::createPartition(int start,int end) {

    PTNList list;
    list.push_back({start,end});
    if (!initPartition(list)) {
        qDebug()<<"输入的作业地址有误,地址最大值为 "<< _maxSize<<Qt::endl;
        return false;
    }

    return true;
}


bool OS::dividePartition(int size, ALGO mode) {

    PTNNode bindNode{0, 0};
    if (divideFree(size, mode, bindNode)) {
        mergeBind(_bind, bindNode);
        return true;
    }
    return false;
}

bool OS::divideFree(int size, ALGO mode, PTNNode &bindNode) {
    bool divideFlag = false;
    switch (mode) {
        case FIRST_FIT:
            divideFlag = firstFit(bindNode, size);
            break;
        case NEXT_FIT:
            divideFlag = nextFit(bindNode, size);
            break;
        case BEST_FIT:
            divideFlag = bestFit(bindNode, size);
            break;
        case WORST_FIT:
            divideFlag = worstFit(bindNode, size);
            break;
        case QUICK_FIT:
            break;
        default:
            break;
    }

    return divideFlag;

}

void OS::mergeBind(PTNList &list, PTNNode node) {
    auto it = list.begin();
    for (; it != list.end(); it++) {
        if (it->mergeNode(node))
            break;
    }
    if (it == list.end()) {
        list.push_back(node);
    }

}

bool OS::initPartition(PTNList initList) {
    auto initNode = initList.begin();

    auto freeNode = _free.begin();

    for (; initNode != initList.end(); initNode++) {
        for (; freeNode != _free.end(); freeNode++) {

            if (freeNode->size()>initNode->size() && freeNode->_begin <= initNode->_begin &&
                freeNode->_end >= initNode->_end) {

                auto tmp = *freeNode;
                //分离空闲表
                int state = freeNode->divideNode(*initNode);
                if (state == 0)
                    _free.erase(freeNode);
                if (state == 3) {
                    _free.push_back({tmp._begin, initNode->_begin - 1});
                }
                //添加占用表
                mergeBind(_bind, *initNode);

                break;
            }
        }
        if (freeNode == _free.end())
            return false;
        freeNode = _free.begin();

    }
    sortList();
    return true;

}

bool OS::firstFit(PTNNode &bind, int size) {
    for (auto it = _free.begin(); it != _free.end(); it++) {

        if (it->size() > size) {
            bind = {it->_begin, it->_begin + size};
            it->divide(size);
            _searchIter = it;

            return true;
        }
    }
    return false;
}

bool OS::nextFit(PTNNode &bind, int size) {
    auto rootIter = _searchIter;
    auto tmpIter = _searchIter;
    while (true) {
        if (tmpIter == _free.end()) {
            tmpIter = _free.begin();
        }
        //TODO 先暂时从上次iter开始搜索
        if (tmpIter->size() > size) {
            bind = {tmpIter->_begin, tmpIter->_begin + size};
            tmpIter->divide(size);
            _searchIter = tmpIter;
            return true;
        }
        tmpIter++;
        if (tmpIter == rootIter) {
            break;
        }
    }

    return false;
}

bool OS::bestFit(PTNNode &bind, int size) {
    const int MAX = std::numeric_limits<int>::max();
    int max = MAX;
    PTNList::iterator minNodeIter = _searchIter;

    for (auto iter = _free.begin(); iter != _free.end(); iter++) {
        if (iter->size() > size && iter->size() < max) {
            max = iter->size();
            minNodeIter = iter;
        }
    }
    if (max == MAX) {
        return false;
    }
    bind = {*minNodeIter};
    return true;

}

bool OS::worstFit(PTNNode &bind, int size) {
    const int MIN = 0;
    int min = MIN;
    PTNList::iterator maxNodeIter = _searchIter;

    for (auto iter = _free.begin(); iter != _free.end(); iter++) {
        if (iter->size() > size && iter->size() > min) {
            min = iter->size();
            maxNodeIter = iter;
        }
    }
    if (min == MIN) {
        return false;
    }
    bind = {*maxNodeIter};
    return true;

}

