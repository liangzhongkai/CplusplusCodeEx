//*    200K	0MS	C++	3105B
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int N = 350;       // 点号有大于300的
const int INF = 0x7ffffff;

struct edge{
	int t, c, f;
	edge *next, *op;
	edge(){}
	edge(int t, int c, int f, edge* n, edge *op):t(t),c(c),f(f),next(n),op(op){}
};
edge es[N<<2], *v[N];// es数组的作用只是用来保存数据，真正使用的是v数组
int ec = 0;

char name[N][25];
int size;

int S, T;

void addedge(int s, int t, int c){
	edge e1 = edge(t, c, 0, v[s], 0);
	edge e2 = edge(s, 0, 0, v[t], 0);
	es[++ec] = e1;   v[s] = &es[ec];
	es[++ec] = e2;   v[t] = &es[ec];
	v[s]->op = v[t];   v[t]->op = v[s];
}

int find(char *s){
	int i;
	for(i=1; i<=size; i++){
		if(strcmp(s, name[i])==0)
			return i;
	}
	strcpy(name[i], s);
	size++;
	return i;
}

int maxflow=0;
int queue[N];   // 队列(双用)
int h[N];       // 高度数组
int gap[N];     // 层数数组
edge* pre[N];   // 边邻接表的调整流量必须要记录路径的边
int prev[N];

void bfs(){
	int u, t;
	int qe=1, qs=0;
	queue[0] = T;
	memset(h, -1, sizeof(h));     // 一定要赋值为-1
	h[T] = 0;                     //汇点高度为0
	memset(gap, 0, sizeof(gap));
	gap[0] = 1;                   //汇点高度为0，数量只有一个
	while(qs<qe){
		u = queue[qs++];
		for(edge *e=v[u]; e; e=e->next ){
			if(h[e->t]==-1){    // 反向边
				t = e->t;
				h[t] = h[u] + 1;
				queue[qe++] = t;
				gap[h[t]]++;
			}
		}
	}
}

void SAP(){
	bfs();

	edge *e = 0;
	int top = 0;
	int i, t;
	int minargu = INF;
	int argu;
	prev[top] = S;

	while(h[S] <= T){   // 最多是T，否则源点S与汇点出现断层
		t = prev[top];
									//printf("%d\n",t);
		for(e=v[t]; e; e=e->next){
			argu = (e->c)-(e->f);
			if(argu>0 && h[t]==h[e->t]+1){
				pre[++top] = e;    // 存储边
				prev[top] = e->t;  // 存储点
									//printf("%d\n",argu);
				if(argu < minargu)
					minargu = argu;
				break;
			}
		}
		if(e){
			if(T==prev[top]){
				for(i=top; i>0; i--){
					e = pre[i];
					e->f += minargu;
					e->op->f -= minargu;
				}
				//printf("%d\n",minargu);
				maxflow += minargu;
				minargu = INF;      // 之前没有还原最小调整量
				top = 0;
			}
		}
		else{
			i = prev[top];
			gap[h[i]]--;
			if(gap[h[i]]==0){
				break;
			}
			// 将h[top]改为后面最小的+1和gap层数+1
			h[i] = INF;
			for(e=v[i]; e; e=e->next){
				if((e->c)>(e->f) && h[e->t]+1<h[i] && h[e->t]>=0){
					h[i] = h[e->t] + 1;
				}
			}
			if(h[i]!=INF)   gap[h[i]]++;
			if(top>0)
				top--;       // 记录点的用处
		}
	}
}

int main()
{
	freopen("data.in", "r", stdin);
	int i;
	int n, m, k;
	int id1, id2;
	char t1[25], t2[25];

	memset(v, 0, sizeof(v));
	// 构图
	scanf("%d", &n);
	for(i=1; i<=n; i++){
		scanf("%s", name[i]);
	}
	size = n;

	scanf("%d", &m);
	for(i=1; i<=m; i++){
		scanf("%s %s", t1, t2);
		id1 = find(t2);
		addedge(i, m+id1, 1);
	}

	scanf("%d", &k);
	for(i=1; i<=k; i++){
		scanf("%s %s", t1, t2);
		id1 = find(t1);
		id2 = find(t2);
		//cout << id1 << "   " <<id2<< endl;
		addedge(m+id1, m+id2, INF);
	}

	S = 0 ;   T = m + size + 1;
	for(i=1; i<=m; i++){
		addedge(S, i, 1);
	}
	for(i=1; i<=n; i++){
		addedge(m+i, T, 1);
	}
	// 构图end

	SAP();
	printf("%d\n", m-maxflow);

	return 0;
}
//*/



























