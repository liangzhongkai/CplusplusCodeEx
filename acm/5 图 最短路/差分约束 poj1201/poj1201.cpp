//*    904K	235MS	C++	1061B
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

#define INF 99999
#define EMAX 50002

struct e{
	int u, v, w;
}edges[EMAX];

int n;
int dist[EMAX];
int mn;
int mx;

void init(){
	memset(dist, 0, sizeof(dist));
	mx = 1;   mn = INF;
}

bool bellman_ford(){
	int i, t;
	int f = 1;

	while(f){
		f = 0;
		for(i=0; i<n; i++){
			t = dist[edges[i].u] + edges[i].w;
			if(dist[edges[i].v] > t){
				dist[edges[i].v] = t;   f = 1;	
			}
		}

		for(i=mn; i<=mx; i++){
			t = dist[i-1] + 1;
			if(dist[i] > t){
				dist[i] = t;   f = 1;
			}
		}

		for(i=mx; i>=mn; i--){
			if(dist[i]<dist[i-1]){
				dist[i-1] = dist[i];   f = 1;
			}
		}
	}
	return true;
}

int main()
{
	while(scanf("%d", &n)!=EOF){
		init();
		int i; 
		int u, v, w;
		for(i=0; i<n; i++){
			scanf("%d %d %d", &u, &v, &w);
			edges[i].u = v,   edges[i].v = u-1,  edges[i].w = -w;
			if(mn>u)   mn = u;
			if(mx<v)   mx = v;
		}
		bellman_ford();
		printf("%d\n", dist[mx]-dist[mn-1]);
	}

	return 0;
}