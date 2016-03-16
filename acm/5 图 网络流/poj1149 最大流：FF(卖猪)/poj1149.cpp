//*   344K	0MS	C++	1848B
#include<iostream>
#include<cstring>

using namespace std;

const int INF = 1000000;
const int M = 1005;
const int N = 105;
int pig[M];

struct Node{
	int c, f;
};
Node edge[N][N];
int vis[M];

int n, m;

#define MIN(a,b) ((a)<(b)?(a):(b))
int prev[N], alpha[N];
int qs, qe;
int queue[N];   // **
int v;

void FF(){
	int i;
	while(1){
		memset(prev, 0xff, sizeof(prev));
		memset(alpha, 0xff, sizeof(alpha));

		prev[0] = 0;   alpha[0] = INF;
		qs = qe = 0;
		queue[qe++] = 0;

		while(qs<qe && prev[n]==-1){  // 一有增广路就out       不一定要专门设一个flag变量，用一个prev就行
			v = queue[qs++];
			for(i=0; i<=n; i++){
				// 向前边、向后边都必须进行增广，此处c>f，所以想增广向后边，必须将使edge[i][v] = -f变成负数，那么它就可以增广向后边了
				if(prev[i]==-1 && edge[v][i].c>edge[v][i].f){  
					prev[i] = v;
					alpha[i] = MIN(alpha[v], edge[v][i].c-edge[v][i].f);
					queue[qe++] = i;
				}
			}
		}

		if(prev[n]==-1)   break;

		int k1 = n, k2 = prev[n];
		int a = alpha[n];
		while(1){
			//if(edge[k2][k1].c>0)  edge[k2][k1].f += a;
			//else edge[k1][k2].f -= a;
			edge[k2][k1].f += a;
			edge[k1][k2].f = -edge[k2][k1].f;    //  这里体现了顾客之间流量流动的核心，前一个顾客的没用完，
			if(k2==0)   break;
			k1 = k2;   k2 = prev[k2];
		}
	}

	int maxflow = 0;
	for(i=0; i<n; i++){
		maxflow += edge[i][n].f;
	}
	cout << maxflow << endl;
}

int main()
{
	int i, j;
	int a, b, tmp;

	cin >> m >> n;

	for(i=1; i<=m; i++){
		cin >> pig[i];
	}

	n++;
	memset(vis, 0, sizeof(vis));
	for(i=0; i<=n; i++){
		for(j=0; j<=n; j++){
			edge[i][j].c = edge[i][j].f = 0;
		}
	}
	for(i=1; i<n; i++){
		cin >> a;
		for(j=0; j<a; j++){
			cin >> tmp;

			if(!vis[tmp]){                  // 第i个顾客与源点的边
				edge[0][i].c += pig[tmp];
				edge[0][i].f = 0;
				vis[tmp] = i;
			}
			else{                           // 顾客之间取猪圈的先后
				edge[vis[tmp]][i].c = INF;
				edge[vis[tmp]][i].f = 0;
				vis[tmp] = i;
			}
		}
		cin >> b;
		if(b==0)   continue;
		// 第i个顾客与终点的边
		edge[i][n].c = b;   edge[i][n].f = 0;
	}

	FF();

	return 0;
}
//*/
/*
3 3
3 6 3
2 1 2 2
2 1 3 4
1 2 6

3 3
3 6 5
2 1 2 2
2 1 3 4
1 2 6
//*/



/*   344K	32MS	C++	2389B
#include<iostream>
#include<cmath>
#include<cstring>

using namespace std;

const int INF = 1000000;
const int M = 1005;
const int N = 105;
int pig[M];

struct Node{
	int c, f;
};
Node edge[N][N];
int vis[M];

int n, m;

#define MIN(a,b) ((a)<(b)?(a):(b))
int flag[N], prev[N], alpha[N];
int qs, qe;
int queue[N];   // **
int v;

void FF(){
	int i;
	while(1){
		memset(flag, 0xff, sizeof(flag));
		memset(prev, 0xff, sizeof(flag));
		memset(alpha, 0xff, sizeof(alpha));

		flag[0] = prev[0] = 0;   alpha[0] = INF;
		qs = qe = 0;
		queue[qe++] = 0;

		while(qs<qe && flag[n]==-1){  // 一有增广路就out
			v = queue[qs++]; 
			for(i=0; i<=n; i++){
				if(flag[i]==-1){
					if(edge[v][i].c>0 && edge[v][i].c>edge[v][i].f){
						flag[i] = 0;  prev[i] = v;
						alpha[i] = MIN(alpha[v], edge[v][i].c-edge[v][i].f);
						queue[qe++] = i;
					}
					else if(edge[i][v].c>0 && edge[i][v].f>0){
						flag[i] = 0;  prev[i] = -v;  // 下面k2 = abs(prev[n])
						alpha[i] = MIN(alpha[v], edge[i][v].f);
						queue[qe++] = i;
					}
				}
			}
			flag[v] = 1;
		}

		//cout << flag[n] << " " << alpha[n] << endl;
		if(flag[n]==-1 || alpha[n]==0)   break;

		int k1 = n, k2 = abs(prev[n]);
		int a = alpha[n];
		while(1){
			if(edge[k2][k1].c>0)     // 写成edge[k2][k1].f，错得我只狗甘
				edge[k2][k1].f += a;
			else 
				edge[k1][k2].f -= a;
			if(k2==0)   break;
			k1 = k2;   k2 = abs(prev[k2]);
		}
	}

	int maxflow = 0;
	for(i=1; i<=n; i++){
		maxflow += edge[0][i].f;
	}
	cout << maxflow << endl;
}

int main()
{
	int i, j;
	int a, b, tmp;

	cin >> m >> n;

	for(i=1; i<=m; i++){
		cin >> pig[i];
	}

	n++;
	memset(vis, 0, sizeof(vis));
	for(i=0; i<=n; i++){
		for(j=0; j<=n; j++){
			edge[i][j].c = edge[i][j].f = 0;
		}
	}
	for(i=1; i<n; i++){
		cin >> a;
		for(j=0; j<a; j++){
			cin >> tmp;

			if(!vis[tmp]){                  // 第i个顾客与源点的边
				edge[0][i].c += pig[tmp];
				edge[0][i].f = 0;
				vis[tmp] = i;
			}
			else{                           // 顾客之间取猪圈的先后
				edge[vis[tmp]][i].c = INF;
				edge[vis[tmp]][i].f = 0;
				vis[tmp] = i;
			}
		}
		cin >> b;
		if(b==0)   continue;
		// 第i个顾客与终点的边
		edge[i][n].c = b;   edge[i][n].f = 0;
	}

	FF();

	return 0;
}
//*/

