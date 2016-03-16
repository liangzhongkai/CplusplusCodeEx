/*
12 15
1 2
1 7
1 8
2 3
2 6
3 4
3 5
4 5
4 6
7 9
7 10
9 10
8 11
8 12
11 12

void union_set(int x, int y){
	int xx = find(x);
	int yy = find(y);
	if(xx==yy)   return ;
	else{
		if(rank[xx]>rank[yy]){
			father[yy] = xx;
			rank[xx] += rank[yy];
		}
		else{
			fathre[xx] == yy;
			rank[yy] += rank[xx];
		}
	}
}


*/

/*     328K	125MS	C++	1081B
//      332K	32MS	C++	1588B
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 5001;
vector< vector<int> > adj;
int cnt,low[MAXN],visit[MAXN],degree[MAXN];

int rank[MAXN], father[MAXN];
int n;

void init(){
	for(int i=0; i<=n; i++){
		//rank[i] = 1;
		father[i] = i;
	}
}

int find(int x){
	if(father[x]==x)   return x;
	else{
		while(father[x]!=x){
			x = father[x];
		}
	}
	return x;
}


// 将双连通分量标记起来  其实只是环
void dfs(int u,int v){               // u为当前节点、v为父亲节点
    visit[u] = 1;
    low[u] = cnt++;
    int i,len=adj[u].size();
    for(i=0;i<len;i++){
        if(adj[u][i]==v) continue;   // u为叶子
        if(!visit[adj[u][i]]) dfs(adj[u][i],u);  // 向前边
        if(low[adj[u][i]]<low[u]){
			low[u]=low[adj[u][i]];
			father[u] = father[adj[u][i]];
		}
    }
    //visit[u]=2;   // 如果不要这句328K	47MS	C++	1083B
}

int main()
{
    int i,j,u,v,m,len,ans;
    scanf("%d %d",&n,&m);
    adj.assign(n+1,vector<int>());

    while(m--){
        scanf("%d %d",&u,&v);
        adj[u].push_back(v),adj[v].push_back(u);
    }

	init();
    memset(visit,0,sizeof(visit));
    cnt=0, dfs(1,1);

	for(i=1; i<=n; i++)
		cout << find(i) << " ";
	cout << endl;

	for(i=1; i<=n; i++)
		father[i] = find(i);

    memset(degree,0,sizeof(degree));
    for(i=1;i<=n;i++){
        len=adj[i].size();
        for(j=0;j<len;j++)
            if(father[i]!=father[adj[i][j]])
                degree[father[i]]++;
    }

    for(ans=i=0;i<=n;i++)
        if(degree[i]==1) ans++;
    printf("%d\n",(ans+1)/2);

    return 0;
}
//*/







//*     476K	63MS	C++	2446B
#include<iostream>
#include<vector>

using namespace std;
#define min(a, b) a>b?b:a

vector<int>  list[5001];   
int low[5001];
int d[5001],dep[5001];
int color[5001];
int n,m;
int bridge[10001][2];
int p[5001],rank[5001],cnt,tol,num=0;
int ncon,belong[5001];

void Init()
{
    int i;
    for(i=1;i<=n;i++)
    {
        p[i]=i;
        rank[i]=0;
    }
}
int Find(int x)
{
    if(x!=p[x])
        p[x]=Find(p[x]);
    return p[x];
}
int Union(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(rank[a]>rank[b])
    {
        p[b]=a;
    }
    else
    {
        p[a]=b;
        if(rank[a]==rank[b])
        {
            rank[b]++;
        }
    }
    return 0;
}
int DFS(int u,int fa,int t)
{
    color[u]=1;
    dep[u]=low[u]=t;
    tol=0;
    int tofa=0;
    int i,v;
    for(i=0;i<list[u].size();i++)
    {
        v=list[u][i];
        if(color[v]==0)
        {
            DFS(v,u,t+1);
            tol++;
            low[u]=min(low[u],low[v]);
            if(low[v]<=dep[u])
                Union(u,v);
            if(low[v]>dep[u])
            {
                bridge[num][0]=u;
                bridge[num++][1]=v;
            }
        }
        else if(v!=fa||tofa)
        {
            low[u]=min(low[u],dep[v]);
        }
        if(v==fa) tofa=1; 

    }
    return 0;
}
int DC()
{
    int i;
    for(i=1;i<=n;i++)
    {
        belong[i]=-1;
    }
    for(i=1;i<=n;i++)
    {
        int k=Find(i);
        if(belong[k]==-1)
            belong[k]=++ncon;
        belong[i]=belong[k];
    }
    for(i=0;i<num;i++)
    {
        d[belong[bridge[i][0]]]++;
        d[belong[bridge[i][1]]]++;
    }
    for(i=1;i<=ncon;i++)
    {
        if(d[i]==1)
            cnt++;
    }
    return (cnt+1)/2;

}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        cnt=0;
        num=0;
        memset(list,0,sizeof(list));
        memset(d,0,sizeof(d));
        memset(dep,0,sizeof(dep));
        memset(low,0,sizeof(low));
        memset(color,0,sizeof(color));
        int a,b;
        while(m--)
        {
            scanf("%d%d",&a,&b);
            list[a].push_back(b);
            list[b].push_back(a);
        }
        Init();
        int i;
        for(i=1;i<=n;i++)
        {
            if(!color[i])
                DFS(i,-1,1);
        }
		for(i=1; i<=n; i++)
			cout << low[i] << " ";
		cout << endl;

        printf("%d\n",DC());
    }
    system("pause");
    return 0;
}
//*/


