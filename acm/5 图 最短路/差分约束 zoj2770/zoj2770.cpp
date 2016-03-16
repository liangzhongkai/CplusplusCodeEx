//   Accepted  2770 C++ 70ms 464kb
#include<iostream>
#include<cstdio>

using namespace std;

const int INF = 1000000000;
const int N = 23000;
int c[1010];
int dist[1010];

struct edge{
	int u, v, w;
};

edge d[N];

int main()
{
	int n, m;
	int cnt;
	int i, j;
	int a, b, C;

	while(cin >> n >> m){
		c[0] = 0;
		for(i=1; i<=n; i++){
			cin >> c[i];
			c[i] += c[i-1];
		}
		cnt = 0;
		for(i=0; i<m; i++){
			cin >> a >> b >> C;
			d[cnt].u = b, d[cnt].v = a-1, d[cnt++].w = -C;
			d[cnt].u = a-1, d[cnt].v = b, d[cnt++].w = c[b]-c[a-1];
		}
		for(i=0; i<n; i++){
			d[cnt].u = i, d[cnt].v = i+1, d[cnt++].w = c[i+1]-c[i];
			d[cnt].u = i+1, d[cnt].v = i, d[cnt++].w = 0;
		}

		// bellman
		for(i=0; i<=n; i++){
			dist[i] = INF;
		}
		dist[n] = 0;
		bool flag = true;
		for(i=0; i<n && flag; i++){
			flag = false;
			for(j=0; j<cnt; j++){
				if(dist[d[j].u]<INF && dist[d[j].v]>dist[d[j].u]+d[j].w){
					dist[d[j].v] = dist[d[j].u] + d[j].w;
					flag = true;
				}
			}
		}
		flag = false;
		for(i=0; i<cnt; i++){
			if(dist[d[i].u]+d[i].w<dist[d[i].v]){
				flag = true;
				break;
			}
		}
		if(flag){
			cout << "Bad Estimations" << endl;
		}
		else{
			cout << -dist[0] << endl;
		}
	}

	return 0;
}


/*
//  Time Limit Exceeded  2770 C++ 2001ms  464kb 

#include<iostream>
#include<cstdio>

using namespace std;

const int INF = 1000000000;
const int N = 23000;
int c[1010];
int dist[1010];

struct edge{
	int u, v, w;
};

edge d[N];

int main()
{
	int n, m;
	int cnt;
	int i, j;
	int a, b, C;

	while(scanf("%d %d", &n, &m)){
		c[0] = 0;
		for(i=1; i<=n; i++){
			scanf("%d", c+i);
			c[i] += c[i-1];
		}
		cnt = 0;
		for(i=0; i<m; i++){
			scanf("%d %d %d", &a, &b, &C);
			d[cnt].u = b, d[cnt].v = a-1, d[cnt++].w = -C;
			d[cnt].u = a-1, d[cnt].v = b, d[cnt++].w = c[b]-c[a-1];
		}
		for(i=0; i<n; i++){
			d[cnt].u = i, d[cnt].v = i+1, d[cnt++].w = c[i+1]-c[i];
			d[cnt].u = i+1, d[cnt].v = i, d[cnt++].w = 0;
		}

		// bellman
		for(i=0; i<=n; i++){
			dist[i] = INF;
		}
		dist[n] = 0;
		bool flag = true;
		for(i=0; i<n && flag; i++){
			flag = false;
			for(j=0; j<cnt; j++){
				if(dist[d[j].u]<INF && dist[d[j].v]>dist[d[j].u]+d[j].w){
					dist[d[j].v] = dist[d[j].u] + d[j].w;
					flag = true;
				}
			}
		}
		flag = false;
		for(i=0; i<cnt; i++){
			if(dist[d[i].u]+d[i].w<dist[d[i].v]){
				flag = true;
				break;
			}
		}
		if(flag){
			cout << "Bad Estimations" << endl;
		}
		else{
			cout << -dist[0] << endl;
		}
	}

	return 0;
}
//*/