//*   2314 C++ 1400 2260 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

const int maxn = 210;
const int INF = 100000000;   // 无边

#define MIN(a, b) ((a)>(b)?(b):(a))

int n, m;

struct ArcType{
	int b, c, f;
	int no;
};
ArcType Edge[maxn][maxn];
ArcType AccEdge[maxn][maxn];
int flag[maxn];
int prev[maxn];
int alpha[maxn];
int queue[maxn];
int v, qs, qe;

//bool cmp(const ArcType &a, const ArcType &b){
//	return a.no<b.no;
//}

int cmp(const void *a, const void *b){
	return ((ArcType *)a)->no - ((ArcType *)b)->no;
}

void Ford(ArcType network[][maxn], int s, int t){
	int i;
	while(1){
		memset(flag, -1, sizeof(flag));
		memset(prev, -1, sizeof(prev));
		memset(alpha, -1, sizeof(alpha));
		flag[s] = 0;   prev[s] = 0;   alpha[s] = INF; 
		qs = qe = 0; 
		queue[qe++] = s;
		while(qs<qe && flag[t]==-1){
			v = queue[qs++];
			for(i=s; i<=t; i++){
				if(flag[i]==-1){
					if(network[v][i].c<INF && network[v][i].c>network[v][i].f){
						flag[i] = 0;   prev[i] = v;
						alpha[i] = MIN(alpha[v], network[v][i].c-network[v][i].f);
						queue[qe++] = i;
					}
					else if(network[i][v].c<INF && network[i][v].f>network[i][v].b){
						flag[i] = 0;   prev[i] = -v;
						alpha[i] = MIN(alpha[v], network[i][v].f-network[i][v].b);
						queue[qe++] = i;
					}
				}
			}
			flag[v] = 1;
		}

		if(flag[t]==-1 || alpha[t]==0)   break;

		int k1 = t, k2 = abs(prev[k1]), a = alpha[t];
		while(1){
			if(network[k2][k1].f<INF)   network[k2][k1].f += a;
			else   network[k1][k2].f -= a;
			if(k2==s)   break;
			k1 = k2;   k2 = abs(prev[k2]);
		}
	}
}

void accompany(){
	memcpy(AccEdge, Edge, sizeof(Edge));
	int i, j;
	// 新的源点和新的汇点
	for(i=1; i<=n; i++){
		int sum1 = 0, sum2 = 0;
		for(j=1; j<=n; j++){
			if(AccEdge[i][j].b!=INF)   sum1 += AccEdge[i][j].b;
			if(AccEdge[j][i].b!=INF)   sum2 += AccEdge[j][i].b;
		}
		if(sum2>sum1){
			AccEdge[0][i].c = sum2 - sum1,   AccEdge[0][i].b = AccEdge[0][i].f = 0;
		}
		else{
			AccEdge[i][n+1].c = sum1 - sum2,   AccEdge[i][n+1].b = AccEdge[i][n+1].f = 0;
		}
	}
	// 更改原网络对应在伴随网络的边
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			if(AccEdge[i][j].c!=INF){
				AccEdge[i][j].c -= AccEdge[i][j].b;
				AccEdge[i][j].b = 0;
			}
		}
	}

	Ford(AccEdge, 0, n+1);

	bool feasible = 1;
	for(i=0; i<=n+1; i++){
		if(AccEdge[0][i].c!=INF && AccEdge[0][i].f!=AccEdge[0][i].c){
			 feasible = 0;
			 break;
		}
	}
	if(feasible==0){   printf("NO\n");   return ;}
	else   printf("YES\n");

	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			if(Edge[i][j].c!=INF){
				Edge[i][j].f = AccEdge[i][j].f + Edge[i][j].b;
			}
		}
	}

	//Ford(Edge, 1, n);   // 不需要求原网络的最大流？？？？
	//sort(Edge, Edge+(maxn*maxn), cmp);
	qsort(Edge, maxn*maxn, sizeof(Edge[0][0]), cmp);
	for(i=0; i<m; i++)   printf("%d\n", Edge[i/m][i%m].f);
}

void readcase(){
	int i, j;
	int u, v, b, c;
	scanf("%d %d", &n, &m);
	for(i=0; i<maxn; i++){
		for(j=0; j<maxn; j++){
			Edge[i][j].b = Edge[i][j].c = Edge[i][j].f = Edge[i][j].no = INF;
		}
	}
	for(i=1; i<=m; i++){
		scanf("%d%d%d%d", &u, &v, &b, &c);
		Edge[u][v].b = b;
		Edge[u][v].c = c;
		Edge[u][v].f = 0;
		Edge[u][v].no = i;
	}
}

int main()
{
	int tc;
	scanf("%d", &tc);
	while(tc--){
		readcase();
		accompany();
		printf("\n");
	}

	return 0;
}
//*/

