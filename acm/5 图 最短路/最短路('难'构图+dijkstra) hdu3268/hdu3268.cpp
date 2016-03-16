//   0MS	244K	1783 B	C++
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int INF = 9999999;
const int N = 30;
int v[N];
int dist[N];
bool vis[N];
int n, m;

struct Edge{
	int v, w;
	struct Edge *next;
}vec[N*N], *head[N];
int cnt;

void init(){
	int i;
	cnt = 0;
	memset(head, NULL, sizeof(head));
	memset(vis, false, sizeof(vis));
	for(i=0; i<N; i++)   dist[i] = INF;
}

void addedge(int u, int v, int w){
	Edge e;   e.v = v;   e.w = w;   e.next = head[u];
	vec[cnt] = e;
	head[u] = &vec[cnt];
	cnt++;
}

int main()
{
	freopen("in.txt", "r", stdin);
	int tc;
	int i, j, k;
	int a, b, c;
	int ans;

	scanf("%d", &tc);
	while(tc--){
		scanf("%d", &n);
		n++;
		init();
		for(i=1; i<n; i++){
			scanf("%d %d", &a, v+i);
			addedge(n, i, v[i]-1);
		}
		//  必须处理两个等价物品之间的边
		for(i=1; i<n; i++){
			for(j=i+1; j<n; j++){
				if(v[i]==v[j]){
					addedge(i, j, 0);
					addedge(j, i, 0);
				}
			}
		}
		
		scanf("%d", &m);
		for(i=0; i<m; i++){
			scanf("%d %d %d", &a, &b, &c);
			addedge(a, b, c);
		}
		
		dist[n] = 0;
		for(i=1; i<=n; i++){
			int p = -1;
			for(j=n; j>0; j--){
				if(!vis[j] && (p==-1 || dist[p]>dist[j]))
					p = j;
			}
			if(p==-1)    break;
			vis[p] = true;
			for(Edge *e=head[p]; e!=NULL; e=e->next){
				int v = e->v;   int w = e->w;
				if(dist[v]>(dist[p] + w))
					dist[v] = dist[p] + w;
			}
		}

		for(i=1; i<n; i++){
			printf("%d %d\n", i, dist[i]);
		}

		ans = 0;
		for(i=1; i<n; i++){
			bool flag = false;
			for(j=1; j<n-1; j++){
				for(k=j+1; k<n; k++){
					if(dist[i]==dist[j]+dist[k] && j!=i && k!=i && flag==false){
						ans++;
						flag = true;
						break;
					}
				}
				if(flag)   break;
			}
		}
		printf("%d\n", ans);
	}

	return 0;
}
