//
// Created by owmess on 2022/11/23.
//

#include "OS.h"
#include <limits>
#include <QDebug>
#include <algorithm>
#include <cmath>

using namespace std;

OS::OS(int maxSize) : _maxSize(maxSize) {
    _free.push_back({1, _maxSize});
}

bool OS::createPartition(int start, int end) {

    if (!initPartition({start, end})) {
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


bool OS::initPartition(const PTNNode initNode) {

    auto freeNode = _free.begin();
    //遍历空闲区
    for (; freeNode != _free.end(); freeNode++) {
        ///空闲表大小、首尾地址符合要求
        if (freeNode->size() > initNode.size() && freeNode->_begin <= initNode._begin &&
            freeNode->_end >= initNode._end) {

            auto tmp = *freeNode;
            //分离空闲表
            int state = freeNode->divideNode(initNode);
            if (state == 0)
                _free.erase(freeNode);
            if (state == 3) {
                _free.push_back({tmp._begin, initNode._begin - 1});
            }
            //添加占用表
            _bind.push_back({initNode._begin, initNode._end});
            break;
        }
    }
    //没有合适的区域分配
    if (freeNode == _free.end())
        return false;


    sortList();
    return true;

}

bool OS::firstFit(PTNNode &bind, int size) {
    //从头遍历空闲区,够大就分配
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
    //上次搜索的起点
    auto rootIter = _searchIter;
    //用于遍历的迭代器
    auto tmpIter = _searchIter;
    while (true) {
        //到尾部就重头查找
        if (tmpIter == _free.end()) {
            tmpIter = _free.begin();
        }
        //空闲表大小要大于作业大小
        if (tmpIter->size() > size) {
            bind = {tmpIter->_begin, tmpIter->_begin + size};
            tmpIter->divide(size);
            _searchIter = tmpIter;
            return true;
        }
        tmpIter++;
        //搜索到上次搜索的起点则搜索失败
        if (tmpIter == rootIter) {
            break;
        }
    }

    return false;
}

bool OS::bestFit(PTNNode &bind, int size) {
    //初始化为int的最大值
    const int MAX = std::numeric_limits<int>::max();
    int max = MAX;
    PTNList::iterator minNodeIter;
    //从头遍历空闲区
    for (auto iter = _free.begin(); iter != _free.end(); iter++) {
        //空间大于作业大小且小于记录的最大值
        if (iter->size() > size && iter->size() < max) {
            max = iter->size();
            minNodeIter = iter;
        }
    }
    if (max == MAX) {
        return false;
    }
    bind = PTNNode{minNodeIter->_begin, minNodeIter->_begin + size};
    minNodeIter->divide(size);
    _searchIter = minNodeIter;
    return true;

}

bool OS::worstFit(PTNNode &bind, int size) {
    //初始化为0
    const int MIN = 0;
    int min = MIN;
    PTNList::iterator maxNodeIter = _searchIter;

    for (auto iter = _free.begin(); iter != _free.end(); iter++) {
        //空间大于作业大小且大于记录的最小值
        if (iter->size() > size && iter->size() > min) {
            min = iter->size();
            maxNodeIter = iter;
        }
    }
    if (min == MIN) {
        return false;
    }
    bind = {maxNodeIter->_begin, maxNodeIter->_begin + size};
    maxNodeIter->divide(size);
    _searchIter = maxNodeIter;
    return true;

}

bool OS::mergePartition(int begin) {
    //查找占用区，是否有要释放的分区
    auto iter = std::find(_bind.begin(), _bind.end(), begin);
    if (iter == _bind.end()) {
        return false;
    }
    //先尝试将被释放的分区在空闲区合并
    auto piter = _free.begin();
    for (; piter != _free.end(); piter++) {
        if (piter->mergeNode(*iter)) {
            break;
        }
    }
    //合并失败就直接添加新的空闲表
    if (piter == _free.end())
        _free.push_back({*iter});

    //递增排序空闲表
    sortList();

    //合并相邻空闲分区
    PTNList::iterator tmpIt;
    for (auto it = _free.begin(); it != _free.end(); it++) {
        tmpIt = it;
        if (it->_end == (++tmpIt)->_begin) {
            it->_end = tmpIt->_end;
            it->_size = it->_end - it->_begin + 1;
            _free.erase(tmpIt);
            break;
        }
    }

    *iter = PTNNode{0, 0};

    return true;


}

void OS::quickFitInit() {
    _free.clear();
    bool firstFlag = true;
    int index = 1;
    auto iter = _free.begin();
    //初始化快速分配表，2^n各有一个分区
    for (int mi = _maxSize; mi > 0; mi /= 2) {
        PTNNode node;
        if (firstFlag) {
            firstFlag = false;
            _free.push_back({1, 1});
        } else {
            //从上次分配的尾地址接着分配
            int begin = _free.back()._end;
            _free.push_back({begin + 1, begin + index});
        }
        //添加到快速分配表中
        _quickFitList.insert(make_pair(index, PTNList{_free.back()}));
        index *= 2;
        if (index == _maxSize)
            break;
    }
    _free.clear();
}

bool OS::quickFit(int size) {

    //所需分区的大小（2^n）
    int index = 1;
    for (int mi = _maxSize; mi > 0; mi /= 2) {
        if (index >= size)
            break;
        index *= 2;
        if (index == _maxSize)
            break;
    }
    //在快速分配表中查询是否有空闲
    if (!_quickFitList[index].empty()) {//有，直接分配
        qDebug() << "! empty" << Qt::endl;
        PTNNode node = {*_quickFitList[index].begin()};
        _bind.emplace_back(node);
        _quickFitList[index].pop_front();
    } else {//没有，向上请求
        qDebug() << "empty" << Qt::endl;
        int i = index * 2;
//        index*=2;
        qDebug() << "index=" << index << Qt::endl;
        bool foundFlag=false;
        //逐级向上请求空间
        for (; i <= _maxSize/2; i *= 2) {

            qDebug() << "i = " << i << Qt::endl;
            if (!_quickFitList[i].empty()) {//存在空闲空闲
                //指数做差得到相差几个量级
                int num=log2(i)-log2(index);
                PTNNode node1;
                PTNNode node2;
                for (int j= 1; j <= num; j++) {
                    //分成两个小的内存块
                    PTNNode node = {*_quickFitList[i].begin()};
                    _quickFitList[i].pop_front();
                    node1 = {node._begin, node._begin + i / 2 - 1};
                    node2 = {node._begin + i / 2, node._end};
                    //添加到表中
                    _quickFitList[i/2].push_back(node1);
                    _quickFitList[i/2].push_back(node2);
                    i/=2;
                }
                //找到，去掉一个给作业使用
                _quickFitList[index].pop_back();
                _bind.push_back(node2);
//                PTNNode node={*_quickFitList[i].begin()};
//                _quickFitList[i].pop_front();
//                PTNNode node1={node._begin,node._begin+i/2-1};
//                PTNNode node2={node._begin+i/2,node._end};
//                _quickFitList[i-1].emplace_back(node1);
//
//                _bind.emplace_back(node2);
                foundFlag=true;
                break;
            }

        }
        if(!foundFlag)
            return false;
    }
    ///在控制台输出调试信息
    for(const auto& i:this->_quickFitList){
        int x=0;
        for(const auto j:i.second){
            qDebug(" free LinkList <%d,%d>  begin: %d , end: %d \n",i.first,x++,j._begin,j._end );
        }
//        painter.drawLine(QPoint(_x + bind._begin, _y), QPoint(_x + bind._begin, _y + _h));
    }
    for(const auto& i:this->_bind){
        qDebug("BindList  begin: %d , end: %d ",i._begin,i._end);
    }

    return true;
}

