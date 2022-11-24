//
// Created by owmess on 2022/11/23.
//
#ifndef DYNAMICPARITION_OS_H
#define DYNAMICPARITION_OS_H

#include "PartitionNode.h"


class OS {
public:
    OS()=delete;
    /**
     * @param maxSize 分区长度
     */
    explicit OS(int maxSize);
    //创建初始分区
    bool createPartition();
    static bool firstFit(PTNNode n1,int size);

/**
 *
 * @tparam Comp
 * @param _free 空闲区域
 * @param size 待分配大小
 * @param comp 分区算法
 */
template<typename Comp>
bool dividePartition(int size, Comp comp);

private:

    template<typename Comp>
    bool divideFree(PTNList &list,int size,Comp comp,PTNNode &bindNode);

    static void mergeBind(PTNList &list, PTNNode node);

    /**
     * 初始化分区
     * @param initList 代填入节点表
     * @return 错误返回false
     */
    bool initPartition(PTNList initList);




private:
    int _maxSize;
    ///空闲表
    PTNList _free;
    ///占用表
    PTNList _bind;
};


#endif //DYNAMICPARITION_OS_H
