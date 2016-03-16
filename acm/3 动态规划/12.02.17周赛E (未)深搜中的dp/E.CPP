/*
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>

using namespace std;

struct point
{
	int x, edge;
}mp[10001];

vector<int> vec[10001]; 
bool vis[10001];

bool cmp(const point &a, const point &b)
{
	return a.edge>b.edge;
}

int dfs(int n)
{
	int a = 0;
	if(!vis[n])
	{
		vis[n] = true;

		for(int i=0; i<vec[n].size(); i++)
		{
			if(!vis[vec[n][i]] && vec[vec[n][i]].size()==1)
			{
				vis[vec[n][i]] = true;
				return 1;
			}
			else if(!vis[vec[n][i]] && vec[vec[n][i]].size()==2)
			{
				vis[vec[n][i]] = true;
				return dfs(vec[n][i]);
			}
			else if(!vis[vec[n][i]] && vec[vec[n][i]].size()>2)
			{
				vis[vec[n][i]] = true;
				a += dfs(vec[n][i]);
			}
		}
	}
	return a;
}

int main()
{
	int n;   // 10000
	int i;
	cin >> n;
	int a, b;

	for(i=1; i<=n; i++)
	{
		mp[i].x = i;
		mp[i].edge = 0;
	}

	for(i=0; i<n-1; i++)
	{
		cin >> a >> b;
		mp[a].edge++;
		mp[b].edge++;
		vec[a].push_back(b);
		vec[b].push_back(a);
	}


	sort(mp+1, mp+n+1, cmp);

	memset(vis, false, sizeof(vis));

	int ans = 0;
	for(i=1; i<=n; i++)
	{
		if(!vis[mp[i].x])
		{
			vis[mp[i].x] = true;
			for(int j=0; j<vec[mp[i].x].size(); j++)
				if(vec[vec[mp[i].x][j]].size()>1 )
					ans += dfs(vec[mp[i].x][j]);
		}

	
	}

	cout << ans << endl;

	return 0;
}
//*/



//*             516K	47MS	C++	2221B
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int vd[10001];
int n,m;
int arm[20001][2];//记录边
int index[10001];//记录i节点的邻接边在arm里的索引
int num[10001][3];//记录以i为根的树，选改节点与不选该节点的最小数目

int cmp(const void *a,const void *b)
{
    int *x=(int *)a;
    int *y=(int *)b;
    return x[0]-y[0];
}

int min(int a,int b)
{
    if(a<b)
        return a;
    return b;
}

void init()
{
    int i,j;
    scanf("%d",&n);
    for(i=0;i<n-1;i++)
	{
        int a,b;
        scanf("%d%d",&a,&b);
        arm[2*i][0]=a;
        arm[2*i][1]=b;
        arm[2*i+1][0]=b;
        arm[2*i+1][1]=a;
    }
    m=2*n-2;                                     // 总共m个度  总边数的2倍
    memset(vd,0,sizeof(vd));
    memset(index,-1,sizeof(index));
    qsort(arm,m,sizeof(int)*2,cmp);
    for(i=0,j=0;i<m;i++)
	{
        if(i==0||arm[i][0]!=arm[i-1][0])
		{
            index[arm[i][0]]=i;                  // 这个点的边数（要间接求出）
        }
    }
}
void dfs(int v)
{
    int i;
    vd[v]=1;
    int isleaf=1;
	int sum0=0;
    int sum1=0;
    int sum2=0;
    int reduce=99999999;

    if(index[v]!=-1)                           // 1 ~ n
	{
        for(i=index[v]; arm[i][0]==v; i++)     // index[v]为该点的第一条边是总边数的第几条？
		{
            if(vd[arm[i][1]]==0)
			{
                dfs(arm[i][1]);
                isleaf=0;
                sum1+=min(min(num[arm[i][1]][0],num[arm[i][1]][1]),num[arm[i][1]][2]);
                sum2+=num[arm[i][1]][0];
                //统计sum0=================================================reduce 始终>=0

                sum0+=min(num[arm[i][1]][0],num[arm[i][1]][1]);//先取最小的和
                if(num[arm[i][1]][1]-num[arm[i][1]][0]<reduce) //求需要在sum0上添加的最小值
				{
                    if(num[arm[i][1]][1]-num[arm[i][1]][0]>=0)//小于当前最小值且非负，更新之
                        reduce=num[arm[i][1]][1]-num[arm[i][1]][0];
                    else//取到=1时的了，不用reduce了
                        reduce=0;
                }

                //==========================================================

            }
        }
    }
    if(isleaf)
	{
        num[v][1]=1;
        num[v][0]=1;
        num[v][2]=0;
    }
	else
	{
        num[v][1]=1+sum1;
        num[v][0]=sum0+reduce;
        num[v][2]=sum2;
    }
}

int main()
{
    int r;
    init();
    dfs(1);
    r=min(num[1][0],num[1][1]);
    printf("%d\n",r);
    scanf("%d",&r);
    return 0;
}

//*/

