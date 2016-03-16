#include<iostream>

#include<string>

#include<cstring>

#include<cstdio>

#include<algorithm>

#include<cmath>

#include<map>

#include<vector>

using namespace std;

const int N = 105;

const int MAX = 1000000;

int color[N];

vector<int> v[N];

vector<int> ans;

int in[N],out[N];

void dfs(int u)
{
   if(!color[u])ans.push_back(u);

   int vv;

   for(int i = 0; i < v[u].size(); i++)
   {
      vv = v[u][i];

      if(color[vv] == -1)
      {
         color[vv] = !color[u];

         dfs(vv);
      }
   }
}

int main()
{
	int i;
   memset(color,-1,sizeof(color));

   int n,k;

   cin>>n;

   for(i = 1; i <= n; i++)
   {

      while(cin>>k && k)
      {

         v[i].push_back(k);

         v[k].push_back(i);

         in[k]++;

         out[i]++;
      }
   }

   for(i = 1; i <= n; i++)
   {
      if(!in[i] && !out[i])
      {
         cout<<0<<endl;
         return 0;
      }
   }

   for(i = 1; i <= n; i++)
   {
      if(color[i] == -1)
      {
         color[i] = 1;

         dfs(i);
      }
   }

   cout<<ans.size()<<endl;

   cout<<ans[0];

   for(i = 1; i < ans.size(); i++)
   {
      cout<<' '<<ans[i];
   }

   cout<<endl;

   return 0;

}




/*
#include <iostream>
#include <queue>
using namespace std;

#define Rep(k,i,j) for(k=i;k<j;k++)

int a[110][110],state[110];


int main()
{
	queue<int> myqueue;
	int n,i,j;
	cin>>n;

	Rep(i,1,n+1){
		state[i]=-1;
		Rep(j,1,n+1)
			a[i][j]=0;
		}
	Rep(i,1,n+1)
	{
		while (true)
		{
			cin>>j;
			if (j==0) 
				break;
			else 
				a[i][j] =1;
		}
		
	
	}
	
	Rep(i,1,n+1)
	{
		if (state[i]==-1)
		{
			state[i] =0;
			myqueue.push(i);
			while (!myqueue.empty())
			{
				int cur = myqueue.front();
				myqueue.pop();

				Rep(j,1,n+1)
					if (a[i][j] && state[j]==-1)
					{
						state[j]=1-state[i];
						myqueue.push(j);
					}

			}
		}

	}

	int count=0;
	Rep(i,1,n+1)
		if (state[i]==1) count++;
	
	cout<<count<<endl;

	Rep(i,1,n+1)
	{
		if (state[i])
			cout<<i<<" ";
	}
	return 0;
}
//*/


/*
#include <queue>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAX = 110;
bool map[MAX][MAX];
bool used[MAX];
bool team[MAX];
int n;
void DFS(int x)
{
	used[x] = 1;
	for(int i=1; i<=n; i++)
		if( map[x][i] && !used[i] )
		{
			if( !team[x] ) 
				team[i] = true;
			DFS(i);
		}
}
int main()
{
	int t;
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		while( scanf("%d",&t) && t )
			map[i][t] = 1;
			
	memset(used,0,sizeof(used));
	memset(team,false,sizeof(team));
	for(int i=1; i<=n; i++)
		if( !used[i] )
			DFS(i);
	
	int ans = 0;
	for(int i=1; i<=n; i++)
		if( team[i] )
			ans++;
	printf("%d/n",ans);
	for(int i=1; i<=n; i++)
		if( team[i] )
		{
			printf("%d",i);
			ans--;
			printf("%c",ans == 0 ? '/n' : ' ' );
		}
return 0;
}

//*/