//  688K	0MS	C++	1787B
#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

#define MAXN 210

struct Matrix{
	int c, f;
};

Matrix Edge[MAXN][MAXN];
int M, N;
int s, t;
int residual[MAXN][MAXN];
int qu[MAXN*MAXN], qs, qe;
int pre[MAXN];
int vis[MAXN];
int maxflow, min_augment;

void find_augment_path(){
	int i, cu;
	memset(vis, 0, sizeof(vis));
	memset(residual, 0, sizeof(residual));
	memset(pre, 0, sizeof(pre));

	qs = qe = 0;  qu[qe++] = s;
	pre[s] = s;  vis[1];

	while(qs<qe && pre[t]==0){
		cu = qu[qs++];
		for(i=1; i<=N; i++){
			if(vis[i]==0){
				if(Edge[cu][i].c > Edge[cu][i].f){
					residual[cu][i] = Edge[cu][i].c - Edge[cu][i].f;
					pre[i] = cu;   qu[qe++] = i;  vis[i] = 1;
				}
				else if(Edge[i][cu].f>0){
					residual[cu][i] = Edge[i][cu].f;
					pre[i] = cu;  qu[qe++] = i;  vis[i] = 1;
				}
			}
		}
	}
}

void augment_flow(){
	int i = t, j;
	if(pre[i]==0){
		min_augment = 0;
		return ;
	}
	j = 0x7fffffff;
	while(i!=s){
		if(residual[pre[i]][i]<j)   j = residual[pre[i]][i];
		i = pre[i];
	}
	min_augment = j;
}

void update_flow(){
	int i = t;
	if(pre[i]==0){
		return ;
	}
	for(i=t; i!=s; i=pre[i]){               //  660K	16MS	 C++	1931B
		Edge[pre[i]][i].f += min_augment;
		Edge[i][pre[i]].f -= min_augment;
	}
	/*
	while(i!=s){                            //  660K	0MS	     C++	1815B
		if(Edge[pre[i]][i].c>Edge[pre[i]][i].f)
			Edge[pre[i]][i].f += min_augment;
		else 
			Edge[i][pre[i]].f += min_augment;
		i = pre[i];
	}
	*/
}

void solve(){
	s = 1;   t = N;
	maxflow = 0;
	while(1){
		find_augment_path();
		augment_flow();
		maxflow += min_augment;
		if(min_augment>0)   update_flow();
		else return;
	}
}

int main()
{
	int i;
	int u, v, c;
	while(scanf("%d %d", &M, &N)!=EOF){
		memset(Edge, 0, sizeof(Edge));
		for(i=0; i<M; i++){
			scanf("%d %d %d", &u, &v, &c);
			Edge[u][v].c += c;
		}
		solve();
		printf("%d\n", maxflow);
	}

	return 0;
}