/*                     2732K	469MS	C++	1321B

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;
 
#define maxn 2005
 
struct Highway
{
    int a, b;
}way[maxn * maxn];
 
int n, m, k, c[maxn];
__int64 ans;
 
void input()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < k; i++)
        scanf("%d%d", &way[i].a, &way[i].b);
}
 
bool cmp(const Highway &a, const Highway &b)
{
    if (a.a != b.a)
        return a.a < b.a;
    return a.b < b.b;
}
 
__int64 cal(int a)    // 求和
{
    __int64 sum = 0;
    while (a > 0)
    {
        sum += c[a];
        a -= (a & -a);   // 最右边一个1
    }
    return sum;
}
 
void modify(int a, int x)
{
    while (a <= m)
    {
        c[a] += x;
        a += (a & -a);
    }
}
 
void work()
{
    ans = 0;
    for (int i = 0; i < k; i++)
    {
		//printf("%I64d ", cal(way[i].b));
        ans += i - cal(way[i].b);
        modify(way[i].b, 1);
		//cout << way[i].b << endl;
    }
}
 
int main()
{
    //freopen("D:\\t.txt", "r", stdin);
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++)
    {
        memset(c, 0, sizeof(c));
        input();
        sort(way, way + k, cmp);
        work();
        printf("Test case %d: %I64d\n", i + 1, ans);
    }
    return 0;
}

//*/




/*            5040K	719MS	C++	799B

#include<iostream>
#include<algorithm>
#include<vector>
#include<stdio.h>

using namespace std;

int nx[1050];

int main()
{
    //freopen("in.in","r",stdin);
	//freopen("out.txt", "w", stdout);
    int t,T;
	 scanf("%d",&T);t=1;
	 int ret=0;
	 while(t<=T)
	 {
		  int N,M,K;

		  scanf("%d%d%d",&N,&M,&K);

		  vector<pair<int,int> > r;

		  while(K--)
		  {
			   int tmp1,tmp2;
			   scanf("%d%d",&tmp1,&tmp2);
			   r.push_back(make_pair(tmp1,tmp2));
		  }

		  memset(nx,0,sizeof(nx));
		  sort(r.begin(),r.end());
		  __int64 ret=0;

		  for(int i=0;i<r.size();i++)
		  {
			   for(int j=1;j<r[i].second;j++)
			   {
					nx[j]++;
			   }
			   ret+=nx[r[i].second];
		  }

		  printf("Test case %d: %I64d\n",t,ret);
		  t++;
	 }
    return 0;
}

//*/


//*                      2728K	469MS	C++	1100B

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<algorithm>

using namespace std;

const int N=500005;
const int M=1005;

struct TNode 
{
    int xs,xt;
}road[N];

__int64 cal[M];
int n,m,T,knum;
int lowbit(int x) {return x&-x;}

int getsum(int x) 
{
    int s=0;
    for(;x>0;s+=cal[x],x-=lowbit(x));
    return s;
}

void update(int x,int value) 
{
    for(;x<=m;cal[x]+=value,x+=lowbit(x));
}
bool cmp(TNode a,TNode b) 
{
    if(a.xs==b.xs) return a.xt>b.xt;
    else return a.xs>b.xs;
}

int main() 
{
    int end,i;
    __int64 ans;
    scanf("%d",&T);

    for(end=1;end<=T;end++) 
	{
        scanf("%d%d%d",&n,&m,&knum);
        for(i=0,ans=0;i<knum;i++)
			scanf("%d%d",&road[i].xs,&road[i].xt);

        sort(road,road+knum,cmp);

        memset(cal,0,sizeof(cal));

        for(i=0;i<knum;i++) 
		{//如果不减一的话,就将共端点的线段的交点也计为有效了
            ans+=getsum(road[i].xt-1);   // 如果是将前面比当前大的加上得总个数，正因为树状数组有局部求和的特征，所以只要加上某些特定位置的数就可以了。
            update(road[i].xt,1);
        }

        printf("Test case %d: %I64d\n",end,ans);
    }
    return 0;
} 
//*/