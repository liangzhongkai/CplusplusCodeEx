#include<iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define max(a,b) a>b?a:b

int n, b, f;
const int N = 111111;
int msum[N], lsum[N], rsum[N];
int cover[N];

struct node{
	int x, y;
};

void build(int l, int r, int rt){
	msum[rt] = lsum[rt] = rsum[rt] = r - l + 1;
	if(l==r)   return;
	int m = (l + r) >> 1 ;
	build(lson);
	build(rson);
}

void pushdown(int rt, int m){
	if(cover[rt]!=-1){
		cover[rt<<1] = cover[rt<<1|1] = cover[rt];
		msum[rt<<1] = lsum[rt<<1] = rsum[rt<<1] = cover[rt]?0:(m-(m>>1));
		msum[rt<<1|1] = lsum[rt<<1|1] = rsum[rt<<1|1] = cover[rt]?0:(m>>1);
		cover[rt] = -1;
	}
}

void pushup(int rt, int m){
	if(cover[rt<<1]==cover[rt<<1|1])
		cover[rt] = cover[rt<<1];
	else
		cover[rt] = -1;
	lsum[rt] = lsum[rt<<1]==(m-(m>>1))?(lsum[rt<<1]+lsum[rt<<1|1]):lsum[rt<<1];
	rsum[rt] = rsum[rt<<1|1]==(m>>1)?(rsum[rt<<1|1]+rsum[rt<<1]):rsum[rt<<1|1];
	msum[rt] = max(msum[rt<<1], msum[rt<<1|1]);
	msum[rt] = max(msum[rt], rsum[rt<<1]+lsum[rt<<1|1]);
}

void update(int	L, int R, int p, int l, int r, int rt){
	if(L<=l && r<=R){
		cover[rt] = p;
		msum[rt] = rsum[rt] = lsum[rt] = p?0:r-l+1;
		return;
	}
	pushdown(rt, r-l+1);
	int m = (l + r) >> 1;
	if(L<=m)   update(L, R, p, lson);
	if(R>m)   update(L, R, p, rson);
	pushup(rt, r-l+1);
}

int query(int p, int l, int r, int rt){
	if(l==r)   return l;
	pushdown(rt, r-l+1);
	int m = (r + l) >> 1;
	if(msum[rt<<1]>=p)
		return query(p, lson);
	else if(rsum[rt<<1]+lsum[rt<<1|1]>=p)
		return m - rsum[rt<<1] + 1;
	else 
		return query(p, rson);
}

int main()
{
	freopen("in.txt", "r", stdin);
	int m;
	int i;
	int x, y;
	int maxx;
	node tmp;
	vector<node> vec;

	scanf("%d %d %d", &n, &b, &f);

	scanf("%d", &m);
	build(1, n, 1);
	cover[1] = 0;
	maxx = 0;
	for(i=0; i<m; i++){
		scanf("%d %d", &x, &y);
		if(x==1){
			if(msum[1]>=y+b+f){
				
			}
			else if(msum[1]>=y+f){
				x = query(y+f, 1, n, 1);
				if(maxx<x){
					update(x, x+y+f-1, 1, 1, n, 1);
					printf("%d\n", x+f);
					maxx = x+f;
					tmp.x = x;   tmp.y = x+y+f-1;
					vec.push_back(tmp);
				}
			}
			else if(msum[1]>=y){
				x = query(y, 1, n, 1);
				if(msum[1]==n){
					update(x, x+y-1, 1, 1, n, 1);
					printf("0\n");
					tmp.x = x;  tmp.y = x+y-1;
					if(x>maxx)   maxx = x;
					vec.push_back(tmp);
				}
				else{
					printf("-1\n");
				}
			}
			else{
				printf("-1\n");
			}
		}
		else{
			update(vec[y-1].x, vec[y-1].y, 0, 1, n, 1);
			vec.erase(vec.begin()+y);
		}
	}
		 
	return 0;
}
