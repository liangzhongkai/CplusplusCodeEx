//       2406MS	2276K	1012 B	C++
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define min(a,b) a>b?b:a

const int N = 222222;
int maxn[N<<2];
int n, w, k, ans;

void pushup(int rt){
	maxn[rt] = maxn[rt<<1] < maxn[rt<<1|1] ? maxn[rt<<1|1] : maxn[rt<<1];
}

void build(int l, int r, int rt){
	maxn[rt] = w;
	if(l==r) return ;
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
}

void query(int p, int l, int r, int rt){
	if(l==r){
		maxn[rt] -= p;
		ans = l;
		return ;
	}
	int m = (l + r) >> 1;
	if(maxn[rt<<1]>=p)
		query(p, lson);
	else if(maxn[rt<<1|1]>=p)  // 这里其实不用判断也行，因为能进入query的都证明了有一个装得下它的位置了。
		query(p, rson);
	pushup(rt);
}

int main()
{
	freopen("data.txt", "r", stdin);
	int i;
	int a;
	while(~scanf("%d%d%d", &n, &w, &k)){
		if (n > k) n = k;          // 关键1
		build(1, n, 1);
		for(i=0; i<k; i++){
			scanf("%d", &a);
			ans = -1;
			if(a>maxn[1]){
				printf("-1\n");
				continue;
			}
			query(a, 1, n, 1);
			printf("%d\n", ans);
		}
	}

	return 0;
}


/*    2203MS	2296K	1061 B	C++
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define min(a,b) a>b?b:a

const int N = 222222;
int maxn[N<<2];
int n, w, k, ans;

void pushup(int rt){
	maxn[rt] = maxn[rt<<1]<maxn[rt<<1|1]?maxn[rt<<1|1]:maxn[rt<<1];
}

void build(int l, int r, int rt){
	maxn[rt] = w;
	if(l==r) return ;
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
}

int query(int x, int l, int r, int rt){
	if (l == r) {
		maxn[rt] -= x;
		return l;
	}
	int m = (l + r) >> 1;
	int ret = (maxn[rt<<1] >= x) ? query(x , lson) : query(x , rson);
	pushup(rt);
	return ret;
}

int main()
{
	//freopen("data.txt", "r", stdin);
	int i;
	int a;
	while(~scanf("%d%d%d", &n, &w, &k)){
		if (n > k) n = k;          // 关键1
		build(1, n, 1);
		for(i=0; i<k; i++){
			scanf("%d", &a);
			if(a>maxn[1]){
				printf("-1\n");
				continue;
			}
			printf("%d\n", query(a, 1, n, 1));
		}
	}

	return 0;
}
//*/



/*        2265MS	2296K	848 B	C++
#include <cstdio>
#include <algorithm>
using namespace std;
 
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
const int maxn = 222222;
int h , w , n;
int MAX[maxn<<2];

void PushUP(int rt) {
	MAX[rt] = max(MAX[rt<<1] , MAX[rt<<1|1]);
}

void build(int l,int r,int rt) {
	MAX[rt] = w;
	if (l == r) return ;
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
}

int query(int x,int l,int r,int rt) {
	if (l == r) {
		MAX[rt] -= x;
		return l;
	}
	int m = (l + r) >> 1;
	int ret = (MAX[rt<<1] >= x) ? query(x , lson) : query(x , rson);
	PushUP(rt);
	return ret;
}

int main() {
	while (~scanf("%d%d%d",&h,&w,&n)) {
		if (h > n) h = n;
		build(1 , h , 1);
		while (n --) {
			int x;
			scanf("%d",&x);
			if (MAX[1] < x) puts("-1");
			else printf("%d\n",query(x , 1 , h , 1));
		}
	}
	return 0;
}
//*/