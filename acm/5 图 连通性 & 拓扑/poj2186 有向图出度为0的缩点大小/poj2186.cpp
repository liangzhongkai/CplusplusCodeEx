/*
//  1268K	500MS	C++	1635B
#include<iostream>
#include<cstdio>
#include<vector>
#include<stack>
#include<cstring>

using namespace std;

#define  sc(a,b)  scanf("%d%d", &a, &b)
#define  f1(i, n)  for(i=1; i<=n; i++)
#define  f0(i, n)  for(i=0; i<n; i++)

const int N = 10005;
vector<int> adj[N];
int n, m;
int instack[N], dep[N], low[N], belong[N], cnt, num;
int out[N];

stack<int> st;
void Tarjan(int x){
	int i, j, len = adj[x].size();
	dep[x] = low[x] = ++num;
	instack[x] = 1;
	st.push(x);
	f0(i,len){
		int u = adj[x][i];
		if(dep[u]==-1){
			Tarjan(u);
			if(low[u]<low[x]) low[x] = low[u];
		}
		else if(instack[u] && low[x]>dep[u]){
			low[x] = dep[u];
		}
	}
	if(low[x]==dep[x]){
		cnt++;
		do{
			j = st.top();
			st.pop();
			instack[j] = 0;
			belong[j] = cnt;
		}while(j!=x);
	}
}

int main()
{
	int a, b;
	int i, j;

	sc(n, m);
	f1(i, m){
		sc(a, b);
		adj[a].push_back(b);
	}

	cnt = num = 0;
	memset(dep, -1, sizeof(dep));
	memset(low, 0, sizeof(low));
	memset(instack, 0, sizeof(instack));
	f1(i, n){
		if(dep[i]==-1){
			Tarjan(i);
		}
	}

	memset(out, 0, sizeof(out));
	f1(i, n){
		int len = adj[i].size();
		for(j=0; j<len; j++){
			if(belong[i]!=belong[adj[i][j]]){
				out[belong[i]]++;
			}
		}
	}
	// debug
	//for(i=1; i<=n; i++){
	//	printf("%d ", belong[i]);
	//}
	//printf("\n");

	int count = 0;
	int key = 0;
	for(i=1; i<=cnt; i++){
		if(out[i]==0){
			count++;
			key = i;
		}
	}

	if(count!=1){
		printf("0\n");
	}
	else{
		count = 0;
		f1(i, n){
			if(belong[i]==key)
				count++;
		}
		printf("%d\n", count);
	}

	return 0;
}
//*/

