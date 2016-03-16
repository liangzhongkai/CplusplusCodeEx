/*
����:һ��ͼ,ͼ��ÿ���ڵ㶼������,ÿ���߶���һ����λ�۸�,������ĸ��ڵ�ı��Ϊ1,����Ҫʹ��������ܻ�����С,ÿ���ߵĻ���Ϊ�����ߵĵ�λ�۸�*(�����ߵ������ӽڵ������֮��).��������ܻ��Ѿ�Ϊ���бߵĻ����ܺ�.
    ��ΪҪ����С�Ļ���,���Կ�����������ڵ㵽ÿ���ڵ�����·,��ôÿ���ڵ����С���Ѿ���:���ڵ㵽�˽ڵ�����·*�˽ڵ������,��Ȼ�ܻ��Ѿ�Ϊÿ���ڵ�Ļ���֮��,����֤���Ӹ��ڵ㵽ÿ��������·��ɵ�ͼ�ξ���һ��������.
    ������Ŀ���������������ܴ�,������ó�������·�㷨,��ô���ᳬʱ,�Ҹ�����֪�������ֽⷨ:SPFA�������ȶ�����ʵ��Dijkstra�㷨.
    ��Ŀ�е�����ᳬ��int��Χ,����Ӧ�ò���__int64.
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
            e[j].id=v-1,  e[j].len=c,  e[j].next=p[u-1];   p[u-1]=j++;   // ����һ���ߣ�p[]��������ĳ���һ���ߵ����
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

const __int64 INF=(__int64)1<<63-1;                                   //����ϰ���ԵĲ���INF=1000000000,���һֱWA,��Ϊ����������н��������int��Χ
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

void SPFA(int s)                                                                                 //SPFA�㷨������·,sΪԴ��
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
              addedge(u,v,t);                                                                  //ע���������
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


// ʹ��SPFA����ʱ��Ϊ:625ms,
// �������ȶ�����ʵ��Dijkstra�㷨����594ms
// ����Ϊʹ�����ȶ���ʵ��Dijkstra�㷨�Ĵ���:
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

typedef pair<int,int>pii;                                                                                   //��dֵ�ͱ��"����"��һ������ŵ����ȶ�����,ʹ��pair�Զ���һ��pii����

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
     priority_queue<pii,vector<pii>,greater<pii> >q;                                                       //ʹ��greater<int>��ʾ"����"�����,�˴�������һ��С�������Ե����ȶ���
     for(i=1;i<=n;i++)
         d[i]=(i==s?0:INF);
     memset(done,0,sizeof(done));                                                                          //��ʼ�������־,���нڵ㶼û�����
     q.push(make_pair(d[s],s));                                                                            //���������ȶ���
     while(!q.empty())
     {
         pii t=q.top();
         q.pop();
         x=t.second;
         if(done[x])                                                                                       //�Ѿ������,�����
            continue;
         done[x]=true;
         for(u=head[x];u!=-1;u=e[u].next)
          if(d[e[u].to]>d[x]+e[u].w)
          {
               d[e[u].to]=d[x]+e[u].w;                                                                    //�ɳڲ���
               q.push(make_pair(d[e[u].to],e[u].to));                                                     //�������ȶ���
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




/*  ����dijkstra
//  Դ���룺(2220K 579MS)
#include<iostream>
#include<queue>
using namespace std;
const int Max = 50005;
const __int64 inf = 9999999999;
typedef __int64 lint;            //  �Ż���20��MS��
 
struct{
    int v, w, next;
}edge[2*Max];
struct node{
    int u;
    lint dis;
    bool operator < (const node &a) const{        //  heap������ < �ŵ���ʽ��
        return dis > a.dis;
    }
};
int n, m, k, edgeHead[Max], val[Max];
lint dis[Max];
bool vis[Max];
 
void add_edge(int u, int v, int w){               //  Ϊdijkstra�����ڽӱ�
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
    priority_queue<node> que;    //  ����STL�����ȶ��С�
    node a;                      
    a.u = 1; a.dis = 0;
    que.push(a);                 //  �����һ���ڵ㣬��Ϊ��㡣
    while(!que.empty()){         //  �Ż��Ļ����Զ��һ�� (&& count < n) ���жϡ�
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
        //  ����Ҫע��һ�£�һ�����п����Բ�ͬ��dis������que�У��������һ���ɳڵĵ�dis��С����������ǰ�棬���������е�ʱ��vis[u]�ͱ�Ϊtrue���ʺ���Ĳ�ֵͬ��disҲ��������ɳ��ˡ�
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
            add_edge(u, v, w);   //  ��˫��ߡ�
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