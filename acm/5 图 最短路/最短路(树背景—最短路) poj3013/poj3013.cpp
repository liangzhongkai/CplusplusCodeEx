/*
题意:一个图,图中每个节点都有重量,每条边都有一个单位价格,这棵树的根节点的编号为1,现在要使这棵树的总花费最小,每条边的花费为这条边的单位价格*(这条边的所有子节点的重量之和).这棵树的总花费就为所有边的花费总和.
    因为要求最小的花费,所以可以先求出根节点到每个节点的最短路,那么每个节点的最小花费就是:根节点到此节点的最短路*此节点的重量,显然总花费就为每个节点的花费之和,可以证明从根节点到每个点的最短路组成的图形就是一颗生成树.
    由于题目所给出的数据量很大,如果采用常规的最短路算法,那么将会超时,我个人所知的有两种解法:SPFA和用优先队列来实现Dijkstra算法.
    题目中的运算会超出int范围,所以应该采用__int64.
*/ 

//     3848K	688MS	G++	1783B
#include <cstdio>
#include <queue>
#include<iostream>
#include<cstring>

using namespace std;

const __int64 maxn=160001;
typedef unsigned __int64 lint;

struct node1
{
    lint len;
    int next,id;
} e[maxn*3];

lint n,m,level[maxn],dis[maxn];
int p[maxn];
bool inq[maxn];

void spfa(){
    memset(inq,0,sizeof(inq));
    for ( int i=0; i<n; i++)
        dis[i]=9999999999;
    dis[0]=0;
    queue<lint> que;
    que.push(0);
    while (!que.empty()){
        int  tc,i;
        tc = que.front();
        que.pop(),   inq[tc]=0;
        for ( i=p[tc]; i!=-1; i=e[i].next){
            if ( dis[e[i].id] > dis[tc] + e[i].len){
                dis[e[i].id] = dis[tc] + e[i].len;
                if (!inq[e[i].id]){
                    inq[e[i].id]=1;
                    que.push(e[i].id);
                }
            }
        }
    }
}

int main()
{
    int i,j,t;
    lint u,v,c;
    scanf("%d",&t);
    while (t--){
        scanf("%I64d%I64d",&n,&m);
        memset(p,-1,sizeof(p));

        for ( i = 0 ; i < n; i++)
            scanf("%I64d",&level[i]);

        for ( j=i=0 ; i < m; i++){
            scanf("%I64u%I64u%I64u",&u,&v,&c);
            e[j].id=v-1,  e[j].len=c,  e[j].next=p[u-1];   p[u-1]=j++;   // 处理一条边，p[]保留的是某点第一条边的序号
            e[j].id=u-1,  e[j].len=c,  e[j].next=p[v-1];   p[v-1]=j++;   
        }

        spfa();

        lint ans=0,flag=0;
        for ( i=0; i<n; i++){
            if (dis[i]==9999999999){
                flag=1;
                break;
            }
            ans+=level[i]*dis[i];
        }
        if (flag)   //  
            printf("No Answer\n");
        else printf("%I64u\n",ans);
    }
    return 0;
}


/*
#include<iostream>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;

const __int64 INF=(__int64)1<<63-1;                                   //这里习惯性的采用INF=1000000000,结果一直WA,因为在运算过程中结果超出了int范围
const int MAXN=50005;

struct Edge
{
       int to;
       int w;
       int next;
}e[2*MAXN];

int p[MAXN],head[MAXN];
int n,m,pos;

__int64 d[MAXN];
bool inq[MAXN];

void Init(int n)
{
     int i;
     for(i=0;i<=n;i++)
     {
         head[i]=-1;
         inq[i]=false;
     }
     pos=1;
}

void addedge(int from,int to,int weight)
{
     e[pos].to=to;
     e[pos].w=weight;
     e[pos].next=head[from];
     head[from]=pos++;
}

void SPFA(int s)                                                                                 //SPFA算法求解最短路,s为源点
{
     int i,x,u;
     queue<int>q;
     for(i=1;i<=n;i++)
         d[i]=(i==s?0:INF);
     q.push(s);
     while(!q.empty())
     {
         x=q.front();
         q.pop();
         inq[x]=false;
         for(u=head[x];u!=-1;u=e[u].next)
          if(d[e[u].to]>d[x]+e[u].w)
          {
               d[e[u].to]=d[x]+e[u].w;
               if(!inq[e[u].to])
               {
                   inq[e[u].to]=true;
                   q.push(e[u].to);
               }
          }
     }
}

int main()
{
    int i,u,v,t,ncase;
    __int64 sum;
    bool success;
    scanf("%d",&ncase);
    while(ncase--)
    {
          scanf("%d%d",&n,&m);
          for(i=1;i<=n;i++)
              scanf("%d",&p[i]);
          Init(n);
          for(i=0;i<m;i++)
          {
              scanf("%d%d%d",&u,&v,&t);
              addedge(u,v,t);                                                                  //注意是无向边
              addedge(v,u,t);
          }
          if(n==0||n==1)
          {
              printf("0\n");
              continue;
          }
          SPFA(1);
          success=true;
          sum=0;
          for(i=1;i<=n;i++)
           if(d[i]==INF)                                                                      
           {
               success=false;
               break;
           }
          if(success)
          {
               for(i=1;i<=n;i++)
                   sum+=d[i]*p[i];
               printf("%I64d\n",sum);
          }
          else
               printf("No Answer\n");
    }
    system("pause");
    return 0;
}
//*/


