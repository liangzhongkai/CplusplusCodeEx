#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

#define MAXN 1000
#define INF 1000000
#define MIN(a,b) ((a)<(b)?(a):(b))

struct ArcType{
	int c, f;
};

ArcType Edge[MAXN][MAXN];
int n, m;
int flag[MAXN];
int prev[MAXN];
int alpha[MAXN];
int queue[MAXN];
int v;
int qs, qe;
int i, j;

void Ford(){
	while(1){
		memset(flag, 0xff, sizeof(flag)); // -1
		memset(prev, 0xff, sizeof(prev)); // -1
		memset(alpha, 0xff, sizeof(alpha)); // -1
		flag[0] = 0, prev[0] = 0, alpha[0] = INF;
		qs = qe = 0;
		queue[qe++] = 0;   // 0入队

		while(qs<qe && flag[n-1]==-1){
			v = queue[qs++];

			// 开始标号
			for(i=0; i<n; i++){   
				if(flag[i]==-1){
					// 向前边为满
					if(Edge[v][i].c<INF && Edge[v][i].f<Edge[v][i].c){
						flag[i] = 0;   prev[i] = v;
						alpha[i] = MIN(alpha[v], Edge[v][i].c-Edge[v][i].f);
						queue[qe++] = i;
					}
					// 向后边为满
					else if(Edge[i][v].c<INF && Edge[i][v].f>0){
						flag[i] = 0;   prev[i] = v;
						alpha[i] = MIN(alpha[v], Edge[i][v].f);
						queue[qe++] = i;
					}
				}
			}

			// 检查完毕
			flag[v] = 1;
		}

		// 没被标号 || 调整量为0
		if(flag[n-1]==-1 || alpha[n-1]==0)   break;

		// 调整流量
		int k1 = n-1, k2 = abs(prev[k1]);
		int a = alpha[n-1];
		while(1){
			if(Edge[k2][k1].f<INF){
				Edge[k2][k1].f += a;
			}
			else
				Edge[k1][k2].f -= a;
			if(k2==0)   break;
			k1 = k2;   k2 = abs(prev[k2]);
		}
	}//  整个算法至此结束
		
	// 输出
	int maxFlow = 0;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(i==0 && Edge[i][j].f<INF){
				maxFlow += Edge[i][j].f;
			}
			if(Edge[i][j].f<INF)   
				printf("%d->%d:%d\n", i, j, Edge[i][j].f);
		}
	}
	printf("maxflow:%d\n", maxFlow);
}

int main()
{
	int u, v, c, f;
	scanf("%d%d", &n, &m);
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			Edge[i][j].c = Edge[i][j].f = INF;
		}
	}
	for(i=0; i<m; i++){
		scanf("%d%d%d%d", &u, &v, &c, &f);
		Edge[u][v].c = c;   Edge[u][v].f = f;
	}
	Ford();
	return 0;
}

/*
6 10
0 1 8 2
0 2 4 3
1 3 2 2
1 4 2 2
2 1 4 2
2 3 1 1
2 4 4 0
3 4 6 0
3 5 9 3
4 5 7 2

*/