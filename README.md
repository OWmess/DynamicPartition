# DynamicPartition
可变分区分配仿真算法：首次适应，下次适应，最佳适应，最坏适应和快速分配。
````
src
│  main.cpp             main函数
│  OS.cpp               系统类，负责分区的分配与释放
│  OS.h
│  PartitionNode.h      节点类，为链表的基本数据结构
│
└─ui                    ui相关
│  ErrorMessage.h       错误信息弹窗
│
├─BindDialog            分配窗口
│      BindDialog.cpp
│      BindDialog.h
│      BindDialog.ui
│
├─FreeDialog            释放窗口
│      FreeDialog.cpp
│      FreeDialog.h
│      FreeDialog.ui
│
├─InitDialog            初始化窗口
│      InitDialog.cpp
│      InitDialog.h
│      InitDialog.ui
│
├─QuickFitDialog        快速分配窗口
│      QuickFitDialog.cpp
│      QuickFitDialog.h
│      QuickFitDialog.ui
│
└─Widget                主窗口
│      Widget.cpp
│      Widget.h
│      Widget.ui

//.ui文件为qt窗口设计文件
````

















# GUI
采用qt框架绘制ui

# 算法实现
使用std::list 构建链表,数据结构为 PartitionNode {begin,end,size} 
## 分配
通过在空闲区（free）使用 四种分配算法（除快速分配）查找空闲区域并分配，并在占用区（bind）添加新节点
## 释放
在占用区（bind）查找，并去相应节点，在空闲区先尝试扩容相邻区域（节点），失败则添加新节点

# 快速分配实现
使用std::map<int,PartitionNode> 构建查找表，每个表内存在对应的链表。
## 快速分配（伙伴算法原理）
假如系统需要4(2*2)个页面大小的内存块，该算法就到free_area[2]中查找，如果链表中有空闲块，就直接从中摘下并分配出去。如果没有，算法将顺着数组向上查找free_area[3],如果free_area[3]中有空闲块，则将其从链表中摘下，分成等大小的两部分，前四个页面作为一个块插入free_area[2]，后4个页面分配出去，free_area[3]中也没有，就再向上查找，如果free_area[4]中有，就将这16(2*2*2*2)个页面等分成两份，前一半挂如free_area[3]的链表头部，后一半的8个页等分成两等分，前一半挂free_area[2]
的链表中，后一半分配出去。假如free_area[4]也没有，则重复上面的过程，知道到达free_area数组的最后，如果还没有则放弃分配。