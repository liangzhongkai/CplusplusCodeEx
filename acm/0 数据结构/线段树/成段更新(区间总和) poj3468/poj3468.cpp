/*  4252K	1704MS	C++	1556B
//   4508K	2610MS	G++	1584B
#include <cstdio>
#include <algorithm>
using namespace std;
 
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
#define LL __int64

const int maxn = 111111;
LL add[maxn<<2];
LL sum[maxn<<2];

void PushUp(int rt) {
	sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}
void PushDown(int rt,int m) {  // m代表有多少个点
	if (add[rt]) {
		add[rt<<1] += add[rt];
		add[rt<<1|1] += add[rt];// 这两个要传递下去，因为是累加，所以是+=
		sum[rt<<1] += add[rt] * (m - (m >> 1));
		sum[rt<<1|1] += add[rt] * (m >> 1);
		add[rt] = 0;
	}
}
void build(int l,int r,int rt) {
	add[rt] = 0;
	if (l == r) {
		scanf("%lld",&sum[rt]);
		return ;
	}
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
	PushUp(rt);
}
void update(int L,int R,int c,int l,int r,int rt) {
	if (L <= l && r <= R) {
		add[rt] += c;
		sum[rt] += (LL)c * (r - l + 1);
		return ;
	}
	PushDown(rt , r - l + 1);
	int m = (l + r) >> 1;
	if (L <= m) update(L , R , c , lson);
	if (m < R) update(L , R , c , rson);
	PushUp(rt);
}
LL query(int L,int R,int l,int r,int rt) {
	if (L <= l && r <= R) {
		return sum[rt];
	}
	PushDown(rt , r - l + 1);   
	int m = (l + r) >> 1;
	LL ret = 0;
	if (L <= m) ret += query(L , R , lson);
	if (m < R) ret += query(L , R , rson);
	return ret;
}
int main() 
{
	int N , Q;
	scanf("%d%d",&N,&Q);
	build(1 , N , 1);
	while (Q --) {
		char op[2];
		int a , b , c;
		scanf("%s",op);
		if (op[0] == 'Q') {
			scanf("%d%d",&a,&b);
			printf("%I64d\n",query(a , b , 1 , N , 1));
		} else {
			scanf("%d%d%d",&a,&b,&c);
			update(a , b , c , 1 , N , 1);
		}
	}
	return 0;
}
//*/


//  4804K	2610MS	G++	1531B
#include<iostream>
#include<cstdio>

using namespace std;

#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define LL __int64

const int N = 111111;
LL sum[N<<2];
LL add[N<<2];

void pushup(int rt){
	sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}

void pushdown(int rt, int m){
	if(add[rt]){
		add[rt<<1] += add[rt];
		add[rt<<1|1] += add[rt];
		sum[rt<<1] += add[rt] * (m-(m>>1));
		sum[rt<<1|1] += add[rt] * (m>>1);
		add[rt] = 0;
	}
}

void build(int l, int r, int rt){
	add[rt] = 0;
	if(l==r){
		scanf("%I64d",&sum[rt]);
		return ;
	}
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
	pushup(rt);
}

void update(int L, int R, int c, int l, int r, int rt){
	if(L<=l && r<=R){
		add[rt] += c;
		sum[rt] += (LL)c * (r - l + 1);
		return ;
	}
	pushdown(rt, r - l + 1);
	int m = (l + r) >> 1;
	if(L<=m)   update(L, R, c, lson);
	if(m<R)   update(L, R, c, rson);
	pushup(rt);
}

LL query(int L, int R, int l, int r, int rt){
	if(L<=l && r<=R){
		return sum[rt];
	}
	pushdown(rt, r-l+1);
	int m = (l + r) >> 1;
	LL ans = 0;
	if(L<=m)   ans += query(L, R, lson);
	if(m<R)   ans += query(L, R, rson);
	return ans;
}

int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	int i;
	char ch;
	int a, b, c;
	build(1, n, 1);
	for(i=0; i<q; i++){
		getchar();
		scanf("%c", &ch);
		if(ch=='Q'){
			scanf(" %d %d", &a, &b);
			printf("%I64d\n", query(a, b, 1, n, 1));
		}
		else{
			scanf("%d %d %d", &a, &b, &c);
			update(a, b, c, 1, n, 1);
		}
	}

	return 0;
}