/*        1156K	79MS	C++	1746B

#include<iostream>
#include<vector>
using namespace std;

const int mmax=10000000;
int dp[10005][3];
int n;
vector<int> temp[10005];
vector<int> a[10005];
bool use[10005];

void dfs(int i)
{
     int j,l=temp[i].size();
     for(j=0;j<l;j++)
	 {
                      if(!use[temp[i][j]])
					  {
                            use[temp[i][j]]=true;
                            a[i].push_back(temp[i][j]);
                            dfs(temp[i][j]);
                      }
     }
}

void build()
{
     use[1]=true;
     dfs(1);
}

inline int min(int i,int j)
{
       if(i>j)return j;
       return i;
}
void cal(int i)
{
     int j 
		 ,l=a[i].size(),s1=0,s2=0;
     if(l==0)
	 {
              dp[i][0]=0;
              dp[i][1]=1;
              dp[i][2]=1;
              return ;
     }
     for(j=0;j<l;j++)
	 {
                      s1+=dp[a[i][j]][1];
                      s2+=min(dp[a[i][j]][0],dp[a[i][j]][1]);
     }
     dp[i][2]=min(dp[i][2],s2+1);
     dp[i][1]=min(dp[i][1],s2+1);
     for(j=0;j<l;j++)   dp[i][1]=min(dp[i][1],s1-dp[a[i][j]][1]+dp[a[i][j]][2]);
     dp[i][0]=s1;
}
void dfs2(int i)
{
     int j,l=a[i].size();
     for(j=0;j<l;j++)dfs2(a[i][j]);
     cal(i);
}
void solve()
{
     build();
     dfs2(1);
     printf("%d\n",dp[1][1]);
}
void input()
{
     scanf("%d",&n);
     int i,x,y;
     for(i=1;i<n;i++)
	 {
                      scanf("%d%d",&x,&y);
                      temp[x].push_back(y);
                      temp[y].push_back(x);
                      dp[i][0]=dp[i][1]=dp[i][2]=mmax;
      }
     dp[n][0]=dp[n][1]=dp[n][2]=mmax;
}

int main()
{
    input();
    solve();
    //system("pause");
    return 0;
}
//*/




/*
#include<stdio.h>
#include<string.h>
int l[1508];
int s[1508];
int vis[1508];
int map[1508][16];
int n;

int Dfs(int u)
{
	int place=0,i,r=0;
	vis[u]=1;
	for(i=0;i<l[u];i++){
		if(vis[map[u][i]]) continue;
		r+=Dfs(map[u][i]);
		if(!s[map[u][i]])
			place=1;
	}
	return r+(s[u]=place);
}
int main()
{
	int i,j,u,v,e;

	while(~scanf("%d",&n)){

		memset(l,0,sizeof(l));
		memset(s,0,sizeof(s));
		memset(vis,0,sizeof(vis));

		for(i=0;i<n;i++){
			scanf("%d",&u);
			scanf(":(%d)",&e);

			for(j=0;j<e;j++){
				scanf("%d",&v);
				map[u][l[u]++]=v;
				map[v][l[v]++]=u;
			}

		}
		printf("%d\n",Dfs(0));
	}
	return 0;
}


//*/


/*   856K	63MS	C++	1449B
//题目大意：给定一棵树，求最小支配集。就是说用最少的点覆盖这棵树所有的边。
//解题思路：发现，我的想法有点奇葩，和大家的一般思路不太一样。我对每个点设立了三种状态：
//          0表示这个点没有覆盖正期待着被父亲节点覆盖，
//          1表示在当前节点就是属于支配集，
//          2表示当前节点被他的儿子覆盖。                                                         
//状态转移：    dp[root][0]=sum{dp[son][2]};
//　　　　　　dp[root][1]=sum{min{dp[son][0],dp[son][1],dp[son][2]}};
//　　　　　　dp[root][2]=sum{min{dp[son][1],dp[son][2]}};这一条比较特殊，当括号内取小的时候如果一直取的是dp[son][2]，就需要特殊处理，就是说必须有一个点是dp[son][1]的取值。还有就是这个方法的边界处理比较麻烦。

#include <stdio.h>
#include <vector>
#include <string.h>
#define N 10005
#define INF 2000000
#define MIN(a,b) ((a)<(b)?(a):(b))
using namespace std;
 
vector<int>gra[N];
int fa[N],dp[N][3],n;
 
void dfs(int s,int f)
{
    fa[s]=f;
    dp[s][0]=0;
    dp[s][1]=1;
    dp[s][2]=0;
    if(gra[s].size()==1&&gra[s][0]==f)
    {
        dp[s][2]=INF;
        return ;
    }
    int mark=0;
    for(int i=0;i<gra[s].size();i++)
    {
        int t=gra[s][i];
        if(t==f)continue;
        dfs(t,s);
        dp[s][1]+=MIN(MIN(dp[t][0],dp[t][1]),dp[t][2]);
        dp[s][0]+=dp[t][2];
        if(dp[t][1]<=dp[t][2])
        {
            mark=1;
            dp[s][2]+=dp[t][1];
        }
        else
            dp[s][2]+=dp[t][2];
    }
    if(mark)return ;
    int temp=INF;
    for(int i=0;i<gra[s].size();i++)
    {
        int t=gra[s][i];
        if(t==f)continue;
        temp=MIN(temp,dp[s][2]+dp[t][1]-dp[t][2]);
    }
    if(temp!=INF)
        dp[s][2]=temp;
}
 
void re(void)
{
    scanf("%d",&n);
    memset(fa,0,sizeof(fa));
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++)
        gra[i].clear();
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        gra[a].push_back(b);
        gra[b].push_back(a);
    }
}
 
void run(void)
{
    dfs(1,-1);
    printf("%d\n",MIN(dp[1][1],dp[1][2]));
}
 
int main()
{
    re();
    run();
}
//*/