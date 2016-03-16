/*      Runtime Error
//       2832K	250MS	C++	2152B
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

const int N = 8005;

struct seg{
	int x, y1, y2;
};
seg mp[N];

bool cmp(const seg &a, const seg &b){
	if(a.x==b.x){
		if(a.y1==b.y1)   return a.y2<b.y2;
		return a.y1<b.y1;
	}
	return a.x<b.x;
}

#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
int cover[N<<4];          // -1为未赋值，-2为混合色
vector<int> vec[N];

void build(int l, int r, int rt){
	cover[rt] = -1;
	if(l==r)   return ;
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
}

void pushdown(int rt){
	if(cover[rt]!=-2){
		cover[rt<<1] = cover[rt<<1|1] = cover[rt];
	}
}

void pushup(int rt){
	if(cover[rt<<1] == cover[rt<<1|1])
		cover[rt] = cover[rt<<1];
	else   cover[rt] = -2;
}

void update(int L, int R, int p, int l, int r, int rt){
	if(L<=l && r<=R && cover[rt]!=-2){  //不能是混色，否则继续下去
		if(cover[rt]!=-1)
			vec[cover[rt]].push_back(p);
		cover[rt] = p;
		return ;
	}
	pushdown(rt);
	int m = (l + r) >> 1;
	if(L<=m)   update(L, R, p, lson);
	if(m<R)    update(L, R, p, rson);
	pushup(rt);
}

int main()
{
	int tc, n;
	int i, j, k;
	int a, b, c;
	int ans;

	scanf("%d", &tc);

	while(tc--){
		scanf("%d", &n);
		for(i=0; i<n; i++){
			scanf("%d %d %d", &a, &b, &c);
			mp[i].x = c,   mp[i].y1 = a,   mp[i].y2 = b;
		}

		sort(mp, mp+n, cmp);
		
		//build(1, N, 1);    成段更新不用build，直接设置cover[1] = -1即可
		cover[1] = -1;
		for(i=1; i<=n; i++){
			vec[i].clear();
			update(mp[i-1].y1*2+1, mp[i-1].y2*2+1, i, 1, N<<1, 1);
		}

		vector<int>::iterator it;
		for(i=1; i<=n; i++){
			sort(vec[i].begin(), vec[i].end());
			it = unique(vec[i].begin(), vec[i].end());
			vec[i].resize( it - vec[i].begin());
		}

		//for(i=1; i<n; i++){
		//	int l = vec[i].size();
		//	for(j=0; j<l; j++){
		//		cout << vec[i][j] << " " ;
		//	}
		//	cout << endl;
		//}

        ans = 0;
		for(i=1; i<n; i++){
			int len = vec[i].size();
			for(j=0; j<len-1; j++){
				for(k=j+1; k<len; k++){
					int a = vec[i][j];
					int b = vec[i][k];
					if( binary_search(vec[a].begin(), vec[a].end(), b))
						ans++;
				}	
			}
		}

		printf("%d\n", ans);
		
	}

	return 0;
}
//*/


//   2840K	235MS	C++	1881B
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

const int N = 8005;

struct seg{
	int x, y1, y2;
};
seg mp[N];

bool cmp(const seg &a, const seg &b){
	if(a.x==b.x){
		if(a.y1==b.y1)   return a.y2<b.y2;
		return a.y1<b.y1;
	}
	return a.x<b.x;
}

#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
int cover[N<<4];          // -1为未赋值，-2为混合色
vector<int> vec[N];

void pushdown(int rt){
	if(cover[rt]){
		cover[rt<<1] = cover[rt<<1|1] = cover[rt];
		cover[rt] = 0;
	}
}

void pushup(int rt){
	if(cover[rt<<1]==cover[rt<<1|1])
		cover[rt] = cover[rt<<1];
	else cover[rt] = 0;
}

void update(int L, int R, int p, int l, int r, int rt){
	int m;
	if(L<=l && r<=R && cover[rt]){  //不能是混色，否则继续下去
		vec[cover[rt]].push_back(p);
		cover[rt] = p;
		return ;
	}
	pushdown(rt);
	m = (l + r) >> 1;
	if(L<=m)   update(L, R, p, lson);
	if(m<R)    update(L, R, p, rson);
	pushup(rt);
}

