//*  2228K	625MS	C++	2022B
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

#define max(a, b) ((a)>(b)?(a):(b))

#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
 
const int maxn = 55555;
int lsum[maxn<<2];        // lsum[rt]表示从m=(l+r)>>1向左有连续的多少个空位
int rsum[maxn<<2];
int msum[maxn<<2];        // msum[rt]表示
int cover[maxn<<2];       // cover[i]==-1,可能是混色，和未被染色

// 从被修改区间向下
void PushDown(int rt,int m) {
	if (cover[rt] != -1) {
		cover[rt<<1] = cover[rt<<1|1] = cover[rt];
		// 只有 全0 和 全1 的情况
		msum[rt<<1] = lsum[rt<<1] = rsum[rt<<1] = cover[rt] ? 0 : m - (m >> 1);
		msum[rt<<1|1] = lsum[rt<<1|1] = rsum[rt<<1|1] = cover[rt] ? 0 : (m >> 1);
		cover[rt] = -1;                                                               // 这句把修改过的封住了, 与下面pushup的cover[rt] = -1作用一样
	}
}
// 从被修改区间向上
void PushUp(int rt,int m) {  
	lsum[rt] = lsum[rt<<1];
	rsum[rt] = rsum[rt<<1|1];
	// 下面说明，lsum rsum有可能大于 msum
	if (lsum[rt] == m - (m >> 1)) lsum[rt] += lsum[rt<<1|1];                          //  lsum == rsum == msum时，证明相应的[l, r]区间都被赋值为1
	if (rsum[rt] == (m >> 1)) rsum[rt] += rsum[rt<<1];
	msum[rt] = max(lsum[rt<<1|1] + rsum[rt<<1] , max(msum[rt<<1] , msum[rt<<1|1]));   // 取左边、右边、左右+右左的最大值
	//cover[rt] = -1;                                                                 //   2228K	625MS	C++	2638B
}

void build(int l,int r,int rt) {
	msum[rt] = lsum[rt] = rsum[rt] = r - l + 1;
	cover[rt] = -1;
	if (l == r) return ;
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
}

void update(int L,int R,int c,int l,int r,int rt) {
	if (L <= l && r <= R) {
		msum[rt] = lsum[rt] = rsum[rt] = c ? 0 : r - l + 1;
		cover[rt] = c;
		return ;
	}
	PushDown(rt , r - l + 1);
	int m = (l + r) >> 1;
	if (L <= m) update(L , R , c , lson);
	if (m < R) update(L , R , c , rson);
	PushUp(rt , r - l + 1);
}

int query(int w,int l,int r,int rt) {
	//if (l == r){  return l;}       //    没了这句：  2228K	594MS	C++	2477B
	PushDown(rt , r - l + 1);
	int m = (l + r) >> 1;
	// 下面只有三种选择的原因是，确保了[l, r]区间内一定有大于w的一段
	if (msum[rt<<1] >= w) 
		return query(w , lson);
	else if (rsum[rt<<1] + lsum[rt<<1|1] >= w)    // 左边的右 + 右边的左
		return m - rsum[rt<<1] + 1;               // 关键！所有都在这里结束
	return query(w , rson);
}

int main() 
{
	int n , m;
	scanf("%d%d",&n,&m);
	build(1 , n , 1);
	while (m --) {
		int op , a , b;
		scanf("%d",&op);
		if (op == 1) {
			scanf("%d",&a);
			if (msum[1] < a) puts("0");
			else { 
				int p = query(a , 1 , n , 1);             //  左起点
				printf("%d\n",p);
				update(p , p + a - 1 , 1 , 1 , n , 1);    //  在区间[p, p+a-1]覆盖值1
			}
		} 
		else {
			scanf("%d%d",&a,&b);
			update(a , a + b - 1 , 0 , 1 , n , 1);
		}
	}
	return 0;
}

/*
10 6
1 3
1 3
1 3
1 1
2 5 5
1 6

1
4
7
0
5

*/