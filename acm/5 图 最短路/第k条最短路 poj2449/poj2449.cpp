/*
2 2
1 2 5
2 1 4
1 2 2
14
3 3
1 2 5
1 3 6
2 3 5
1 3 2
10
3 3
1 2 5
1 3 6
2 3 5
1 3 3
-1
3 4
1 2 5
1 3 6
2 3 5
3 1 2
1 3 3
14
3 4
1 2 5
1 3 6
2 3 5
3 2 5
1 3 5
26
3 4
1 2 5
1 3 6
2 3 5
3 1 2
1 1 3
16
*/

//*
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>

using namespace std;

const int INF = 200000000;

int dist[1005];
bool vis[1005];
int ct[1005];
int mp[1001][1001];

struct point{
	int v, w;
	point(){};
	point(int a, int b):v(a),w(b){};
	bool operator<(const point &a)const{
		return w+dist[v]>a.w+dist[a.v];
	}
};

int main()
{
	int n, m;
	int i, j;
	int a, b, c;
	int s, t, k;

	scanf("%d%d", &n, &m);
	memset(mp, 0, sizeof(mp));
	for(i=0; i<m; i++){
		scanf("%d%d%d", &a, &b, &c);
		if(mp[a][b]==0 || mp[a][b]>c)
			mp[a][b] = c;                // 邻接矩阵不能处理重边？？？？？？？？？？
	}
	scanf("%d%d%d", &s, &t, &k);

	// 每点到终点t的最短距离///////////////////  dijsktra  ///////////
	memset(vis, false, sizeof(vis));
	for(i=1; i<=n; i++)   dist[i] = INF;
	dist[t] = 0;
	for(i=1; i<=n; i++){
		int p = -1;
		for(j=1; j<=n; j++){
			if(!vis[j] && (p==-1 || dist[p]>dist[j]))
				p = j;
		}
		if(p==-1)    break;
		vis[p] = true;
		for(j=1; j<=n; j++){
			if(!vis[j] && mp[j][p]!=0 && dist[j]>(dist[p] + mp[j][p]))
				dist[j] = dist[p] + mp[j][p];
		}
	}
	//for(i=1; i<=n; i++)
	//	cout << dist[i] << endl;
	///////////////////////////////////////////////////////////////////

	if(s==t)   k++;
	memset(ct, 0, sizeof(ct));

	priority_queue<point> q;
	point temp(s, 0), tmp;
	q.push(temp);
	while(!q.empty()){
		tmp = q.top(); q.pop();
		//printf("*%d  %d\n", tmp.v, tmp.w+dist[tmp.v]);
		
		ct[tmp.v]++;
		if(ct[t]==k)   break;
		if(ct[tmp.v]>k)   continue;

		for(i=1; i<=n; i++){
			if(mp[tmp.v][i]){
				temp.v = i;
				temp.w = mp[tmp.v][i] + tmp.w;
				q.push(temp);
			}
		}
	}

	if(ct[t]<k)
		printf("-1\n");
	else
		printf("%d\n", tmp.w);

	return 0;
}
//*/


/*       15420K   797MS	     C++	2229B

#include <iostream>
#include <queue>
#include <stdio.h>

using namespace std;

#define     INF     1000000000

struct Node{
    Node(int a, int b):u(a),v(b),next(0){}
    int u, v, cost;
    Node *next;
};

struct State{
    int pos;
    int g, h;
    friend bool operator < (State a, State b){
        return a.h+a.g > b.h+b.g;
    }
};

Node*   E[1001] = {0};
Node*   E2[1001] = {0};
int     S, T, K, N, M;
int     dis[1001];

void AddEdge(int u, int v, int cost){
    Node* x = new Node(u, v);
    x->cost = cost;
    x->next = E[u];
    E[u] = x;
}
void AddEdge2(int u, int v, int cost){
    Node* x = new Node(u, v);
    x->cost = cost;
    x->next = E2[u];
    E2[u] = x;
}

void spfa(int s, int t){
    int inq[1001] = {0};
    queue<int> q;

    for (int i=1; i<=N; i++)
        dis[i] = (i == s) ? 0 : INF;
    inq[s] = 1;
    q.push(s);

    while (!q.empty()){
        int u = q.front(); q.pop();
        inq[u]= 0;
        for (Node *e=E2[u]; e!=NULL; e=e->next){
            int v = e->v;
            if (dis[v] > dis[u] + e->cost){
                dis[v] = dis[u] + e->cost;
                if (!inq[v]){
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}

int AStar(int s, int t, int k){
    int vis[1001] = {0};
    priority_queue<State> q;

    State beg;
    beg.pos = s;
    beg.g   = 0;
    beg.h   = dis[s];

    q.push(beg);
    while (!q.empty()){
        State u = q.top(); q.pop();
        vis[u.pos]++;

        if (vis[u.pos]==k && u.pos==t)
            return u.g + u.h;
        if (vis[u.pos] > k) continue;

        // expand u
        for (Node *e=E[u.pos]; e!=0; e=e->next){
            State ns;
            ns.g = u.g + e->cost;
            ns.h = dis[e->v];
            ns.pos = e->v;
            q.push(ns);
        }
    }

    return -1;
}

int main()
{
    cin >> N >> M;
    for (int i=0; i<M; i++){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        AddEdge(a, b, c);
        AddEdge2(b, a, c);
    }

    cin >> S >> T >> K;
    if (S == T)   K++;      // 起点与终点相等
    spfa(T, S);

    cout << AStar(S, T, K) << endl;

    return 0;
}
//*/



