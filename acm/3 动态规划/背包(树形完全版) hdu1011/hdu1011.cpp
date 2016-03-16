//*         46MS	432K	1311 B	C++
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 210;
int c[N], v[N];
int dp[N][N];
int vis[N];
int n, m;

struct node{
	int v;
	node *next;
}*head[N], cavern[N];
int p;

void init(){
	p = 1;
	memset(head, NULL, sizeof(head));
	memset(dp, 0, sizeof(dp));
	memset(vis, 0, sizeof(vis));
}

void addedge(int a, int b){
	cavern[p].v = b;
	cavern[p].next = head[a];
	head[a] = &cavern[p++];
}

void dfs(int u){
	vis[u] = 1;
	int i, j;
	node *pp = head[u];
	int cc = c[u];
	int vv = v[u];

	for(i=m; i>=cc; i--)
		dp[u][i] = vv;

	while(pp!=NULL){
		int uv = pp->v;
		if(!vis[uv]){  
			dfs(uv);
			for(i=m; i>=cc; i--){
				for(j=1; i+j<=m; j++){
					if(dp[uv][j] && dp[u][i+j]<dp[u][i]+dp[uv][j]){
						dp[u][i+j] = dp[u][i] + dp[uv][j];
					}
				}
			}
		}
		pp = pp->next;
	}

}

int main()
{
	freopen("in.txt", "r", stdin);
	int i;
	int a, b;

	while(scanf("%d %d", &n, &m)){
		if(n==-1 && m==-1)
			break;
		
		init();
		for(i=1; i<=n; i++){
			scanf("%d %d", c+i, v+i);
			c[i] = (c[i] + 19) / 20;
		}
		for(i=1; i<n; i++){
			scanf("%d %d", &a, &b);
			addedge(a, b);
			addedge(b, a);
		}

		if(m==0){
			printf("0\n");
			continue;
		}

        dfs(1);
        printf("%d\n",dp[1][m]);  
	}

	return 0;
}
//*/






/*          46MS	320K	1420 B	C++
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
#define MAX 110
#define max(a,b) (a)>(b)?(a):(b)


int val[MAX],need[MAX];
vector<int> tree[MAX];
int cnt,n,m,dp[MAX][MAX],vis[MAX];


void Tree_DP(int s){

    if (vis[s]) return ;
    vis[s] = 1;
	int i,j,k,tp,temp;


    for (i = need[s]; i <= m; ++i) 
		dp[s][i] = val[s];
    for (i = 0; i < tree[s].size(); ++i) {

        tp = tree[s][i];
        if (vis[tp]) continue;
        Tree_DP(tp);
        

        for (j = m; j >= need[s]; --j)
            for (k = 1; k + j <= m; ++k)
                if (dp[tp][k]) {

		            temp = dp[s][j] + dp[tp][k];
                    dp[s][j+k] = max(dp[s][j+k],temp);
                }
    }
}


int main()
{
    int i,j,k,a,b;


    while (scanf("%d%d",&n,&m),n + m != -2){
    
        for (i = 1; i <= n; ++i){

            scanf("%d%d",&need[i],&val[i]);
			tree[i].clear();
            need[i] = (need[i] + 19) / 20;
        }

            
        for (i = 1; i < n; ++i){

            scanf("%d%d",&a,&b);
			if (a < b)
            tree[a].push_back(b);
            else 
			tree[b].push_back(a);
        }
		

		if (m == 0) {

			printf("0\n");
			continue;
		}

        memset(dp,0,sizeof(dp));
        memset(vis,0,sizeof(vis));
        Tree_DP(1);
        printf("%d\n",dp[1][m]);
    }
    return 0;
}
//*/