/*    1304K	0MS	     C++	1986B
#include <stdio.h>
#include <string.h>
#include <queue>
using std::queue;

#define min(x, y) ((x)<(y)?(x):(y))

#define MAXN 600
#define INF 100
char name[MAXN][25];
int tn, cnt, d[MAXN], cap[MAXN][MAXN];
queue <int> q;

int str_to_int(char *s)
{
    int i;
    for (i = 0; i < tn; i++)
      if (!strcmp(s, name[i]))
          return i;
    strcpy(name[i], s); // 对未出现过的特殊处理
    tn++;
    return i;
}

 

bool bfs()
{
    int i, u;
    memset(d, -1, sizeof(d));
    while (!q.empty())
        q.pop();
    q.push(0);
    d[0] = 0;
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        for (i = 1; i <= cnt; i++)
        if (cap[u][i] > 0 && d[i] == -1)
        {
            d[i] = d[u] + 1;
            q.push(i);
        }
    }
    if (d[1] >= 0)
        return true;
    return false;
}

 

int dinic(int cur, int sum)
{
    int i, os, cf;
    if (cur == 1) // end
        return sum;
    os = sum;
    for (i = 0; i <= cnt && sum; i++)
        if (cap[cur][i] > 0 && d[i] == d[cur] + 1)
        {
            cf = dinic(i, min(sum, cap[cur][i]));
            cap[cur][i] -= cf;
            cap[i][cur] += cf;
            sum -= cf;
        }
    return os - sum;
}

int main()
{
    char t1[25], t2[25];
    int i, k, t, n, m, result;
    scanf("%d", &n);
    tn = n;
    for (i = 0; i < n; i++)
        scanf("%s", name[i]);
    scanf("%d", &m);
    for (i = 2; i <= m+1; i++)
    {
        scanf("%s%s", t1, t2);
        cap[0][i] = 1; // 连入超级起点0
        t = str_to_int(t2);
        cap[i][t+2+m] = 1;
    }
    for (i = 0; i < n; i++) // 连入超级终点1，不要漏加
        cap[i+m+2][1] = 1;
    scanf("%d", &k);
    while (k--)
    {
        scanf("%s%s", t1, t2);
        cap[str_to_int(t1)+m+2][str_to_int(t2)+m+2] = INF;
    }
    cnt = tn + m + 1;
    result = 0;
    while (bfs())
        result += dinic(0, INT_MAX);
    printf("%d\n", m-result);
    return 0;
}
//*/






















