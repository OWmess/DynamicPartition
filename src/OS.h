//
// Created by owmess on 2022/11/23.
//
#ifndef DYNAMICPARITION_OS_H
#define DYNAMICPARITION_OS_H

#include "PartitionNode.h"

typedef enum {
    FIRST_FIT = 0,
    NEXT_FIT,
    BEST_FIT,
    WORST_FIT,
    QUICK_FIT
} ALGO;

class OS {
public:
    OS() = delete;

    /**
     * @param maxSize 分区长度
     */
    explicit OS(int maxSize);

    //创建初始分区
    bool createPartition(int start, int end);

    [[nodiscard]] PTNList getFree() const {
        return _free;
    }

    [[nodiscard]] PTNList getBind() const {
        return _bind;
    }

    bool mergePartition(int begin);

    bool dividePartition(int size, ALGO mode);

private:


    bool divideFree(int size, ALGO mode, PTNNode &bindNode);

    /**
     * 初始化分区
     * @param initList 代填入节点表
     * @return 错误返回false
     */
    bool initPartition(PTNList initList);

    bool firstFit(PTNNode &bind, int size);

    bool nextFit(PTNNode &bind, int size);

    bool bestFit(PTNNode &bind, int size);

    bool worstFit(PTNNode &bind, int size);

    inline void sortList() {
        _free.sort();
//        _bind.sort();
    }

private:
    int _maxSize;
    ///空闲表
    PTNList _free;
    ///占用表
    PTNList _bind;

    PTNList::iterator _searchIter = _free.begin();

};


#endif //DYNAMICPARITION_OS_H