// 使用SPFA所用时间为:625ms,
// 换用优先队列来实现Dijkstra算法用了594ms
// 下面为使用优先队列实现Dijkstra算法的代码:
/*
#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

const __int64 INF=(__int64)1<<63-1;
const int MAXN=50005;

struct Edge
{
       int to;
       int w;
       int next;
}e[2*MAXN];

typedef pair<int,int>pii;                                                                                   //把d值和编号"捆绑"成一个整体放倒优先队列中,使用pair自定义一个pii类型

int p[MAXN],head[MAXN];
int n,m,pos;

__int64 d[MAXN];
bool done[MAXN];

void addedge(int from,int to,int weight)
{
     e[pos].to=to;
     e[pos].w=weight;
     e[pos].next=head[from];
     head[from]=pos++;
}

void Dijkstra(int s)
{
     int i,x,u;
     priority_queue<pii,vector<pii>,greater<pii> >q;                                                       //使用greater<int>表示"大于"运算符,此处来声明一个小整数出对的优先队列
     for(i=1;i<=n;i++)
         d[i]=(i==s?0:INF);
     memset(done,0,sizeof(done));                                                                          //初始化计算标志,所有节点都没有算出
     q.push(make_pair(d[s],s));                                                                            //起点进入优先队列
     while(!q.empty())
     {
         pii t=q.top();
         q.pop();
         x=t.second;
         if(done[x])                                                                                       //已经计算过,则忽略
            continue;
         done[x]=true;
         for(u=head[x];u!=-1;u=e[u].next)
          if(d[e[u].to]>d[x]+e[u].w)
          {
               d[e[u].to]=d[x]+e[u].w;                                                                    //松弛操作
               q.push(make_pair(d[e[u].to],e[u].to));                                                     //加入优先队列
          }
     }
}

int main()
{
    int i,u,v,t,ncase;
    __int64 sum;
    bool success;
    scanf("%d",&ncase);
    while(ncase--)
    {
          scanf("%d%d",&n,&m);
          for(i=1;i<=n;i++)
              scanf("%d",&p[i]);
          memset(head,-1,sizeof(head));
          pos=1;
          for(i=0;i<m;i++)
          {
              scanf("%d%d%d",&u,&v,&t);
              addedge(u,v,t);
              addedge(v,u,t);
          }
          if(n==0||n==1)
          {
              printf("0\n");
              continue;
          }
          Dijkstra(1);
          success=true;
          sum=0;
          for(i=1;i<=n;i++)
           if(d[i]==INF)
           {
               success=false;
               break;
           }
          if(success)
          {
               for(i=1;i<=n;i++)
                   sum+=d[i]*p[i];
               printf("%I64d\n",sum);
          }
          else
               printf("No Answer\n");
    }
    system("pause");
    return 0;
}
//*/




/*  还是dijkstra
//  源代码：(2220K 579MS)
#include<iostream>
#include<queue>
using namespace std;
const int Max = 50005;
const __int64 inf = 9999999999;
typedef __int64 lint;            //  优化了20多MS。
 
struct{
    int v, w, next;
}edge[2*Max];
struct node{
    int u;
    lint dis;
    bool operator < (const node &a) const{        //  heap的重载 < 号的形式。
        return dis > a.dis;
    }
};
int n, m, k, edgeHead[Max], val[Max];
lint dis[Max];
bool vis[Max];
 
void add_edge(int u, int v, int w){               //  为dijkstra构造邻接表。
    edge[k].v = v;
    edge[k].w = w;
    edge[k].next = edgeHead[u];
    edgeHead[u] = k ++;
    edge[k].v = u;
    edge[k].w = w;
    edge[k].next = edgeHead[v];
    edgeHead[v] = k ++;
}
 
void init_data(){
    for(int i = 1; i <= n; i ){
        dis[i] = inf;
        vis[i] = false;
    }
    dis[1] = 0;
}
 
void dijkstra(){
    init_data();
    priority_queue<node> que;    //  运用STL的优先队列。
    node a;                      
    a.u = 1; a.dis = 0;
    que.push(a);                 //  加入第一个节点，即为起点。
    while(!que.empty()){         //  优化的话可以多加一个 (&& count < n) 的判断。
        int u = que.top().u;
        que.pop();
        if(vis[u]) continue;
        vis[u] = true; 
        for(int i = edgeHead[u]; i != 0; i = edge[i].next){
            int v = edge[i].v;
            if(!vis[v] && dis[v] > dis[u] + edge[i].w){
                dis[v] = dis[u] + edge[i].w;
                a.u = v; a.dis = dis[v];
                que.push(a);    
        //  这里要注意一下：一个点有可能以不同的dis出现在que中，但是最后一次松弛的点dis最小，必排在最前面，而且它出列的时候vis[u]就变为true，故后面的不同值的dis也不会继续松弛了。
            }
        }  
    }
}
 
int main(){
    int t, i;
    scanf("%d", &t);
    while(t --){
        scanf("%d%d", &n, &m);
        for(i = 1; i <= n; i ){
            edgeHead[i] = 0;
            scanf("%d", &val[i]);
        }
        k = 1;
        while(m --){
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add_edge(u, v, w);   //  建双向边。
        }
        dijkstra();
        bool flag = true;
        lint ans = 0;
        for(i = 2; i <= n; i ){
            if(dis[i] == inf){
                flag = false;
                break;
            }
            ans = dis[i] * val[i];
        }
        if(flag) printf("%I64d\n", ans);
        else printf("No Answer\n");
    }
    return 0;
}
//*/