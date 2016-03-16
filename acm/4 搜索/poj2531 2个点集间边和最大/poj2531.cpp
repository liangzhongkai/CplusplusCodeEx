/*
#include<iostream>

using namespace std;

int mp[25][25];
bool vis[25];
int n;
int mmax = 0;

void dfs(int node, int level, int sum){
	if(level>=n){
		if(n%2==0){
			sum += mp[node][1];
		}
		//cout << sum << " " << node << endl;
		if(sum>=mmax)
			mmax = sum;
	}
	else{
		for(int i=1; i<=n; i++){
			if(!vis[i] && mp[node][i]){
				vis[i] = true;
				dfs(i, level+1, sum+mp[node][i]);
				vis[i] = false;
			}
		}
	}
}

int main()
{
	int i, j;

	cin >> n;
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			cin >> mp[i][j];
		}
	}

	memset(vis, false, sizeof(vis));
	vis[1] = true;
	dfs(1, 1, 0);
	cout << mmax;

	return 0;
}
//*/

/*
4
0 20 30 0
20 0 50 10
30 50 0 10
0 10 10 0

5
0 50 0 0 10
50 0 40 0 0
0 40 0 30 0
0 0 30 0 20
10 0 0 20 0
*/


/*  168K	141MS	C++	699B

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int c[22][22], n, ans, set[22];

void DFS(int id, int sum)
{
    int i;

    set[id] = 1;
    for (i = 0; i < n; i++){
        if (set[i] == 1)
            sum -= c[id][i];
        else
			sum += c[id][i];
    }
    if (sum > ans) ans = sum;

    for (i = id+1; i < n; i++){
        DFS(i, sum);
        set[i] = 0;
    }
}

int main()
{
    int i, j;

    scanf ("%d", &n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
             scanf ("%d", &c[i][j]);
    memset (set, 0, sizeof (set));
    ans = 0;
    DFS(0, 0);
    printf ("%d", ans);

    return 0;
}
//*/

/*     5300K	157MS	C++	789B
#include<stdio.h>

const int N=21;
int n,map[N][N],ans,f[1<<20];
bool v[1<<20];

inline bool find(int x,int s){
	return s>>(x-1)&1;
}

inline int max(int a,int b){
	if(a>b)
		return a;
	return b;
}

int main()
{
	int i;
	  //freopen("poj2531.in","r",stdin);
	  //freopen("poj2531.out","w",stdout);
	  scanf("%d",&n);
	  for(i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		scanf("%d",&map[i][j]);

	  int s=(1<<n)-1;
	  for(i=1;i<s;i++)
	  if(!v[i])
	  {
			v[i]=1;
			v[i^s]=1;
			int j=1;

			for(;j<=n;j++)
			  if(find(j,i))
				break;

			f[i]=f[i-(-i&i)];

			for(int k=1;k<=n;k++)
			  if(find(k,i-(-i&i)))
				 f[i]-=map[j][k];
			  else
				 f[i]+=map[j][k];

			f[i^s]=f[i];
			ans=max(ans,f[i]);
	  }
	  printf("%d",ans);
	  return 0;
}
    
//*/