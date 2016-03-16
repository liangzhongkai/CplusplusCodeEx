

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
	edge *nex, *bak;     // ��һ����   �����
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
int Q[100000];       // �Ҳ������Ķ���
int D[N];            // D[]�����ǲ������ı�ǣ�-1����������, +1�Ĺ�ϵ

edge *cur[N], *path[N];
edge *base, *data, *it;

NODE limit[KN][KM];
int sumn[KN], summ[KM];
int kn, km;

//////////////////////////////////// DINIC������� ///////////////////////////////////////////////
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
		bfs();      // �����ͼ
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
				// ��������
				for(k=0; k<path_n; k++){
					(path[k]->c) -= d;
					((path[k]->bak)->c) += d;
				}
				path_n = mink;   i = path[path_n]->x;   flow += d;
			}
			// iΪ��������·ʧЧ�ߵ����
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
				if(!path_n)   break;   //ջ��ָ��Ϊ0
				path_n--;   i = path[path_n]->x;
			}
		}
	}
	return flow;
}
///////////////////////////////////////// DINIC������� //////////////////////////////////////////////////

///////////////////////////////////////// �Ƿ��п����� ////////////////////////////////////////////////////
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
//////////////////////////////////////////// �Ƿ��п����� //////////////////////////////////////////////////

////////////////////////////////////////// // ��ͼ��Ҫ�� //////////////////////////////////////////////////////
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
////////////////////////////////////////// // ��ͼ��Ҫ�� //////////////////////////////////////////////////////

//////////////////////////////////////////////// ��ͼ ////////////////////////////////////////////////////////
//             ��㡢 �յ㡢 ������ �½�
void addedge(int x, int y, int w, int u){
	E[x] = new ((void*)data++) edge(x, y, w, w, u, E[x]);    // �����
	E[y] = new ((void*)data++) edge(y, x, 0, 0, u, E[y]);    // �����
	E[x]->bak = E[y],   E[y]->bak = E[x];
}

void solve(){
	int i, j, n, x, y, w, s, t, u, c;
	int in[N], out[N];
	if(!build()){                     // ����������ì��
		print(-1);   return ;
	}
	// ���ڽӱ�
	memset(E, 0, sizeof(E));

	// ���������Դ��ͻ�㣬����ԭ����Ļ��
	S = 0; T = kn+km+3; n = kn+km+2;

	// ����������쭳�����
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));

	// ��������ʲô��
	data = new edge[5*n*n];   base = data;

	// �ȴ����������ıߣ�������Լ��
	for(i=1; i<=kn; i++){
		for(j=1; j<=km; j++){
			x = i + 1;   y = j + kn + 1;
			c = limit[i][j].high;   u = limit[i][j].low;
			w = c - u;
			addedge(x, y, w, u);
			in[y] += u;   out[x] += u;
		}
	}
	// �� �� �� ��Լ������ԭ���� Դ�� �� ��� �ı�
	// Ϊʲô Դ�� �� ��� �ı߶����ӵ� E[]���ڽӱ��ϣ�����
	// �е�Լ��
	s = 1;   t = kn + km + 2;
	for(i=1; i<=kn; i++){
		x = s;   y = i + 1;   u = sumn[i];
		in[y] += u;   out[x] += u;
	}
	// �е�Լ��
	for(i=1; i<=km; i++){
		x = i + kn + 1;   y = t;   u = summ[i];
		in[y] += u;   out[x] += u;
	}
	// ��������������S,  T�ϵıߣ��ڶ��ֹ�ͼ��
	for(i=1; i<=n; i++){      // ԭ�������е�
		if(in[i]>out[i]){
			x = S;   y = i;   w = in[i] - out[i];
		}
		else{
			x = i;   y = T;   w = out[i] - in[i];
		}
		addedge(x, y, w, 0);  // ÿ���ڵ�ֻ��һ����
	}
	addedge(t, s, INF, 0);    // �ڶ��ֹ�ͼ���ǲ��������������ߵģ�
	// �������
	dinic();
	// �Ƿ��п�����  feasible
	if(!isok())   print(-1);
	else   print(1);
	delete[] base;
}
//////////////////////////////////////////////// ��ͼ /////////////////////////////////////////////////////

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)   solve();

	return 0;
}
//*/






