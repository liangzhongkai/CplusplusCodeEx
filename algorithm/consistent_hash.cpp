#include "stdafx.h"

#ifdef _CONSISTENT_HASH_

//为了负载均衡，让数据找到相应的位置进行存储

//将机器节点node和数据，用统一的hash函数进行求值
//添加、删除：数据都自动迁移到hash值最近的节点
//平衡性：引入虚拟节点，例如有node1 node3   对应的虚拟节点：node1-1、node3-1、node1-2、node3-2
//

#endif