/*       13792K	438MS	 C++	2729B
#include <queue>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

#define MAXN 1011
#define MAXM 500000
#define inf 999999999   //表示无穷大

int n, m, S, T, K;
int dist[MAXN];

struct Edge
{
	 int to, w, next;
	 Edge(int to, int w, int next):to(to),w(w),next(next){}
	 Edge(){}
	 inline bool operator < (const Edge &b) const
	 {
		return w + dist[to] > b.w + dist[b.to]; //这里是对估价函数的使用，使得路径最短的先出队
	 } 
};

Edge e[MAXM], ee[MAXM];
int pn1[MAXM], pn2[MAXM];
int cnt1, cnt2;

int getint()     //这个getchar的输入对大数据量输入非常有用，甚至可以挽救效率不高的算法
{
    int ret=0;
	char tmp;
    while(!isdigit(tmp=getchar()));
    do{
		ret = (ret<<3) + (ret<<1) + tmp - '0';
    }while(isdigit(tmp=getchar()));
    return ret;
}
// 要学习这种构图方式：允许有重边
void addedge(Edge *e, int *pn, int &cnt, int from, int to, int w)
{
	 e[cnt].to = to;
	 e[cnt].w = w;
	 e[cnt].next = pn[from];
	 pn[from] = cnt++;
}

void Dijkstra(int v)
{
	 int i, u, x;
	 bool s[MAXN];               //最短路径顶点集
	 memset(s,false,sizeof(s));
	 for (i = 1; i <= n; i++)    //最短距离初始化 
		dist[i] = inf; 

	 priority_queue<Edge> heap;
	 dist[v] = 0;        //把顶点v加入最短路径顶点集
	 heap.push(Edge(v,0,-1));
	 while (!heap.empty())
	 {
		  u = heap.top().to;
		  heap.pop();
		  if (s[u])   continue;
		  s[u] = 1;
		  for (i = pn2[u]; i != -1; i = ee[i].next)
		  {
			   x = ee[i].to;
			   if (!s[x] && dist[u] + ee[i].w < dist[x])
			   {
					dist[x] =  dist[u] + ee[i].w;  // father[x] = u;
					heap.push(Edge(x,dist[x],-1));
			   }
		  }
	 }
}

int Astar()          //A*搜索
{
	 int u, i, len, c[MAXN], temp;
	 if(dist[S] == inf)   return -1;  //S点到不了T点

	 priority_queue<Edge> heap;  //用优先级队列实现Open表
	 memset(c,0,sizeof(c));  //统计经过该点的次数
	 heap.push(Edge(S,0,-1));
	 while(!heap.empty())
	 {
		  u = heap.top().to;  //从Open表中取得一个节点X
		  len = heap.top().w;
		  heap.pop();  //并从Open表中删除
		  c[u]++;
		  if(c[T] == K)  //第K次到达目标节点
				return len;
		  if(c[u] > K)  //任意一点重复超过K次
				continue;
		  for (i = pn1[u]; i != -1; i = e[i].next)  //每个X的子节点Y
		  {
			   temp = e[i].to;
			   heap.push(Edge(temp,len + e[i].w,-1));   //更新Open表
		  } 
	 }
	 return -1;  //没有第K条最短路
}

int main()
{   
    int u, v, w;
 
	 n = getint();
	 m = getint();
	 //scanf("%d %d",&n,&m);

	 memset(pn1,0xff,sizeof(pn1));     // 以char为单位赋值
	 memset(pn2,0xff,sizeof(pn2));     // 这里等于-1
	 cnt1 = cnt2 = 1;
	 while (m--)
	 {
		  u=getint();  v=getint();  w=getint();
		  //scanf("%d %d %d",&u,&v,&w);
		  addedge(e,pn1,cnt1,u,v,w);   // 构造正向图
		  addedge(ee,pn2,cnt2,v,u,w);  // 构造反向图
	 }
	 //scanf("%d %d %d",&S,&T,&K);
	 S=getint();  T=getint();  K=getint();

	 if (S == T)                       // 起点与终点相等
			K++;
	 Dijkstra(T);

	 printf("%d\n",Astar());
  
     return 0;   
}  
//*/ 



