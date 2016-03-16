

/*      704K	32MS	C++	5939B
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

#define INF 10000000
#define N 300
#define KN 205
#define KM 25
#define max(a, b) ((a)>(b)?(a):(b))
#define min(a, b) ((a)>(b)?(b):(a))

struct edge{
	int c, f, low, x, y;
	edge *nex, *bak;     // 下一条边   反向边
	edge(){}
	edge(int x, int y, int c, int f, int low, edge *nex):
	x(x), y(y), c(c), f(f), low(low),nex(nex), bak(0){}
	void *operator new(size_t, void *p){
		return p;
	}
}*E[N];

struct NODE{
	int low, high;
};

int S, T, m;
int Q[100000];       // 找层次网络的队列
int D[N];            // D[]数组是层次网络的标记，-1不在网络中, +1的关系

edge *cur[N], *path[N];
edge *base, *data, *it;

NODE limit[KN][KM];
int sumn[KN], summ[KM];
int kn, km;

//////////////////////////////////// DINIC求最大流 ///////////////////////////////////////////////
void bfs(){
	memset(D, -1, sizeof(D));
	int i, j, p1=0, p2=0;
	Q[p2++] = S;  D[S] = 0;
	while(p1<p2){
		i = Q[p1++];
		for(edge *e=E[i]; e; e=e->nex){
			if(e->c==0)   continue;
			j = e->y;
			if(-1==D[j]){
				Q[p2++] = j;   
				D[j] = D[i] + 1;
				if(j==T)   return ;
			}
		}
	}
}
int dinic(){
	int i, k, mink, d, flow = 0, path_n;
	while(1){
		bfs();      // 建层次图
		if(D[T]==-1)   break;
		memcpy(cur, E, sizeof(E));
		path_n = 0;
		i = S;
		while(1){
			if(i==T){
				mink = 0,   d = INF;
				for(k=0; k<path_n; k++){
					if(path[k]->c < d){
						d = path[k]->c;   mink = k;
					}
				}
				// 调整流量
				for(k=0; k<path_n; k++){
					(path[k]->c) -= d;
					((path[k]->bak)->c) += d;
				}
				path_n = mink;   i = path[path_n]->x;   flow += d;
			}
			// i为上面增广路失效边的起点
			edge *e;
			for(e=cur[i]; e; e=e->nex){
				if(!e->c)   continue;
				int j = e->y;
				if(D[i]+1==D[j])   break;
			}
			cur[i] = e;
			if(e){
				path[path_n++] = e;   i = e->y;
			}
			else{
				D[i] = -1;
				if(!path_n)   break;   //栈顶指针为0
				path_n--;   i = path[path_n]->x;
			}
		}
	}
	return flow;
}
///////////////////////////////////////// DINIC求最大流 //////////////////////////////////////////////////

///////////////////////////////////////// 是否有可行流 ////////////////////////////////////////////////////
bool isok(){
	for(edge *e=E[S]; e; e=e->nex){
		if(e->c)   return 0;
	}
	return 1;
}

void print(int ok){
	int i, j;
	if(ok==-1)   printf("IMPOSSIBLE\n");
	else{
		for(i=0, it=base; i<kn; i++){
			for(j=0; j<km; j++, it+=2)
				printf("%d ", it->f - it->c + it->low);
			printf("\n");
		}
	}
	printf("\n");
}
//////////////////////////////////////////// 是否有可行流 //////////////////////////////////////////////////

////////////////////////////////////////// // 构图的要求 //////////////////////////////////////////////////////
int setlimit(int x, int y, char op, int v){
	if(op=='='){
		if(v>limit[x][y].high)   return 0;
		if(v<limit[x][y].low)   return 0;
		limit[x][y].high = limit[x][y].low = v;
	}
	else if(op=='>'){
		limit[x][y].low = max(limit[x][y].low, v+1);
	}
	else if(op=='<'){
		limit[x][y].high = min(limit[x][y].high, v-1);
	}
	if(limit[x][y].low>limit[x][y].high)   return 0;
	return 1;
}

int build(){
	int i, j, T, ok = 1;
	scanf("%d%d", &kn, &km);
	for(i=1; i<=kn; i++)   scanf("%d", &sumn[i]);
	for(i=1; i<=km; i++)   scanf("%d", &summ[i]);

	for(i=1; i<=kn; i++){
		for(j=1; j<=km; j++){
			limit[i][j].low = 0;  limit[i][j].high = INF;
		}
	}
	scanf("%d", &T);
	while(T--){
		int x, y, v;
		char op[2];
		scanf("%d%d%s%d", &x, &y, op, &v);
		if(!x && !y){
			for(i=1; i<=kn; i++){
				for(j=1; j<=km; j++){
					if(!setlimit(i, j, op[0], v))   ok = 0;
				}
			}
		}
		else if(!x && y){
			for(i=1; i<=kn; i++){
				if(!setlimit(i, y, op[0], v))   ok = 0;
			}
		}
		else if(x && !y){
			for(i=1; i<=km; i++){
				if(!setlimit(x, i, op[0], v))   ok = 0;
			}
		}
		else if(!setlimit(x, y, op[0], v))   ok = 0;
	}
	return ok;
}
////////////////////////////////////////// // 构图的要求 //////////////////////////////////////////////////////

//////////////////////////////////////////////// 构图 ////////////////////////////////////////////////////////
//             起点、 终点、 容量、 下界
void addedge(int x, int y, int w, int u){
	E[x] = new ((void*)data++) edge(x, y, w, w, u, E[x]);    // 正向边
	E[y] = new ((void*)data++) edge(y, x, 0, 0, u, E[y]);    // 反向边
	E[x]->bak = E[y],   E[y]->bak = E[x];
}

void solve(){
	int i, j, n, x, y, w, s, t, u, c;
	int in[N], out[N];
	if(!build()){                     // 条件本身有矛盾
		print(-1);   return ;
	}
	// 边邻接表
	memset(E, 0, sizeof(E));

	// 伴随网络的源点和汇点，还有原网络的汇点
	S = 0; T = kn+km+3; n = kn+km+2;

	// 这两个哪里飙出来的
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));

	// 这两个有什么用
	data = new edge[5*n*n];   base = data;

	// 先处理格子里面的边：条件的约束
	for(i=1; i<=kn; i++){
		for(j=1; j<=km; j++){
			x = i + 1;   y = j + kn + 1;
			c = limit[i][j].high;   u = limit[i][j].low;
			w = c - u;
			addedge(x, y, w, u);
			in[y] += u;   out[x] += u;
		}
	}
	// 行 与 列 的约束都是原网络 源点 与 汇点 的边
	// 为什么 源点 与 汇点 的边都不加到 E[]边邻接表上？？？
	// 行的约束
	s = 1;   t = kn + km + 2;
	for(i=1; i<=kn; i++){
		x = s;   y = i + 1;   u = sumn[i];
		in[y] += u;   out[x] += u;
	}
	// 列的约束
	for(i=1; i<=km; i++){
		x = i + kn + 1;   y = t;   u = summ[i];
		in[y] += u;   out[x] += u;
	}
	// 伴随网络新增的S,  T上的边（第二种构图）
	for(i=1; i<=n; i++){      // 原网络所有点
		if(in[i]>out[i]){
			x = S;   y = i;   w = in[i] - out[i];
		}
		else{
			x = i;   y = T;   w = out[i] - in[i];
		}
		addedge(x, y, w, 0);  // 每个节点只加一条边
	}
	addedge(t, s, INF, 0);    // 第二种构图不是不用增加这两条边的？
	// 求最大流
	dinic();
	// 是否有可行流  feasible
	if(!isok())   print(-1);
	else   print(1);
	delete[] base;
}
//////////////////////////////////////////////// 构图 /////////////////////////////////////////////////////

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)   solve();

	return 0;
}
//*/






