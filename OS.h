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
    OS(int maxSize);
    void createPartition();
private:
    int _maxSize;
    ///空闲表
    PTNList _free;
    ///占用表
    PTNList _bind;
};


#endif //DYNAMICPARITION_OS_H
