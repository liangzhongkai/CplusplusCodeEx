//   46MS	252K	1438 B	C++
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
 
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
#define min(a, b) a>b?b:a
const int maxn = 5555;

int sum[maxn<<2];

void PushUP(int rt){
	sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}

void build(int l,int r,int rt) {  // 中 左 右赋初值为0 ，注意下标从1开始
	sum[rt] = 0;
	if (l == r) return ;
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
}

void update(int p,int l,int r,int rt) {   //  单点更新
	if (l == r){
		sum[rt] ++;
		return ;
	}
	int m = (l + r) >> 1;
	if (p <= m) update(p , lson);  // 求左子
	else update(p , rson);         // 求右子
	PushUP(rt);                    // 求中子
}

int query(int L,int R,int l,int r,int rt) {  //  区间求和
	if (L <= l && r <= R){
		return sum[rt];
	}
	int m = (l + r) >> 1;
	int ret = 0;
	if (L <= m) ret += query(L , R , lson);
	if (R > m) ret += query(L , R , rson);
	return ret;
}

int x[maxn];

int main() {
	int n, i;
	while (~scanf("%d",&n)) {
		build(0 , n - 1 , 1);
		int sum = 0;

		for (i = 0 ; i < n ; i ++) {    // 最初的逆序对
			scanf("%d",&x[i]);
			sum += query(x[i] , n - 1 , 0 , n - 1 , 1);
			update(x[i] , 0 , n - 1 , 1);
		}		

		int ret = sum;
		for (i = 0 ; i < n ; i ++) {     // 相邻逆序对之间的关系
			sum += n - x[i] - 1 - x[i] ;
			ret = min(ret , sum);
		}		
		printf("%d\n",ret);
	}
	return 0;
}