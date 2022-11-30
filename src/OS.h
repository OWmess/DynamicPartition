//
// Created by owmess on 2022/11/23.
//
#ifndef DYNAMICPARITION_OS_H
#define DYNAMICPARITION_OS_H

#include "PartitionNode.h"
#include <map>

/**
 * 算法枚举
 */
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

    /**
     * 初始化分区
     * @param start 首地址
     * @param end 末地址
     * @return 错误返回false
     */
    bool createPartition(int start, int end);

    [[nodiscard]] PTNList getFree() const {
        return _free;
    }

    [[nodiscard]] PTNList getBind() const {
        return _bind;
    }

    [[nodiscard]] std::map<int,PTNList> getQFList() const{
        return _quickFitList;
    }

    /**
     * 释放作业
     * @param begin 将释放的作业的首地址
     * @return 错误返回false
     */
    bool mergePartition(int begin);


    /**
     * 分配作业
     * @param size 所需大小
     * @param mode 分配模式
     * @return 错误返回false
     */
    bool dividePartition(int size, ALGO mode);

    /**
     * 初始化快速适应分配分区
     */
    void quickFitInit();
    /**
     * 快速适应分区-分配
     * @param size 所需大小
     * @return 错误返回false
     */
    bool quickFit(int size);
private:

    /**
     * 从空闲区给作业分配空间
     * @param size 需要的空间大小
     * @param mode 分配算法
     * @param bindNode 被分配分区
     * @return 错误返回false
     */
    bool divideFree(int size, ALGO mode, PTNNode &bindNode);

    /**
     * 初始化分区
     * @param node 代填入节点表
     * @return 错误返回false
     */
    bool initPartition(PTNNode node);
    /**
     * 首次适应算法
     * @param bind 被分配分区
     * @param size 需要的空间大小
     * @return
     */
    bool firstFit(PTNNode &bind, int size);

    /**
     * 下次适应算法
     * @param bind 被分配分区
     * @param size 需要的空间大小
     * @return
     */
    bool nextFit(PTNNode &bind, int size);

    /**
    * 最佳适应算法
    * @param bind 被分配分区
    * @param size 需要的空间大小
    * @return
    */
    bool bestFit(PTNNode &bind, int size);
    /**
    * 最坏适应算法
    * @param bind 被分配分区
    * @param size 需要的空间大小
    * @return
    */
    bool worstFit(PTNNode &bind, int size);

    /**
     * 递增排序
     */
    inline void sortList() {
        _free.sort();
//        _bind.sort();
    }

private:
    //必须是2的指数
    int _maxSize;
    ///空闲表
    PTNList _free;
    ///占用表
    PTNList _bind;
    //下次适应的指针
    PTNList::iterator _searchIter = _free.begin();
    //快速分配表
    std::map<int,PTNList> _quickFitList;
};


#endif //DYNAMICPARITION_OS_H
