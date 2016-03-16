/*    78MS	332K	1172 B	C++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 105;
struct Good{
	int id, p, v;
	bool operator < (const Good &a)const{
		return id<a.id;
	}
}goods[N];

int dp[2][10010];

int main()
{
	int n, m, k;
	int i, j, l;
	int p;

	while(scanf("%d %d %d", &n, &m, &k)!=EOF){
		for(i=0; i<n; i++){
			scanf("%d %d %d", &goods[i].id, &goods[i].p, &goods[i].v);
		}
		sort(goods, goods+n);

		int now = 0, now1 = 0;
		memset(dp, -1, sizeof(dp));
		dp[0][0] = 0;
		l = 0;
		for(i=1; i<=k; i++){
			l = l^1;
			memset(dp[l], -1, sizeof(dp[l]));
			for(now1=now; goods[now1].id==i; now1++){
				p = goods[now1].p;
				for(j=m; j>=p; j--){
					if(dp[l][j-p]!=-1 && dp[l][j]<dp[l][j-p]+goods[now1].v)
						dp[l][j] = dp[l][j-p]+goods[now1].v;
					if(dp[l^1][j-p]!=-1 && dp[l][j]<dp[l^1][j-p]+goods[now1].v)
						dp[l][j] = dp[l^1][j-p]+goods[now1].v;
				}
			}
			now = now1;
		}

		int ans = -1;
		for(i=1; i<=m; i++){
			if(ans<dp[l][i]){
				ans = dp[l][i];
			}
		}
		if(ans<0)
			printf("Impossible\n");
		else
			printf("%d\n", ans);
	}

	return 0;
}
//*/
/*
5 100 3
1 4 6
2 5 7
3 4 99
1 55 77
2 44 66
*/



/*    93MS	684K	1146 B	C++
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

struct node {
	int a,b,c;
}shoe[101];

int dp[11][10001];
bool cmp(node a,node b){return a.a<b.a;}
int main(void) 
{
	int n,m,k;
	int i, j;
	while(scanf("%d%d%d",&n,&m,&k)!=EOF) {
		for(i=0;i<n;i++)
			scanf("%d%d%d",&shoe[i].a,&shoe[i].b,&shoe[i].c);
		sort(shoe,shoe+n,cmp);
		memset(dp,-1,sizeof(dp));
		dp[0][0]=0;
		for(i=0;i<n;i++) {
			for(j=m;j>=shoe[i].b;j--) {   //  i-1 传递了至少一个给 i
				if(dp[shoe[i].a][j-shoe[i].b]!=-1 && dp[shoe[i].a][j-shoe[i].b]+shoe[i].c>dp[shoe[i].a][j]) {
					dp[shoe[i].a][j] = dp[shoe[i].a][j-shoe[i].b] + shoe[i].c;
				}
				if(dp[shoe[i].a-1][j-shoe[i].b]!=-1 && dp[shoe[i].a-1][j-shoe[i].b]+shoe[i].c>dp[shoe[i].a][j]) {
					dp[shoe[i].a][j] = dp[shoe[i].a-1][j-shoe[i].b] + shoe[i].c;
				}
			}
		}
		int max=-1;
		for(i=0;i<=m;i++) {
			if(dp[k][i]>max)max=dp[k][i];
		}
		if(max<0)
			puts("Impossible");
		else 
			printf("%d\n",max);
	}
	return 0;
}
//*/



//*   31MS	688K	962 B	C++

#include<stdio.h>
#include<string.h>
#define max(x,y) (x)>(y)?(x):(y)
#define min(x,y) (x)<(y)?(x):(y)
#define INF 0x7fffffff
#define MAXN 10005

int N, V, K;
int f[105][MAXN];
int c[105], w[105], n[105];

void init_full()
{
 int i, j;
 for(i=1;i<=K;i++)
  for(j=0;j<=V;j++)
   f[i][j] = -INF;
}

int main()
{
 while(scanf("%d %d %d",&N,&V,&K)!=EOF)
 {
  init_full();
  
  int i, j, k;
  for(i=1;i<=N;i++)
   scanf("%d %d %d",&n[i],&c[i],&w[i]);
  
  for(k=1;k<=K;k++)
   for(i=1;i<=N;i++)//每组物品可以放多个，如果每组物品只能放一个的话，2、3循环对调 
   {
    if(n[i]==k)
    {
     for(j=V;j>=c[i];j--)
     {
      f[k][j] = max(f[k][j], f[k][j-c[i]]+w[i]);
      //当前品牌数目的前提之下取最大的值
      f[k][j] = max(f[k][j], f[k-1][j-c[i]]+w[i]);
      //在比当前数目小的基础之上放一个另外品     
     }
    }
   }
   if(f[K][V] < 0)
    puts("Impossible");
   else printf("%d\n",f[K][V]);
 }
 return 0;
 }
//*/