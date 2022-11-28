//
// Created by owmess on 2022/11/23.
//
#include <list>
#include <algorithm>
#ifndef DYNAMICPARITION_PARTITIONNODE_H
#define DYNAMICPARITION_PARTITIONNODE_H

#define JUDGE_SIZE(SIZE) if(SIZE==1) return 0

class PartitionNode{
public:
    PartitionNode()=delete;
    /**
     * 节点构造函数
     * @param begin 首地址
     * @param end   末地址
     */
    PartitionNode(int begin,int end):_begin(begin),_end(end){
        _size=abs(end-begin)+1;
    }
    [[nodiscard]] int size() const{
        return _size;
    }
    /**
     *  合并节点
     * @param newNode 新节点
     * @return 合并失败返回false
     */
    bool mergeNode(PartitionNode newNode){
        if(this->_begin == newNode._end) {
            this->_begin = newNode._begin;
            _size=_end-_begin+1;
            return true;
        }else if(this->_end == newNode._begin) {
            this->_end = newNode._end;
            _size=_end-_begin+1;
            return true;
        }
        return false;
    }
    /**
     * 分离节点
     * @param divideNode 分离的节点
     * @return 1:空闲区在尾段  2：空闲区在前段  3：空闲区在两边(需后续push_back一个前段空闲区)
     */
    int divideNode(PartitionNode divideNode){
        if(this->_begin==divideNode._begin){///空闲区在尾段
            this->_begin=divideNode._end+1;
            _size=_end-_begin+1;
            JUDGE_SIZE(_size);
            return 1;
        }else if(this->_end==divideNode._end){///空闲区在前段
            this->_end=divideNode._begin-1;
            _size=_end-_begin+1;
            JUDGE_SIZE(_size);
            return 2;
        }else{///空闲区在两边
            this->_begin=divideNode._end+1;
            _size=_end-_begin+1;
            JUDGE_SIZE(_size);
            return 3;
        }
    }

    /**
     * 缩小节点大小
     * @param n 占用的大小
     */
    void divide(int n){
        _begin+=n;
        _size-=n;
    }

    bool operator <(PartitionNode node2) const{
        return this->_begin<node2._begin;
    }
    int _begin;
    int _end;
    int _size;
};
typedef std::list<PartitionNode> PTNList;
typedef PartitionNode PTNNode;

#endif //DYNAMICPARITION_PARTITIONNODE_H