/*          208K	0MS	     C++	2428B
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define inf 99999999
#define min(a,b) (a>b)?b:a
#define maxN 500
#define maxM 1000

struct point{
	int v,cow,next;
}po[maxM];

int n,num,head[maxN],Cur[maxN],gap[maxN],lev[maxN],pre_point[maxN],flow[maxM],Q[maxN];
char str[maxN][30];

void init(){
	memset(head,-1,sizeof(head));
	memset(Cur,-1,sizeof(Cur));
	memset(lev,-1,sizeof(lev));
	num=0;
}

void add(int u,int v,int cow){
	po[num].v=v;   po[num].cow=cow;
	po[num].next=head[u];   head[u]=num++;

	po[num].v=u;   po[num].cow=0;
	po[num].next=head[v];   head[v]=num++;
}
int get_id(char *st){
	for(int i=0;i<n;i++)
		if(strcmp(st,str[i])==0)
			return i;
	return -1;
}

void dfs(int t){
	int hea=-1,tail=-1;
	Q[++hea]=t;
	lev[t]=0;
	while(tail<=hea){
		int u=Q[++tail];
		gap[lev[u]]++;
		for(int i=head[u];i!=-1;i=po[i].next){
			int v=po[i].v;
			if(lev[v]==-1){
				Q[++hea]=v;
				lev[v]=lev[u]+1;
			}
		}
	}
}

int sap(int s,int t,int v)
{
	int low=inf,max_flow=0,cur=s;
	dfs(t);
	memcpy(Cur,head,sizeof(head));
	while(lev[s]<v){
		int &i=Cur[cur];    // 点cur的第一条边
		for(;i!=-1;i=po[i].next){
			if(po[i].cow-flow[i]>0 && lev[cur]==lev[po[i].v]+1){
				low=min(po[i].cow-flow[i], low);
				cur=po[i].v;
				pre_point[cur]=i;
				if(cur==t){
					while(cur!=s){
						flow[pre_point[cur]]+=low;
						flow[pre_point[cur]^1]-=low;
						cur=po[pre_point[cur]^1].v;
					}
					max_flow+=low;
					low=inf;
				}
				break;
			}
		}
		if(i==-1){
			if(--gap[lev[cur]]==0)   return max_flow;
			Cur[cur]=head[cur];
			lev[cur]=inf;
			for(int j=head[cur]; j!=-1; j=po[j].next)
				if(po[j].cow-flow[j]>0 && lev[cur]>lev[po[j].v]+1)
					lev[cur]=lev[po[j].v]+1;
			if(lev[cur]<inf)gap[lev[cur]]++;
			cur=s;
		}
	}
	return max_flow;
}

int main()
{
	int i;
	int s=0,t=1,sumN=1,m,k;
	char temp[30],res[30];

	init();
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%s",str[i]);
		add(++sumN,1,1);
	}

	scanf("%d",&m);
	for(i=0;i<m;i++){
		scanf("%s%s",temp,res);
		int id=get_id(res);
		if(id==-1)
			strcpy(str[n++],res);
		add(0,(id==-1?++sumN:(id+2)),1);    // 这里有合并边
	}

	scanf("%d",&k);
	while(k--){
		scanf("%s%s",temp,res);
		int id1,id2;
		id1=get_id(temp);
		id2=get_id(res);

		if(id1==-1){
			strcpy(str[n++],temp);
			id1=++sumN;             // 最新点
		}
		else id1+=2;

		if(id2==-1){
			strcpy(str[n++],res);
			id2=++sumN;             // 最新点
		}
		else id2+=2;
		add(id1,id2,inf);
	}

	printf("%d %d\n",m, sap(s,t,sumN+1));
	return 0;
}
//*/










/*        1292K	32MS	     C++	2010B

#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <queue>

using namespace std;

const int inf = 100000000;
const int maxN = 505;
int n, m, k, c[maxN][maxN]; 
int S, T, pre[maxN], maxFlow = 0;
map<string, int> M;           //用来计算plug的种数，从而编号
queue<int> Q;

void addFlow(int d){
    int cur = T;
    while(cur != S){
        c[pre[cur]][cur] -= d;  // 这里是容量减少了
        c[cur][pre[cur]] += d;
        cur = pre[cur];
    }
    maxFlow += d;
}

void EK(){
    while(true){
        //广搜找增广路径

        //队列初始化
        while(!Q.empty())
            Q.pop();
        Q.push(S);
        memset(pre, -1, sizeof(pre)); // 前驱子图

        while(!Q.empty()){
            int head = Q.front(); Q.pop();
			//cout << head << " ";
            for(int i=0; i<=T; i++){
                if(c[head][i] != 0 && pre[i] == -1){
                    pre[i] = head;
                    Q.push(i);
                }
            }
            if(pre[T] != -1) {//while(!Q.empty()) {cout << Q.front()<< " ";
				Q.pop(); break;}    //找到了增广路径
        }
		//cout << endl;        
		if(pre[T] == -1) return;
        else addFlow(1);
    }
}

int main()
{
    //******建图******
    string plug, device;
	int i;

    cin >> n;
    for(i=1; i<=n; i++){
        cin >> plug;
        M[plug] = i;
    }

    int t = n;
    cin >> m;
    for(i=1; i<=m; i++){
        cin >> device >> plug;
        if(M.find(plug) == M.end())
            M[plug] = ++t;         // 插座号
        c[i][m + M[plug]] = 1;     // 第i个设备与相应的插座相连。
    }

    string plug1, plug2;
    cin >> k;
    for(i=1; i<=k; i++){
        cin >> plug1 >> plug2;
        if(M.find(plug1) == M.end())
            M[plug1] = ++t;
        if(M.find(plug2) == M.end())
            M[plug2] = ++t;

        c[m + M[plug1]][m + M[plug2]] = 1;
    }

    S = 0, T = m + t + 1;   // 所有的节点号（[0, m+t+1]）
    for(i=1; i<=m; i++)
        c[S][i] = 1;
    for(i=1; i<=n; i++)
        c[m+i][T] = 1;

	//******建图结束******

    //最大流算法
    EK();

    cout << m - maxFlow << endl;


    return 0;
}
//*/
