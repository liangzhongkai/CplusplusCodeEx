#include<iostream>

using namespace std;

#define MAXN 10
#define INF1 1000000               // 无边
#define INF2 10000                 // 最大流量值
#define MIN(a,b) ((a)<(b)?(a):(b))

struct ArcType{
	int b, c, f;
};
ArcType Edge[MAXN+2][MAXN+2];      // 原网络
ArcType AccEdge[MAXN+2][MAXN+2];   // 伴随网络
int n, m;                          // 顶点个数，弧的数目
int flag[MAXN+2];                  // -1为未标记，0已标记为检查，1标记且检查
int prev[MAXN+2];                  // 父子跳表
int alpha[MAXN+2];                 // 改进量
int queue[MAXN+2];                 // bfs队列
int v;                             // 队头元素
int qs, qe;

// max = -1时，计算伴随网络的最大流
// max = 1 时，计算原网络的最大流
// max = 0 时，计算原网络的最小流
// 这种写法是最正规的！
void Ford(ArcType network[][MAXN+2], int s, int t, int max){
	int i, j;
	while(1){
		memset(flag, -1, sizeof(flag));
		memset(prev, -1, sizeof(prev));
		memset(alpha, -1, sizeof(alpha));

		flag[s] = 0;   prev[s] = 0;   alpha[s] = INF1;
		qs = qe = s;   queue[qe++] = s;
		while(qs<qe && flag[t]==-1){
			v = queue[qs++];
			for(i=s; i<=t; i++){
				if(flag[i]==-1){
					if(network[v][i].c<INF1 && network[v][i].f<network[v][i].c){
						flag[i] = 0;   prev[i] = v;
						alpha[i] = MIN(alpha[v], network[v][i].c-network[v][i].f);
						queue[qe++] = i;
					}
					else if(network[i][v].c<INF1 && network[i][v].f>network[i][v].b){ // 当求原网络的时候，不可以破坏下界的底线
						flag[i] = 0;   prev[i] = -v;
						alpha[i] = MIN(alpha[v], network[i][v].f-network[i][v].b);
						queue[qe++] = i;
					}
				}
			}
			flag[v] = 1;
		}

		if(flag[t]==-1 || alpha[t]==0)   break;

		int k1 = t, k2 = abs(prev[k1]);
		int a = alpha[t];
		while(1){                        // 网络本来有可行流时，不可以正反同时更新流量
			if(network[k2][k1].f<INF1){
				network[k2][k1].f += a;
			}
			else
				network[k1][k2].f -= a;
			if(k2==s)   break;
			k1 = k2;    k2 = abs(prev[k2]);
		}
	}//  FF算法结束

	int maxflow = 0;
	for(i=s; i<=t; i++){
		for(j=s; j<=t; j++){
			if(i==s && network[i][j].f<INF1)
				maxflow += network[i][j].f;
			if(i==s && network[j][i].f<INF1)
				maxflow -= network[j][i].f;
			if(network[i][j].c<INF1 && network[i][j].f<INF1)  
				printf("%d->%d : %d\n", i, j, network[i][j].f);
		}
	}
	if(max)   printf("maxflow : %d\n", maxflow);
	else    printf("minflow : %d\n", -maxflow);
}

int accompany(){
	memcpy(AccEdge, Edge, sizeof(Edge));      // 将 原网络 复制到 伴随网络 中
	int i, j;
	int sum1, sum2;

	// ///////////////////////////构造伴随网络/////////////////////////////////////////////////
	// 源点为0，汇点未n+1
	for(i=1; i<=n; i++){
		sum1 = sum2 = 0;
		for(j=0; j<=n; j++){
			if(AccEdge[i][j].b!=INF1)   sum1 += AccEdge[i][j].b;
			if(AccEdge[j][i].b!=INF1)   sum2 += AccEdge[j][i].b;
		}
		AccEdge[i][n+1].c = sum1;   AccEdge[i][n+1].b = AccEdge[i][n+1].f = 0;
		AccEdge[0][i].c = sum2;   AccEdge[0][i].b = AccEdge[0][i].f = 0;
	}
	// 改变原网络的边
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			if(AccEdge[i][j].c!=INF1){
				AccEdge[i][j].c = AccEdge[i][j].c - AccEdge[i][j].b;
				AccEdge[i][j].b = 0;
			}
		}
	}
	// 原网络的源点与汇点之间的边
	AccEdge[1][n].c = AccEdge[n][1].c = INF2;
	AccEdge[1][n].b = AccEdge[n][1].b = 0;
	AccEdge[1][n].f = AccEdge[n][1].f = 0;
	/////////////////////////////////////////////////////////////////////////////////////////////

	// 求出伴随网络最大流
	Ford(AccEdge, 0, n+1, -1);

	// 判断该最大流是否可行流, 从0点出发的边流量都要爆满
	bool feasible = 1;
	for(i=0; i<=n+1; i++){
		if(AccEdge[0][i].c!=INF1 && AccEdge[0][i].f!=AccEdge[0][i].c)
			feasible = 0;
	}

	// 如果没有可行流
	if(feasible==0){
		printf("No feasible network flow.\n");
		return 0;
	}

	// 更改原网络的可行流 （ 不计算伴随网络新增的源点和汇点 ）
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			if(Edge[i][j].c!=INF1){
				Edge[i][j].f = AccEdge[i][j].f + Edge[i][j].b;
			}
		}
	}

	// 原网络的最大流 ( 注意：已经改变了原网络的可行流流量 )
	Ford(Edge, 1, n, 1);

	// 恢复到原网络的可行流 == 更改原网络的可行流过程
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			if(Edge[i][j].c!=INF1)
				Edge[i][j].f = AccEdge[i][j].f + Edge[i][j].b;
		}
	}

	// 图形上是交换原网络的源点和汇点的位置
	int b, c, f;
	for(i=1; i<=n; i++){
		b = Edge[1][i].b;   c = Edge[1][i].c;   f = Edge[1][i].f;
		Edge[1][i].b = Edge[n][i].b;   Edge[1][i].c = Edge[n][i].c;   Edge[1][i].f = Edge[n][i].f;
		Edge[n][i].b = b;   Edge[n][i].c = c;   Edge[n][i].f = f;

		b = Edge[i][1].b;   c = Edge[i][1].c;   f = Edge[i][1].f;
		Edge[i][1].b = Edge[i][n].b;   Edge[i][1].c = Edge[i][n].c;   Edge[i][1].f = Edge[i][n].f;
		Edge[i][n].b = b;   Edge[i][n].c = c;   Edge[i][n].f = f;
	}

	// 原网络的最小流
	Ford(Edge, 1, n, 0);

	return 1;
}


int readcase()
{
	int i, j, u, v, b, c;
	scanf("%d%d", &n, &m);
	if(n==0 && m==0)   return 0;

	for(i=0; i<MAXN+2; i++){
		for(j=0; j<MAXN+2; j++){
			Edge[i][j].b = Edge[i][j].c = Edge[i][j].f = INF1;
		}
	}

	for(i=1; i<=m; i++){
		scanf("%d%d%d%d", &u, &v, &b, &c);
		Edge[u][v].b = b;
		Edge[u][v].c = c;
		Edge[u][v].f = 0;
	}

	return 1;
}

int main()
{
	while(readcase())
		accompany();

	return 0;
}

/*
6 8
1 2 1 10
2 4 2 8
3 1 1 3
3 5 5 7
4 3 2 8
5 2 1 3
5 6 3 5
6 4 2 6
*/