/* Memory: 8208K		Time: 266MS
#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
const int N = 1000+1;
const int M =  100000+1;
struct Edge
{
 int from,to;
 int dis;
 Edge *next;
}*ed[N],edge[M],*re[N],redge[M];
int ednum;
int dis[N];
int visited[N];
void init(int n)
{
 int i;
 for(i=0;i<n;i++)
 {
  ed[i]=NULL;
     re[i]=NULL;
 }
}
void addEdge(int from,int to,int dis)
{
 Edge *ptr = &edge[ednum];
 ptr->from = from;
 ptr->to = to;
 ptr->dis = dis;
 ptr->next = ed[from];
 ed[from]=ptr;
}

void addRedge(int from,int to,int dis)
{
 Edge *ptr = &redge[ednum];
 ptr->from = from;
 ptr->to = to;
 ptr->dis = dis;
 ptr->next = re[from];
 re[from]=ptr;
}

struct dnode//dijkstra()优先队列中使用的节点
{
 int v,len;//记录从出发点到节点v的长度
    bool operator<(const dnode &A)const
 {
  return A.len<len;
 }
};

void dijkstra(int s,int n)//计算各点到终点的距离
{
 memset(visited,0,sizeof(visited));
    memset(dis,-1,sizeof(dis));
 priority_queue<dnode>Q;
 dnode cur,next;
 cur.len = 0;
 cur.v = s;
 Q.push(cur);
 dis[s]=0;
 int vnum = 0;//已访完的节点数
 while(!Q.empty())
 {
  cur = Q.top();

  Q.pop();
  if(visited[cur.v])continue;
  visited[cur.v]=1;
  vnum++;
  if(vnum==n)return;
  for(Edge *ed = re[cur.v];ed!=NULL;ed=ed->next)
  {
           if(visited[ed->to]==0)
     {
      if(dis[ed->to]==-1||dis[ed->to]>cur.len+ed->dis)
      {
       next.len = cur.len+ed->dis;
       dis[ed->to]=next.len;
       next.v = ed->to;
       Q.push(next);
      }
     }
  }

 }
     
}

struct anode//astar()优先队列中的节点
{
   int to;   //记录从出发点到当前节点的距离
   int len;
   bool operator<(const anode &A)const
   {
    if(dis[A.to]==-1)return false;
    if(dis[to]==-1)return true;
    return A.len+dis[A.to]<len+dis[to];//估计函数的使用
   }
};
int aStar(int from,int to,int k)
{
     memset(visited,0,sizeof(visited));

  priority_queue<anode>Q;
  anode cur,next;
  if(from==to)k++;//两点重合时按题意加1
  cur.len = 0;
  cur.to = from;
  Q.push(cur);
  while(!Q.empty())
  {
         cur = Q.top();
 // printf("%d\n",cur.len);
   Q.pop();
   if(visited[cur.to]==k)return cur.len+dis[cur.to];
   if(visited[cur.to]>k)continue;
   visited[cur.to]++;
   if(visited[to]==k)return cur.len;

   for(Edge *ptr = ed[cur.to];ptr;ptr=ptr->next)
   {
    next.len = cur.len+ptr->dis;
    next.to = ptr->to;
    Q.push(next);
   }

  }
   return -1;
}
int main()
{
 int n,m;
 while(scanf("%d%d",&n,&m)!=EOF)
 {
  init(n);
  ednum = 0;
  while(m--)
  {
   int a,b,t;
   scanf("%d%d%d",&a,&b,&t);
   a--;
   b--;
   addEdge(a,b,t);
   addRedge(b,a,t);
   ednum++;
  }
  int s,t,k;
  scanf("%d%d%d",&s,&t,&k);
  s--,t--;
  dijkstra(t,n);
 // for(int i=0;i<n;i++)
 //  printf("%d\n",dis[i]);

  if(dis[s]==-1)printf("-1\n");
  else
   printf("%d\n",aStar(s,t,k));
 }
 return 0;
}

//*/