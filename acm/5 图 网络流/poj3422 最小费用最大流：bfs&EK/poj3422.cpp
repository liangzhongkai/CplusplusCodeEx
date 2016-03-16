//     2232K	219MS	C++	3870B
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

#define INF 10000000
#define MAXN 5100

struct edge{
	int next;
	int f, c, w;
}N, P;

vector<edge> map[MAXN];
int s, t, n, k;
int queue[MAXN*1000];
int cost[MAXN];
int pre[MAXN];
int m[51][51];

bool spfa(){
	int i, H=0, T=0, cur;
	pre[s] = 0;
	for(i=0; i<=t; i++)   cost[i] = INF;
	cost[s] = 0;   queue[T++] = s;
	while(H<T){
		cur = queue[H++];
		for(i=0; i<map[cur].size(); i++){
			N = map[cur][i];
			if(N.c-N.f>0 && cost[N.next]>cost[cur]+N.w ){
				cost[N.next] = cost[cur] + N.w;
				pre[N.next] = cur;
				queue[T++] = N.next;    // 只是普通的bfs(),,,不是已在队列的不能再进入吗?????????????????????????
			}
		}
	}
	if(cost[t]!=INF)   return 1;
	else return 0;
}

int argument(){
	 int i, j, min=INF;
	 for(i=t; i!=s; i=pre[i]){
		 for(j=0; j<map[pre[i]].size(); j++){
			 if(map[pre[i]][j].next==i && map[pre[i]][j].c-map[pre[i]][j].f<min)
					min = map[pre[i]][j].c - map[pre[i]][j].f;
		 }
	 }
	 for(i=t; i!=s; i=pre[i]){
		 for(j=0; j<map[pre[i]].size(); j++){
			 if(map[pre[i]][j].next==i)
				map[pre[i]][j].f += min;
		 }
	 }
	 for(i=t; i!=s; i=pre[i]){
		 for(j=0; j<map[i].size(); j++){
			 if(map[i][j].next==pre[i])
				map[i][j].f -= min;
		 }
	 }
	 return min*cost[t];   // min 恒= 1
}

int maxcostflow(){
	int Flow = 0;
	while(spfa()){
		Flow += argument();
	}
	return Flow;
}

void build(){
	int i;

	// 头尾两点 连接 矩阵的边
	N.c = k;   N.f = 0;   N.next = 1;   N.w = 0;   
	map[s].push_back(N);
	N.c = 0;   N.f = 0;   N.next = s;   N.w = 0; 
	map[1].push_back(N);
	N.c = k;   N.f = 0;   N.next = t;   N.w = 0;
	map[2*n*n].push_back(N);
	N.c = 0;   N.f = 0;   N.next = 2*n*n;   N.w = 0;
	map[t].push_back(N);

	// 矩阵节点分裂，每个点演变1条边，因为边邻接表表示，所以构图时要弄一个反向边
	for(i=1; i<=n*n; i++){
		N.c = 1;   N.f = 0;   N.next = n*n+i;   N.w = -m[(i-1)/n+1][(i-1)%n+1];
		map[i].push_back(N);
		N.c = 0;   N.f = 0;   N.next = i;   N.w = m[(i-1)/n+1][(i-1)%n+1];
		map[i+n*n].push_back(N);
	}

	// 分裂之后，原本相邻点的连接
	for(i=1; i<=n*n; i++){
		// i不在最后一列
		if(i%n!=0){   
			// 原本点邻接右边原本点
			N.c = INF,   N.f = 0,   N.next = i+1,   N.w = 0;
			map[i].push_back(N);
			N.c = 0,   N.f = 0,   N.next = i,   N.w = 0;
			map[i+1].push_back(N);
			// 分身点邻接右边分身点
			N.c = INF,   N.f = 0,   N.next = n*n+i+1,   N.w = 0;
			map[n*n+i].push_back(N);
			N.c = 0,   N.f = 0,   N.next = n*n+i,   N.w = 0;
			map[n*n+i+1].push_back(N);
			// 原本点邻接右边分身点
			N.c = INF,   N.f = 0,   N.next = n*n+i+1,   N.w = 0;
			map[i].push_back(N);
			N.c = 0,   N.f = 0,   N.next = i,   N.w = 0;
			map[i+1+n*n].push_back(N);
			// 分身点邻接右边原本点
			N.c = INF,   N.f = 0,   N.next = i+1,   N.w = 0;
			map[i+n*n].push_back(N);
			N.c = 0,   N.f = 0,   N.next = i+n*n,   N.w = 0;
			map[i+1].push_back(N);
		}
		// i不在最后一行
		if(i<=n*(n-1)){ 
			// 原本点邻接下面原本点
			N.c = INF,   N.f = 0,   N.next = i+n,   N.w = 0;
			map[i].push_back(N);
			N.c = 0,   N.f = 0,   N.next = i,   N.w = 0;
			map[i+n].push_back(N);
			// 分身点邻接下面分身点
			N.c = INF,   N.f = 0,   N.next = i+n+n*n,   N.w = 0;
			map[n*n+i].push_back(N);
			N.c = 0,   N.f = 0,   N.next = i+n*n,   N.w = 0;
			map[i+n+n*n].push_back(N);
			// 原本点邻接下面分身点
			N.c = INF,   N.f = 0,   N.next = i+n+n*n,   N.w = 0;
			map[i].push_back(N);
			N.c = 0,   N.f = 0,   N.next = i,   N.w = 0;
			map[i+n+n*n].push_back(N);
			// 分身点邻接原本点
			N.c = INF,   N.f = 0,   N.next = i+n,   N.w = 0;
			map[i+n*n].push_back(N);
			N.c = 0,   N.f = 0,   N.next = i+n*n,   N.w = 0;
			map[i+n].push_back(N);
		}
	}
}

int main()
{
	int i, j;
	while(scanf("%d %d", &n, &k)!=EOF){
		s = 0,   t = 2*n*n+1;
		for(i=1; i<=n; i++){
			for(j=1; j<=n; j++){
				scanf("%d", &m[i][j]);
			}
		}
		for(i=0; i<=t; i++){
			map[i].clear();
		}
		build();
		printf("%d\n", -maxcostflow());
	}

	return 0;
}