/*        这种构图是错误的！
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

const int maxn = 210;
const int INF = 100000000;   // 无边
const int INF1 = 30000000;   // 伴随网络新增的两条边

#define MIN(a, b) ((a)>(b)?(b):(a))

int n, m;

struct ArcType{
	int b, c, f;
	int no;
};
ArcType Edge[maxn][maxn];
ArcType AccEdge[maxn][maxn];
int flag[maxn];
int prev[maxn];
int alpha[maxn];
int queue[maxn];
int v, qs, qe;

//bool cmp(const ArcType &a, const ArcType &b){
//	return a.no<b.no;
//}

int cmp(const void *a, const void *b){
	return ((ArcType *)a)->no - ((ArcType *)b)->no;
}

void Ford(ArcType network[][maxn], int s, int t){
	int i;
	while(1){
		memset(flag, -1, sizeof(flag));
		memset(prev, -1, sizeof(prev));
		memset(alpha, -1, sizeof(alpha));
		flag[s] = 0;   prev[s] = 0;   alpha[s] = INF; 
		qs = qe = 0; 
		queue[qe++] = s;
		while(qs<qe && flag[t]==-1){
			v = queue[qs++];
			for(i=s; i<=t; i++){
				if(flag[i]==-1){
					if(network[v][i].c<INF && network[v][i].c>network[v][i].f){
						flag[i] = 0;   prev[i] = v;
						alpha[i] = MIN(alpha[v], network[v][i].c-network[v][i].f);
						queue[qe++] = i;
					}
					else if(network[i][v].c<INF && network[i][v].f>network[i][v].b){
						flag[i] = 0;   prev[i] = -v;
						alpha[i] = MIN(alpha[v], network[i][v].f-network[i][v].b);
						queue[qe++] = i;
					}
				}
			}
			flag[v] = 1;
		}

		if(flag[t]==-1 || alpha[t]==0)   break;

		int k1 = t, k2 = abs(prev[k1]), a = alpha[t];
		while(1){
			if(network[k2][k1].f<INF)   network[k2][k1].f += a;
			else   network[k1][k2].f -= a;
			if(k2==s)   break;
			k1 = k2;   k2 = abs(prev[k2]);
		}
	}
}

void accompany(){
	memcpy(AccEdge, Edge, sizeof(Edge));
	int i, j;
	// 新的源点和新的汇点
	for(i=1; i<=n; i++){
		int sum1 = 0, sum2 = 0;
		for(j=1; j<=n; j++){
			if(AccEdge[i][j].b!=INF)   sum1 += AccEdge[i][j].b;
			if(AccEdge[j][i].b!=INF)   sum2 += AccEdge[j][i].b;
		}
		AccEdge[0][i].c = sum2;   AccEdge[0][i].b = AccEdge[0][i].f = 0;  
		AccEdge[i][n+1].c = sum1;   AccEdge[i][n+1].b = AccEdge[i][n+1].f = 0;
	}
	// 更改原网络对应在伴随网络的边
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			if(AccEdge[i][j].c!=INF){
				AccEdge[i][j].c -= AccEdge[i][j].b;
				AccEdge[i][j].b = 0;
			}
		}
	}
	// 新增两条边
	AccEdge[1][n].c = AccEdge[n][1].c = INF1;
	AccEdge[1][n].b = AccEdge[n][1].b = 0;
	AccEdge[1][n].f = AccEdge[n][1].f = 0;

	Ford(AccEdge, 0, n+1);

	bool feasible = 1;
	for(i=0; i<=n+1; i++){
		if(AccEdge[0][i].c!=INF && AccEdge[0][i].f!=AccEdge[0][i].c){
			 feasible = 0;
			 break;
		}
	}
	if(feasible==0){   printf("NO\n");   return ;}
	else   printf("YES\n");

	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			if(Edge[i][j].c!=INF){
				Edge[i][j].f = AccEdge[i][j].f + Edge[i][j].b;
			}
		}
	}

	//Ford(Edge, 1, n);   // 不需要求原网络的最大流？？？？
	//sort(Edge, Edge+(maxn*maxn), cmp);
	qsort(Edge, maxn*maxn, sizeof(Edge[0][0]), cmp);
	for(i=0; i<m; i++)   printf("%d\n", Edge[i/m][i%m].f);
}

void readcase(){
	int i, j;
	int u, v, b, c;
	scanf("%d %d", &n, &m);
	for(i=0; i<maxn; i++){
		for(j=0; j<maxn; j++){
			Edge[i][j].b = Edge[i][j].c = Edge[i][j].f = Edge[i][j].no = INF;
		}
	}
	for(i=1; i<=m; i++){
		scanf("%d%d%d%d", &u, &v, &b, &c);
		Edge[u][v].b = b;
		Edge[u][v].c = c;
		Edge[u][v].f = 0;
		Edge[u][v].no = i;
	}
}

int main()
{
	int tc;
	scanf("%d", &tc);
	while(tc--){
		readcase();
		accompany();
		printf("\n");
	}

	return 0;
}
//*/