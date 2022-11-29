//
// Created by owmess on 2022/11/23.
//

#include "OS.h"
#include <limits>
#include <QDebug>

using namespace std;

OS::OS(int maxSize) : _maxSize(maxSize) {
    _free.push_back({0, _maxSize});
}

bool OS::createPartition(int start, int end) {

    PTNList list;
    list.push_back({start, end});
    if (!initPartition(list)) {
        qDebug() << "输入的作业地址有误,地址最大值为 " << _maxSize << Qt::endl;
        return false;
    }
    return true;
}


bool OS::dividePartition(int size, ALGO mode) {

    PTNNode bindNode{0, 0};
    if (divideFree(size, mode, bindNode)) {
        _bind.emplace_back(bindNode);
        sortList();

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


bool OS::initPartition(PTNList initList) {
    auto initNode = initList.begin();

    auto freeNode = _free.begin();

    for (; initNode != initList.end(); initNode++) {
        for (; freeNode != _free.end(); freeNode++) {

            if (freeNode->size() > initNode->size() && freeNode->_begin <= initNode->_begin &&
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
                _bind.push_back({initNode->_begin,initNode->_end});
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
            bind = {it->_begin+1, it->_begin + size};
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
        if (tmpIter->size() > size) {
            bind = {tmpIter->_begin+1, tmpIter->_begin + size};
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
    PTNList::iterator minNodeIter;

    for (auto iter = _free.begin(); iter != _free.end(); iter++) {

        if (iter->size() > size && iter->size() < max) {
            max = iter->size();
            minNodeIter = iter;
        }
    }
    if (max == MAX) {
        return false;
    }
    bind = PTNNode{minNodeIter->_begin+1,minNodeIter->_begin+size};
    minNodeIter->divide(size);
    _searchIter = minNodeIter;
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
    bind = {maxNodeIter->_begin+1,maxNodeIter->_begin+size};
    maxNodeIter->divide(size);
    _searchIter = maxNodeIter;
    return true;

}

bool OS::mergePartition(int begin) {
    auto iter=std::find(_bind.begin(), _bind.end(),begin);
    if(iter==_bind.end()){
        return false;
    }
    auto piter=_free.begin();
    for(; piter != _free.end(); piter++){
        if(piter->mergeNode(*iter)){
            break;
        }
    }
    if(piter == _free.end())
        _free.push_back({*iter});

    sortList();

    //合并相邻空闲分区
    PTNList::iterator tmpIt;
    for(auto it=_free.begin();it!=_free.end();it++){
        tmpIt=it;
        if(it->_end==(++tmpIt)->_begin){
            it->_end=tmpIt->_end;
            it->_size=it->_end-it->_begin+1;
            _free.erase(tmpIt);
            break;
        }
    }

    *iter=PTNNode{0,0};

    return true;



}

void OS::quickFitInit() {
    _free.clear();
    bool firstFlag=true;
    int index=1;
    auto iter=_free.begin();
    for(int mi = _maxSize;mi>0;mi/=2){
        if(firstFlag){
            firstFlag=false;
            _free.push_back({1,1});
        }else{
            int begin=_free.back()._end;
            _free.push_back({begin+1,begin+index});
        }
        _quickFitList.insert(make_pair(index,PTNList{_free.back()}));
        index*=2;
        if(index==_maxSize)
            break;
    }

}

bool OS::quickFit(int size) {
    int index=1;
    for(int mi = _maxSize;mi>0;mi/=2){
        if(index>=size)
            break;
        index*=2;
        if(index==_maxSize)
            break;
    }
    if(!_quickFitList[index].empty()){
        PTNNode node={*_quickFitList[index].begin()};
        _bind.emplace_back(node);
        _quickFitList[index].pop_front();
    }else{
        int i=index*2;
        index*=2;
        for(;i<=512;i*=2){
            if(!_quickFitList[i].empty()){
                PTNNode node={*_quickFitList[i].begin()};
                _quickFitList[i].pop_front();
                PTNNode node1={node._begin,node._begin+i/2-1};
                PTNNode node2={node._begin+i/2,node._end};
                _quickFitList[i].emplace_back(node1);
                _bind.emplace_back(node2);
                break;
            }

        }
    }



}

