#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

const int MAXN=1003,MAXM=10002*4,INF=0x7FFFFFFF;

using namespace std;

struct edge{
	edge *next, *op;
	int t, c, v;
}ES[MAXM],*V[MAXN];

struct Queue{     // 特别为spfa而设计的队列
	int Q[MAXN],QH,QL,Size;
	bool inq[MAXN];
	inline void ins(int v)
	{
		if (++QL>=MAXN)
			QL=0;
		Q[QL]=v;
		inq[v]=true;
		Size++;
	}
	inline int pop()
	{
		int r=Q[QH];
		inq[r]=false;
		Size--;
		if (++QH>=MAXN)
			QH=0;
		return r;
	}
	inline void reset()
	{
		memset(Q,0,sizeof(Q));
		QH=Size=0;
		QL=-1;
	}
}Q;

int N,M,S,T,EC=-1;
int demond[MAXN],sp[MAXN],prev[MAXN];
edge *path[MAXN];

//                  起点  终点  权值  容量
inline void addedge(int a,int b,int v,int c=INF){
	edge e1={V[a],0,b,c,v} , e2={V[b],0,a,0,-v};
	ES[++EC]=e1; V[a]=&ES[EC];
	ES[++EC]=e2; V[b]=&ES[EC];
	//V[a] = &e1;   V[b] = &e2;    因为这里是局部函数，e1,e2的内存会释放，V[i]第i点的头边指针也会失效
    V[a]->op=V[b]; V[b]->op=V[a];
}

void init(){
	int i, a, b, c;
	freopen("employee.in","r",stdin);
	//freopen("employee.out","w",stdout);
	scanf("%d%d",&N,&M);

	for (i=1;i<=N;i++)
		scanf("%d",&demond[i]);

	for (i=1;i<=M;i++){
		scanf("%d%d%d",&a,&b,&c);
		addedge(a,b+1,c);         // 红边
	}
	S=0,T=N+2;
	for (i=1;i<=N+1;i++){
		c = demond[i] - demond[i-1];
		if (c>=0)
			addedge(S,i,0,c);     // 源点的边
		else 
			addedge(i,T,0,-c);    // 汇点的边
		if (i>1)
			addedge(i,i-1,0);     // 蓝边
	}
}

bool spfa(){
	int u,v;
	for (u=S;u<=T;u++)
		sp[u]=INF;
	Q.reset();
	Q.ins(S);
	sp[S]=0;
	prev[S]=-1;
	while (Q.Size){
		u=Q.pop();
		for (edge *k=V[u];k;k=k->next){
			v=k->t;
			//  容量大于0，更新权值至最小
			if (k->c>0 && sp[u] + k->v <sp[v]){
				sp[v]=sp[u] + k->v;
				prev[v]=u;     // 存储 前驱结点
				path[v]=k;     // 存储 边 
				if (!Q.inq[v])
					Q.ins(v);
			}
		}
	}
	return sp[T]!=INF;
}

int argument(){
	int i,delta=INF,flow=0;
	edge *e;

	for (i=T;prev[i]!=-1;i=prev[i]){   // 最小调整量
		e=path[i];
		if (e->c<delta)
			delta=e->c;
	}

	for (i=T;prev[i]!=-1;i=prev[i]){   // 调整
		e=path[i];
		e->c-=delta;
		e->op->c+=delta;
		flow+=e->v*delta;
	}

	return flow;
}

int maxcostflow(){            // 最小费用最大流
	int Flow=0;
	while (spfa())            // 先求最小费用的路径
		Flow += argument();   // 然后沿着该路径，更新流量
	return Flow;
}

int main()
{
	init();
	printf("%d\n",maxcostflow());
	return 0;
}