// C++ 	10001ms 	236kb   Time Limit Exceeded 
/*
#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

int mp[1005][11];
int t[1005];
bool vis[1005];

int gcd(int a, int b){
	int c;
	if(a<b)  c = a, a = b, b = c;
	if(a==0)  return b;
	while(b!=0)  c = b, b = a%b, a = c;
	return a;
}	

int lcm(int a, int b){
	return a/gcd(a,b)*b;
}

int main()
{
	int tc;
	int n, g;
	int i, j;

	cin >> tc;
	while(tc--){
		g = 1;
		cin >> n;
		for(j=0; j<n; j++){
			cin >> t[j];
			for(i=0; i<t[j]; i++){
				scanf("%d", mp[j]+i);
			}
		}

		int min1, min2;
		int id1, id2;
		int ans1 = n, ans2;
		int key, cnt=-1, ct;
		memset(vis, false, sizeof(vis));
	
		while(1){
			key = 0;  cnt++;
			if(ans1==1)  break;

			g = 1;
			for(i=0; i<n; i++){
				if(!vis[i])
					 g = lcm(g, t[i]);    // C++ 10001ms 236kb Time Limit Exceeded 快了一点
			}

			for(i=0; i<g; i++){
				min1 = min2 = 260;
				id1 = id2 = 260;
				for(j=0; j<n; j++){
					if(!vis[j]){
						if(min1>=mp[j][i%t[j]]){
							min2 = min1;  id2 = id1;
							min1 = mp[j][i%t[j]];  id1 = j;
						}
						else if(min2>mp[j][i%t[j]])
							min2 = mp[j][i%t[j]];  id2 = j;
					}
				}

				//cout << min1 << " " << min2 << endl; 
				if(min1==min2 && min1!=260)   continue;
				else{
					vis[id1] = true;
					ans1--;  ans2 = i;
					key = 1;
				}
			}

			if(key==1) ct = cnt * g;
			if(key==0) break;
		}

		if(ans1==n)   ans2 = 0;
		else   ans2 = ct + ans2 + 1;
		cout << ans1 << " " << ans2 << endl;
		
	}

	return 0;
}
//*/




/*  Time Limit Exceeded 
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;

int mp[1005][11];
int t[1005];
bool vis[1005];

struct point{
	int id, w;
	point(int a, int b):id(a),w(b){}
	point(){}
};
point les[1005];
int len=0;

bool cmp(const point &a, const point &b){
	return a.w<b.w;
}

int gcd(int a, int b){
	int c;
	if(a<b)   c = a, a = b, b = c;
	if(a==0)   return b;
	while(b!=0)   c = b, b = a%b, a = c;
	return a;
}

int lcm(int a, int b){
	return a/gcd(a, b)*b;
}

int main()
{
	int tc;
	int n, g;
	int i, j;
	int ct, dt;
	int ans1, ans2, key, id;

	scanf("%d", &tc);
	while(tc--){
		scanf("%d", &n);
		for(i=0; i<n; i++){
			scanf("%d", t+i);
			for(j=0; j<t[i]; j++){
				scanf("%d", mp[i]+j);
			}
		}

		ans1 = n; ans2 = 0; ct = dt = 0;
		memset(vis, false, sizeof(vis));
		while(1){
			if(ans1==1)   break;

			g = 1;
			for(i=0; i<n; i++){
				if(!vis[i]){
					g = lcm(g, t[i]);
				}
			}

			key = 0;
			for(i=0; i<g; i++){
				len = 0;
				for(j=0; j<n; j++){
					if(!vis[j])
						les[len++] = point(j, mp[j][i%t[j]]);
				}
				sort(les, les+len, cmp);

				for(j=0; j<len-1; j++){
					if(les[j].w==les[j+1].w)   break;
					id = i, ans1--, key = 1;
					vis[les[j].id] = true;
				}
			}

			if(key){   ct += g, dt = g - id - 1;}
			else   break;
		}

		ans2 = ct - dt;
		if(ans1==n)   ans2 = 0;
	    if(ans1==1)   ans2++;
		cout << ans1 << " " << ans2 << endl;
	}

	return 0;
}

/*
2
4
4 7 1 2 9
1 2
2 7 1
1 2
4
6 7 2 5 7 2 8
5 4 3 3 6 1
2 2 8
1 7
*/




//*   C++ 	2180s 	2936kb
#include <iostream>
#include <algorithm>

using namespace std;

//映射二分堆(mapped)
//可插入,获取并删除任意元素,复杂度均O(logn)
//插入时提供一个索引值,删除时按该索引删除,获取并删除最小元素时一起获得该索引
//索引值范围..MAXN-1,不能重复,不负责维护索引的唯一性,不在此返回请另外映射
//主要用于图论算法,该索引值可以是节点的下标
//可更改元素类型,修改比较符号或换成比较函数
//n是堆中元素个数，h[1]是最小元素，ind[1]是最小元素下标，使用时要注意判断堆是否为空

#define MAXN 1010
#define _cp(a,b) ((a)<(b))
typedef int elem_t;

