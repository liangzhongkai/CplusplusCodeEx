//   0ms   356k
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include<iostream>

using namespace std;

#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
 
const int maxn = 2222;
int cnt[maxn << 2];                           // 正数为改层横线长度是否包括这个区间
double sum[maxn << 2];                        // 两个端点之间的长度
double X[maxn];                               // 底层包含的真正长度，用来计算sum[]的

struct Seg{
	double h , l , r;
	int s;
	Seg(){}
	Seg(double a,double b,double c,int d) : l(a) , r(b) , h(c) , s(d) {}
	bool operator < (const Seg &cmp) const {
		return h < cmp.h;
	}
}ss[maxn];

// 分两种情况，更新层 及其 上层  的处理
// 其中更新层有分对  0 和 非0  的处理
void PushUp(int rt,int l,int r) {
	if (cnt[rt]) sum[rt] = X[r+1] - X[l];      // 所在区间长度。如果是点，那就是与下一个点(横坐标排序)的距离
	else if (l == r) sum[rt] = 0;              // 当减1时，最低层被减为0时，发挥作用
	else sum[rt] = sum[rt<<1] + sum[rt<<1|1];  // 非完全所在区间的上层部分
}

void update(int L,int R,int c,int l,int r,int rt) {
	if (L <= l && r <= R) {
		cnt[rt] += c;
		PushUp(rt , l , r);
		return ;
	}
	int m = (l + r) >> 1;
	if (L <= m)   update(L , R , c , lson);
	if (m < R)   update(L , R , c , rson);
	PushUp(rt , l , r);
}

// 在X[]的[0, k)范围内找key的序列号
int Bin(double key,int n,double X[]) {
	int l = 0 , r = n - 1;
	while (l <= r) {
		int m = (l + r) >> 1;
		if (X[m] == key) return m;
		if (X[m] < key) l = m + 1;
		else r = m - 1;
	}
	return -1;
}

int main() {
	freopen("in.txt", "r", stdin);
	int n , i, cas = 1;
	while (~scanf("%d",&n) && n) {
		int m = 0;
		while (n --) {
			double a , b , c , d;
			scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
			X[m] = a;
			ss[m++] = Seg(a , c , b , 1);
			X[m] = c;
			ss[m++] = Seg(a , c , d , -1);
		}

		sort(X , X + m);
		sort(ss , ss + m);

		// 横坐标离散化
		int k = 1;
		for (i = 1 ; i < m ; i ++) {
			if (X[i] != X[i-1]) X[k++] = X[i];
		}

		//for (i = 0 ; i < m ; i ++) {
		//	cout << ss[i].l << " " << ss[i].r << endl;
		//}

		memset(cnt , 0 , sizeof(cnt));
		memset(sum , 0 , sizeof(sum));
		double ret = 0;
		for (i = 0 ; i < m - 1 ; i ++) {
			//cout << "**";
			int l = Bin(ss[i].l , k , X);        // ss[i].l是第i个矩形的左横坐标
			int r = Bin(ss[i].r , k , X) - 1;    // ss[i].r是第i个矩形的右横坐标
			//cout << l << " " << r << " " << ss[i].l << " " << ss[i].r << " " << ss[i].s << endl;
			if (l <= r)   update(l , r , ss[i].s , 0 , k - 1, 1);
			ret += sum[1] * (ss[i+1].h - ss[i].h);
			//  将多边矩形分成一层一层的
			//cout << sum[1] * (ss[i+1].h - ss[i].h) << " " << sum[1] << " " << ss[i+1].h << " " << ss[i].h << endl;  
		}
		printf("Test case #%d\nTotal explored area: %.2lf\n\n", cas++ , ret);
	}
	return 0;
}