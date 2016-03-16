//*    484MS	2280K	1194 B	C++
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1

const int N = 222222;
int maxn[N<<2];

void pushup(int rt)
{
	maxn[rt] = maxn[rt<<1]>maxn[rt<<1|1])?maxn[rt<<1]:maxn[rt<<1|1];
}

void build(int l, int r, int rt)
{
	if(l==r)
	{
		scanf("%d", &maxn[rt]);
		return ;
	}
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
	pushup(rt);
}

void update(int p, int q, int l, int r, int rt)
{
	if(l==r){
		maxn[rt] = q;
		return ;
	}
	int m = (l + r) >> 1;
	if(p<=m)
		update(p, q, lson);
	else
		update(p, q, rson);
	pushup(rt);
}

int query(int L,int R,int l,int r,int rt) {
	if (L <= l && r <= R) {
		return maxn[rt];
	}
	int m = (l + r) >> 1;
	int ret = 0;
	if (L <= m) ret = max(ret , query(L , R , lson));
	if (R > m) ret = max(ret , query(L , R , rson));
	return ret;
}

int main()
{
	int n, m;

	while (~scanf("%d%d",&n,&m)) {
		build(1 , n , 1);
		while (m --) {
			char op[2];
			int a , b;
			scanf("%s%d%d",op,&a,&b);
			if (op[0] == 'Q') printf("%d\n",query(a , b , 1 , n , 1));
			else update(a , b , 1 , n , 1);
		}
	}

	return 0;
}
//*/

/*         515MS	2280K	1150 B	C++
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define max(a,b) a>b?a:b 
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
const int maxn = 222222;
int MAX[maxn<<2];
void PushUP(int rt) {
	MAX[rt] = max(MAX[rt<<1] , MAX[rt<<1|1]);
}
void build(int l,int r,int rt) {
	if (l == r) {
		scanf("%d",&MAX[rt]);
		return ;
	}
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
	PushUP(rt);
}
void update(int p,int sc,int l,int r,int rt) {
	if (l == r) {
		MAX[rt] = sc;
		return ;
	}
	int m = (l + r) >> 1;
	if (p <= m) update(p , sc , lson);
	else update(p , sc , rson);
	PushUP(rt);
}
int query(int L,int R,int l,int r,int rt) {
	if (L <= l && r <= R) {
		return MAX[rt];
	}
	int m = (l + r) >> 1;
	int ret = 0;
	if (L <= m) ret = max(ret , query(L , R , lson));
	if (R > m) ret = max(ret , query(L , R , rson));
	return ret;
}
int main() {
	int n , m;
	while (~scanf("%d%d",&n,&m)) {
		build(1 , n , 1);
		while (m --) {
			char op[2];
			int a , b;
			scanf("%s%d%d",op,&a,&b);
			if (op[0] == 'Q') printf("%d\n",query(a , b , 1 , n , 1));
			else update(a , b , 1 , n , 1);
		}
	}
	return 0;
}
//*/