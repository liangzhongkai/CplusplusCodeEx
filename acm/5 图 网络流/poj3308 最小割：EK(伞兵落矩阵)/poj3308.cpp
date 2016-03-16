//  388K	16MS	C++	1458B
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

#define MIN(a, b) ((a)>(b)?(b):(a))
#define INF 10000000.0
const int N = 110;
struct edge{
	double c, f;
};
edge mp[N][N];

int m, n, l;
int s, t;
int pre[N]; 
int queue[N];

bool bfs(){
	int i, qs, qe, cur;
	memset(pre, -1, sizeof(pre));
	pre[s] = s;
	qs = qe = 0;
	queue[qe++] = s;
	while(qs<qe){
		cur = queue[qs++];
		for(i=0; i<=t; i++){
			if(pre[i]==-1 && mp[cur][i].c>mp[cur][i].f){
				pre[i] = cur;
				queue[qe++] = i;
				if(i==t)   return true;
			}
		}
	}
	return false;
}

double dinic(){
	double maxflow = 0.0;
	double minf;
	int i;
	while(bfs()){
		minf = INF;
		for(i=t; i!=s; i=pre[i]){
			if(mp[pre[i]][i].c-mp[pre[i]][i].f<minf)
				minf = mp[pre[i]][i].c - mp[pre[i]][i].f;
		}
		for(i=t; i!=s; i=pre[i]){
			mp[pre[i]][i].f += minf;
			mp[i][pre[i]].f -= minf;
		}
		//printf("%lf\n", minf);
		maxflow += minf;
	}
	return maxflow;
}

int main()
{
	int tc, i;
	int a, b;
	double c;

	scanf("%d", &tc);

	while(tc--){
		memset(mp, 0, sizeof(mp));
		scanf("%d %d %d", &m, &n, &l);
		s = 0;   t = m + n + 1;

		for(i=1; i<=m; i++){
			scanf("%lf", &c);
			mp[s][i].c = log(c);    
		}
		for(i=1; i<=n; i++){
			scanf("%lf", &c);
			mp[i+m][t].c = log(c);
		}
		for(i=0; i<l; i++){
			scanf("%d %d", &a, &b);
			mp[a][m+b].c = INF;
		}

		printf("%.4lf\n", exp(dinic()));
	}

	return 0;
}



/*
int sign[N][N];
bool vis[N];
int queue[N];
double maxflow;

bool bfs(){
	int i, qs, qe, cur;
	memset(vis, 0, sizeof(vis));
	memset(sign, 0, sizeof(sign));
	vis[s] = true;
	qs = qe = 0;
	queue[qe++] = s;
	while(qs<qe){
		cur = queue[qs++];
		for(i=0; i<=t; i++){
			if(!vis[i] && mp[cur][i].c>mp[cur][i].f){
				queue[qe++] = i;
				vis[i] = true;
				sign[cur][i] = 1;
				if(i==t)   return true;     //  错在只找一条增广路就走人。
			}
		}
	}
	if(i==t)   return true;                 // 放在这里才对
	return false;
}

double dinic(int a, double b){
	if(a==t){
		cout << b << endl;
		maxflow += b;
		return b;
	}
	else{
		for(int i=0; i<=t; i++){
			if(sign[a][i]){
				double tmp = dinic(i, MIN(b, mp[a][i].c-mp[a][i].f));
				mp[a][i].f += tmp;
				mp[i][a].f -= tmp;
			}
		}
	}
}
*/