struct heap{
	elem_t h[MAXN];
	int ind[MAXN],map[MAXN],n,p,c;
	void init(){n=0;}
	void ins(int i,elem_t e){
		for (p=++n;p>1&&_cp(e,h[p>>1]);h[map[ind[p]=ind[p>>1]]=p]=h[p>>1],p>>=1);
			h[map[ind[p]=i]=p]=e;
	}
	int del(int i,elem_t& e){
		 i=map[i];if (i<1||i>n) return 0;
		 for (e=h[p=i];p>1;h[map[ind[p]=ind[p>>1]]=p]=h[p>>1],p>>=1);
		 for (c=2; c<n&&_cp(h[c+=(c<n-1&&_cp(h[c+1],h[c]))],h[n]); h[map[ind[p]=ind[c]]=p]=h[c],p=c,c<<=1);
	     h[map[ind[p]=ind[n]]=p]=h[n];n--;
		 return 1;
	}
	int delmin(int& i,elem_t& e){
		if (n<1) return 0;i=ind[1];
		for (e=h[p=1],c=2;c<n&&_cp(h[c+=(c<n-1&&_cp(h[c+1],h[c]))],h[n]);h[map[ind[p]=ind[c]]=p]=h[c],p=c,c<<=1);
	    h[map[ind[p]=ind[n]]=p]=h[n];n--;return 1;
	}
	int getmin(elem_t& e) {
		 e = h[1]; return ind[1];
	}
};

long long getGcd(long long a, long long b)
{
	long long t;
	while (b) {
	   t = a;
	   a = b;
	   b = t % a;
	}
	return a;
}


int m[1010][20], ti[1010], indexs[10], l;
heap cow[15][15];

int main()
{
	int cases, n, count, mint, mini, c, e, temp, k, ln;
	scanf("%d", &cases);
	while (cases--) {
		   scanf("%d", &n);

		   for (int i = 0; i < n; i++) {
				scanf("%d", ti + i);
				for (int j = 0; j < ti[i]; j++)
					 scanf("%d", &m[i][j]);
		   }

		   for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
			 cow[i][j].init();

		   for (int i = 0; i < n; i++) {
			for (int j = 0; j < ti[i]; j++) {
			 cow[ti[i]][j].ins(i, m[i][j]);
			}
		   }

		   long long t = 1;
		   for (int i = 0; i < 11; i++)
			if (cow[i][0].n)
			 t = t * i / getGcd(t, i);

		   l = -1;
		   ln = 0;
		   for (k = 0; k <= t * n; k++) {
			if (!n) break;
			if (k % t == 0) {
			 if (ln == n) break;
			 ln = n;
			}

			mint = 1000;
			for (int j = 1; j < 11; j++)
			 if (cow[j][k%j].n && mint > cow[j][k%j].h[1]) {
			  mint = cow[j][k%j].h[1];
			  mini = j;
			 }

			count = 0;
			for (int j = 1; j < 11; j++)
			 if (cow[j][k%j].n && mint == cow[j][k%j].h[1])
			  count++;

			if (count > 1) continue;

			cow[mini][k%mini].delmin(c, e);
			if (e == cow[mini][k%mini].h[1] && cow[mini][k%mini].n)
				 cow[mini][k%mini].ins(c, e);
			else {
				 n--;
				 l = k;
				 for (int i = 0; i < mini; i++)
				  if (i != k%mini)
				   cow[mini][i].del(c, e);
			}
	   }
	   printf("%d %d\n", n, l + 1);
	}

}
//*/


/*   Time Limit Exceeded 
#include<stdio.h>
#include<string.h>
#define MAXD 1010
#define INF 1000000000
int N, T, t[MAXD], d[MAXD][20], U[MAXD], D[MAXD], st[MAXD];

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

void init()
{
    int i, j, k;
    scanf("%d", &N);
    for(i = 1; i <= N; i ++)
    {
        scanf("%d", &t[i]);
        for(j = 0; j < t[i]; j ++)
            scanf("%d", &d[i][j]);
    }
    for(i = 0; i <= N; i ++)
    {
        D[i] = i + 1;
        U[i + 1] = i;
    }
    D[N] = 0;
    memset(st, 0, sizeof(st));
    T = 1;
    for(i = 1; i <= N; i ++)
    {
        if(T < t[i])
            k = gcd(t[i], T);
        else
            k = gcd(T, t[i]);
        T = T * t[i] / k;
    }
}

void solve()
{
    int i, j, k, cur, min, num, flag, a, p, sum;
    num = min = 0;
    for(p = 0;; p ++)
    {
        flag = 0;
        for(cur = 1; cur <= T; cur ++)
        {
            a = INF;
            for(i = D[0]; i != 0; i = D[i])
            {
                if(d[i][st[i]] < a)
                {
                    a = d[i][st[i]];
                    k = i;
                    sum = 1;
                }
                else if(d[i][st[i]] == a)
                    sum ++;
                st[i] = (st[i] + 1) % t[i];
            }
            if(sum == 1)
            {
                flag = 1;
                U[D[k]] = U[k];
                D[U[k]] = D[k];
                min = p * T + cur;
                num ++;
            }
        }
        if(!flag)
            break;
    }
    printf("%d %d\n", N - num, min);
}

int main()
{
    int test;
    scanf("%d", &test);
    while(test --)
    {
        init();
        solve();
    }
    return 0;
}
//*/