//
// Created by owmess on 2022/11/23.
//
#include <list>
#include <algorithm>
#ifndef DYNAMICPARITION_PARTITIONNODE_H
#define DYNAMICPARITION_PARTITIONNODE_H

class PartitionNode{
public:
    PartitionNode()=delete;
    /**
     * 节点构造函数
     * @param begin 首地址
     * @param end   末地址
     */
    PartitionNode(int begin,int end):_begin(begin),_end(end){
        _size=abs(end-begin);
    }
    int size() const{
        return _size;
    }
    /**
     * 缩小节点大小
     * @param n 占用的大小
     */
    void divide(int n){
        _begin+=n;
        _size-=n;
    }

    int _begin;
    int _end;
    int _size;
};
typedef std::list<PartitionNode> PTNList;
typedef PartitionNode PTNNode;

#endif //DYNAMICPARITION_PARTITIONNODE_H