/*  1536K	579MS	C++	1672B
#include <iostream>
#include<vector>
#include<cstdio>
using namespace std;

const int V = 10005;
vector<int> adj1[V], adj2[V];
int dfn[V], num[V], n, m, scc, cnt;
int out[V];

void dfs(int k)
{
	num[k] = 1;
	int len = adj1[k].size();
	for(int i=0; i<len; i++)
		if(!num[adj1[k][i]])
			dfs(adj1[k][i]);
	dfn[++cnt] = k;		//记录第cnt个出栈的顶点为k 
}
void ndfs(int k)
{
	num[k] = scc;//本次DFS染色的点，属于同一个scc，用num数组做记录
	int len = adj2[k].size();
	for(int i=0; i<len; i++)
		if(!num[adj2[k][i]])   //注意我们访问的原矩阵的对称矩阵 
			ndfs(adj2[k][i]);
}
void kosaraju()
{
	int i;
	for(i=1; i<=n; i++)				//DFS求得拓扑排序 
		if(!num[i])
			dfs(i);
	memset(num, 0, sizeof num);		
	for(i=cnt; i>=1; i--)
		if(!num[dfn[i]]){	     //按照拓扑序进行第二次DFS 
			scc++;
			ndfs(dfn[i]); 
		}
}
int main()
{
	int i, j;
	int x, y;
	cin>>n>>m;
	for(i=1; i<=m; i++){
		cin>>x>>y;
		adj1[x].push_back(y);
		adj2[y].push_back(x);
	}
	kosaraju();
	// debug
	//for(i=1; i<=n; i++){
	//	cout << num[i] << " ";
	//}
	//cout << endl;
	memset(out, 0, sizeof(out));
	for(i=1; i<=n; i++){
		int len = adj1[i].size();
		for(j=0; j<len; j++){
			if(num[i]!=num[adj1[i][j]]){
				out[num[i]]++;
			}
		}
	}
	// debug
	//for(i=1; i<=scc; i++){
	//	printf("%d ", out[i]);
	//}
	//printf("\n");
	int count = 0;
	int key = 0;
	for(i=1; i<=scc; i++){
		if(out[i]==0){
			count++;
			key = i;
		}
	}
	if(count!=1){
		printf("0\n");
	}
	else{
		count = 0;
		for(i=1; i<=n; i++){
			if(num[i]==key)
				count++;
		}
		printf("%d\n", count);
	}

	return 0;
}





/*    3312K	329MS	C++	1633B
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define N 10000
#define M 50000
struct
{
    int s,e;
}edge[M];
typedef struct Arc
{
    int v;
    struct Arc*next;
}arc;
arc* cow[N],*rcow[N];
int n,m;
int cnt,ts[N],deg[N],sc[N];
char v[N];
void dfsr(int t)
{
    v[t]=1;
    arc*p;
    for(p=rcow[t];p;p=p->next)
        if(!v[p->v])
            dfsr(p->v);
    ts[cnt++]=t;
}
void dfs(int t)
{
    v[t]=1;
    sc[t]=cnt;
    arc*p;
    for(p=cow[t];p;p=p->next)
        if(!v[p->v])
            dfs(p->v);
}
int main()
{
    int s,e,i,k;
    arc*p;
    scanf("%d%d",&n,&m);
    for(i=0;i<m;i++)
    {
        scanf("%d%d",&s,&e);
        s--,e--;
        edge[i].s=s;
        edge[i].e=e;
        p=(arc*)malloc(sizeof(arc));
        p->v=e;
        p->next=cow[s];
        cow[s]=p;
        p=(arc*)malloc(sizeof(arc));
        p->v=s;
        p->next=rcow[e];
        rcow[e]=p;
    }
    cnt=0;
    for(i=0;i<n;i++)
        if(!v[i])
            dfsr(i);
    memset(v,0,sizeof(v));
    cnt=0;
    for(i=n-1;i>=0;i--)
        if(!v[ts[i]])
        {
            dfs(ts[i]);
            cnt++;
        }
    k=cnt;
    for(i=0;i<m;i++)
    {
        s=edge[i].s;
        e=edge[i].e;
        if(sc[s]!=sc[e])
            deg[sc[s]]++;
    }
    cnt=0;
    for(i=0;i<k;i++)
        if(!deg[i])
        {
            cnt++;
            s=i;
        }
    if(cnt>1)
        printf("0\n");
    else
    {
        for(cnt=0,i=0;i<n;i++)
            if(sc[i]==s)
                cnt++;
        printf("%d\n",cnt);
    }
    return 0;
}
//*/



//*   Gabow 实现
#include<string.h>
#include<stdio.h>
#include<malloc.h>
#define N 10000
#define M 50000
typedef struct Arc
{
    int v;
    struct Arc* next;
}arc;
struct
{
    int s,e;
}edge[M];
arc* cow[N];
int n,m;
int sc[N],s[N],path[N],pre[N],lens,cnt0,p,cnt,cnt1;
void dfs(int w)
{
    arc *q;
    pre[w]=cnt0++;
    s[lens++]=w;
    path[p++]=w;
    for(q=cow[w];q;q=q->next)
        if(pre[q->v]==-1)
            dfs(q->v);
        else if(sc[q->v]==-1)
            while(pre[path[p-1]]>pre[q->v])
                p--;
    if(path[p-1]!=w)
        return;
    else
        p--;
    do
        sc[s[--lens]]=cnt;
    while(s[lens]!=w);
    cnt++;
}
int main()
{
    int i,l,r;
    arc* q;
    scanf("%d%d",&n,&m);
    for(i=0;i<m;i++)
    {
        scanf("%d%d",&l,&r);
        edge[i].s=--l;
        edge[i].e=--r;
        q=(arc*)malloc(sizeof(arc));
        q->v=r;
        q->next=cow[l];
        cow[l]=q;
    }
    memset(pre,0xff,sizeof(pre));
    memset(sc,0xff,sizeof(sc));
    for(i=0;i<n;i++)
        if(sc[i]==-1)
            dfs(i);
    memset(s,0,sizeof(s));
    for(i=0;i<m;i++)
        if(sc[edge[i].s]!=sc[edge[i].e])
            s[sc[edge[i].s]]++;
    cnt1=0;
    for(i=0;i<cnt;i++)
        if(!s[i])
        {
            cnt1++;
            l=i;
        }
    if(cnt1!=1)
        printf("0\n");
    else
    {
        cnt=0;
        for(i=0;i<n;i++)
            if(sc[i]==l)
                cnt++;
        printf("%d\n",cnt);
    }
    return 0;
}
//*/