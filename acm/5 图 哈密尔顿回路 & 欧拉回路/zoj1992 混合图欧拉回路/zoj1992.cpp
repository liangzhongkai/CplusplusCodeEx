//*     C++ 	10ms 	220kb
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
 
using namespace std;
 
#define REP(i,n) for(int i=0;i<(n);++i)
#define FOR(i,l,h) for(int i=(l);i<=(h);++i)
#define FORD(i,h,l) for(int i=(h);i>=(l);--i)
 
const int N=202;
const int E=2220;
const int oo=1000000000;
 
int node,src,dest,ne;
int head[N],dist[N],Q[N],work[N];
int pnt[E],nxt[E],flow[E],cap[E];
int indeg[N],outdeg[N];
int n,m;
 
void init(int _node,int _src,int _dest)
{
    node=_node;
    src=_src;
    dest=_dest;
    fill(head,head+node,-1);
    memset(indeg,0,sizeof(indeg));
    memset(outdeg,0,sizeof(outdeg));
    ne=0;
}
void add(int u,int v,int c)
{
    pnt[ne]=v,cap[ne]=c,flow[ne]=0,nxt[ne]=head[u],head[u]=ne++;
    pnt[ne]=u,cap[ne]=0,flow[ne]=0,nxt[ne]=head[v],head[v]=ne++;
}
bool dinic_bfs(void)
{
    memset(dist,255,sizeof(dist));
    dist[src]=0;
    int sizeQ=0;
    Q[sizeQ++]=src;
    REP(cl,sizeQ)   for(int k=Q[cl],i=head[k];i>=0;i=nxt[i])
        if(flow[i]<cap[i] && dist[pnt[i]]<0)
        {
            dist[pnt[i]]=dist[k]+1;
            Q[sizeQ++]=pnt[i];
        }
    return dist[dest]>=0;
}
int dinic_dfs(int x,int exp)
{
    if(x==dest) return exp;
    for(int &i=work[x];i>=0;i=nxt[i])
    {
        int v=pnt[i],tmp;
        if(flow[i]<cap[i] && dist[v]==dist[x]+1 && (tmp=dinic_dfs(v,min(exp,cap[i]-flow[i])))>0)
        {
            flow[i]+=tmp;
            flow[i^1]-=tmp;
            return tmp;
        }
    }
    return 0;
}
int dinic_flow(void)
{
    int res=0;
    while(dinic_bfs())
    {
        REP(i,node) work[i]=head[i];
        while(1)
        {
            int delta=dinic_dfs(src,oo);
            if(delta==0)    break;
            res+=delta;
        }
    }
    return res;
}
int main(void)
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        init(n+2,0,n+1);
        REP(i,m)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            outdeg[u]++;
            indeg[v]++;
            if(!w)  add(u,v,1);
        }
        bool flag=0;
        FOR(i,1,n)  if(abs(outdeg[i]-indeg[i])&1)
        {
            flag=1;
            break;
        }
        if(flag)
        {
            puts("impossible");
            continue;
        }
        int sum=0;
        FOR(i,1,n)
        {
            int x=(outdeg[i]-indeg[i])/2;
            if(x>0)
            {
                add(src,i,x);
                sum+=x;
            }
            else    add(i,dest,-x);
        }
        int res=dinic_flow();
        if(sum==res)    puts("possible");
        else    puts("impossible");
    }
    return 0;
}
//*/
