int main()
{
	int tc, n;
	int i, j, k;
	int a, b, c;
	int ans;

	scanf("%d", &tc);

	while(tc--){
		scanf("%d", &n);
		for(i=0; i<n; i++){
			scanf("%d %d %d", &a, &b, &c);
			mp[i].x = c,   mp[i].y1 = a,   mp[i].y2 = b;
		}

		sort(mp, mp+n, cmp);
		
		cover[1] = 1<<30;   // 不能是0 （更新不了cover）或者1~n
		for(i=1; i<=n; i++){
			vec[i].clear();
			update(mp[i-1].y1*2+1, mp[i-1].y2*2+1, i, 1, N<<1, 1);
		}

		vector<int>::iterator it;
		for(i=1; i<=n; i++){
			sort(vec[i].begin(), vec[i].end());
			it = unique(vec[i].begin(), vec[i].end());
			vec[i].resize( it - vec[i].begin());
		}


        ans = 0;
		for(i=1; i<n; i++){
			int len = vec[i].size();
			for(j=0; j<len-1; j++){
				for(k=j+1; k<len; k++){
					int a = vec[i][j];
					int b = vec[i][k];
					if( binary_search(vec[a].begin(), vec[a].end(), b))
						ans++;
				}	
			}
		}

		printf("%d\n", ans);
		
	}

	return 0;
}




/*  3300K	313MS	C++	2746B
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include <string.h>
#include <string>
#include <algorithm>
#define MID(x,y) ( ( x + y ) >> 1 )
#define L(x) ( x << 1 )
#define R(x) ( x << 1 | 1 )
#define FOR(i,s,t) for(i=(s); i<(t); i++)
#define BUG puts("here!!!")
#define STOP system("pause")
#define file_r(x) freopen(x, "r", stdin)
#define file_w(x) freopen(x, "w", stdout)

using namespace std;

const int MAX = 8010*2;
struct Tnode{				// 一维线段树 
    int l,r,id;
    int len() { return r - l;}
    int mid() { return MID(l,r);}
    bool in(int ll,int rr) { return l >= ll && r <= rr; }
    void lr(int ll,int rr){ l = ll; r = rr;}
};
Tnode node[MAX<<2];
vector< vector<int> > v(MAX/2);
vector< int >::iterator it;

void Build(int t,int l,int r)
{
	node[t].lr(l,r);
	node[t].id = -1;			//未被赋值为-1，混合色为-2 
	if( node[t].len() == 1 )
		return ;
	int mid = MID(l,r);
	Build(L(t),l,mid);
	Build(R(t),mid,r);
}
void Updata_id(int t)
{
	if( node[L(t)].id == node[R(t)].id && node[L(t)].id != -2 )
		node[t].id = node[L(t)].id;
	else
		node[t].id = -2;
}

void Push_down(int t)
{
	if( node[t].len() == 1 )
		return ;
	if( node[t].id >= 0 )
		node[L(t)].id = node[R(t)].id = node[t].id;
}
void Updata(int t,int l,int r,int id)
{
	Push_down(t);
	if( node[t].in(l,r) && node[t].id != -2 )
	{
		if( node[t].id != -1 )
			v[node[t].id].push_back(id);
		node[t].id = id;
		return ;
	}
	if( node[t].len() == 1 ) return ;
	int mid = node[t].mid();
	if( l < mid ) Updata(L(t),l,r,id);
	if( r > mid ) Updata(R(t),l,r,id);
	Updata_id(t);
}

struct NODE{
	int x, y, id, xx;	// x < y 
	void get()
	{
		scanf("%d%d%d", &x, &y, &xx);
	}
};
NODE a[MAX/2];
bool cmp(NODE a,NODE b)
{
	return a.xx < b.xx;
}
int solve(int n)
{
	int i, k, j;
	int sum = 0;
	Build(1, 0, MAX);

	FOR(i, 0, n)
	{
		v[i].clear();
		Updata(1, a[i].x*2, a[i].y*2+1, a[i].id);
	}
	
	FOR(i, 0, n)
	{
		sort(v[i].begin(), v[i].end());
		it = unique(v[i].begin(), v[i].end());
		v[i].resize( it - v[i].begin());
	}
	
	FOR(i, 0, n)
	{
		int len = v[i].size();
		FOR(k, 0, len)
		{
			FOR(j, k+1, len) // 经测试，根据POJ的数据，最内层这个计算量不到50w 
			{				
				int a = v[i][k];
				int b = v[i][j];
				if( binary_search(v[a].begin(), v[a].end(), b) )
					sum++;
			}
		}
	}
	return sum;		
}
		
int main()
{
	int ncases, n;
	int i;
	
	scanf("%d", &ncases);
	
	while( ncases-- )
	{
		scanf("%d", &n);
		FOR(i, 0, n)
			a[i].get();

		sort(a, a+n, cmp);
		
		FOR(i, 0, n)
			a[i].id = i;
		int ans = solve(n);
		
		printf("%d\n", ans);
	}
			
	return 0;
}
//*/
