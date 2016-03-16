#include "stdafx.h"
#ifdef _DP_PACKET_9_SECTION_


/*
* 背包九讲     重量 w[1....N]     体积 v[1....M]
* 01背包       for w[1 to N]   for v[M to v[i]]    dp[i] = max{dp[i], dp[i-v[i]] | 1<=i<=M}     初始化：全为0
* 完全背包     for w[1 to N]   for v[1 to M]    dp[i] = max{dp[i], dp[i-v[i]] | 1<=i<=M}       初始化：dp[0] 为0   其余为-∞
* 多重背包     判断某个物品是否形成完全背包  否则做01背包处理   
* 前三种混合背包
* 多维消耗背包
* 互斥背包     互斥物品在每一个v[i] 进行竞争
* 依赖背包     转化为互斥，然后剔除明显劣质选项
* 依赖-》树形dp
*/


#endif