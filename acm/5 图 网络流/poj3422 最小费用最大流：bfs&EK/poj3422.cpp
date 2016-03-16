//     2232K	219MS	C++	3870B
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

#define INF 10000000
#define MAXN 5100

struct edge{
	int next;
	int f, c, w;
}N, P;

vector<edge> map[MAXN];
int s, t, n, k;
int queue[MAXN*1000];
int cost[MAXN];
int pre[MAXN];
int m[51][51];

bool spfa(){
	int i, H=0, T=0, cur;
	pre[s] = 0;
	for(i=0; i<=t; i++)   cost[i] = INF;
	cost[s] = 0;   queue[T++] = s;
	while(H<T){
		cur = queue[H++];
		for(i=0; i<map[cur].size(); i++){
			N = map[cur][i];
			if(N.c-N.f>0 && cost[N.next]>cost[cur]+N.w ){
				cost[N.next] = cost[cur] + N.w;
				pre[N.next] = cur;
				queue[T++] = N.next;    // ֻ����ͨ��bfs(),,,�������ڶ��еĲ����ٽ�����?????????????????????????
			}
		}
	}
	if(cost[t]!=INF)   return 1;
	else return 0;
}

int argument(){
	 int i, j, min=INF;
	 for(i=t; i!=s; i=pre[i]){
		 for(j=0; j<map[pre[i]].size(); j++){
			 if(map[pre[i]][j].next==i && map[pre[i]][j].c-map[pre[i]][j].f<min)
					min = map[pre[i]][j].c - map[pre[i]][j].f;
		 }
	 }
	 for(i=t; i!=s; i=pre[i]){
		 for(j=0; j<map[pre[i]].size(); j++){
			 if(map[pre[i]][j].next==i)
				map[pre[i]][j].f += min;
		 }
	 }
	 for(i=t; i!=s; i=pre[i]){
		 for(j=0; j<map[i].size(); j++){
			 if(map[i][j].next==pre[i])
				map[i][j].f -= min;
		 }
	 }
	 return min*cost[t];   // min ��= 1
}

int maxcostflow(){
	int Flow = 0;
	while(spfa()){
		Flow += argument();
	}
	return Flow;
}

void build(){
	int i;

	// ͷβ���� ���� ����ı�
	N.c = k;   N.f = 0;   N.next = 1;   N.w = 0;   
	map[s].push_back(N);
	N.c = 0;   N.f = 0;   N.next = s;   N.w = 0; 
	map[1].push_back(N);
	N.c = k;   N.f = 0;   N.next = t;   N.w = 0;
	map[2*n*n].push_back(N);
	N.c = 0;   N.f = 0;   N.next = 2*n*n;   N.w = 0;
	map[t].push_back(N);

	// ����ڵ���ѣ�ÿ�����ݱ�1���ߣ���Ϊ���ڽӱ��ʾ�����Թ�ͼʱҪŪһ�������
	for(i=1; i<=n*n; i++){
		N.c = 1;   N.f = 0;   N.next = n*n+i;   N.w = -m[(i-1)/n+1][(i-1)%n+1];
		map[i].push_back(N);
		N.c = 0;   N.f = 0;   N.next = i;   N.w = m[(i-1)/n+1][(i-1)%n+1];
		map[i+n*n].push_back(N);
	}

	// ����֮��ԭ�����ڵ������
	for(i=1; i<=n*n; i++){
		// i�������һ��
		if(i%n!=0){   
			// ԭ�����ڽ��ұ�ԭ����
			N.c = INF,   N.f = 0,   N.next = i+1,   N.w = 0;
			map[i].push_back(N);
			N.c = 0,   N.f = 0,   N.next = i,   N.w = 0;
			map[i+1].push_back(N);
			// ������ڽ��ұ߷����
			N.c = INF,   N.f = 0,   N.next = n*n+i+1,   N.w = 0;
			map[n*n+i].push_back(N);
			N.c = 0,   N.f = 0,   N.next = n*n+i,   N.w = 0;
			map[n*n+i+1].push_back(N);
			// ԭ�����ڽ��ұ߷����
			N.c = INF,   N.f = 0,   N.next = n*n+i+1,   N.w = 0;
			map[i].push_back(N);
			N.c = 0,   N.f = 0,   N.next = i,   N.w = 0;
			map[i+1+n*n].push_back(N);
			// ������ڽ��ұ�ԭ����
			N.c = INF,   N.f = 0,   N.next = i+1,   N.w = 0;
			map[i+n*n].push_back(N);
			N.c = 0,   N.f = 0,   N.next = i+n*n,   N.w = 0;
			map[i+1].push_back(N);
		}
		// i�������һ��
		if(i<=n*(n-1)){ 
			// ԭ�����ڽ�����ԭ����
			N.c = INF,   N.f = 0,   N.next = i+n,   N.w = 0;
			map[i].push_back(N);
			N.c = 0,   N.f = 0,   N.next = i,   N.w = 0;
			map[i+n].push_back(N);
			// ������ڽ���������
			N.c = INF,   N.f = 0,   N.next = i+n+n*n,   N.w = 0;
			map[n*n+i].push_back(N);
			N.c = 0,   N.f = 0,   N.next = i+n*n,   N.w = 0;
			map[i+n+n*n].push_back(N);
			// ԭ�����ڽ���������
			N.c = INF,   N.f = 0,   N.next = i+n+n*n,   N.w = 0;
			map[i].push_back(N);
			N.c = 0,   N.f = 0,   N.next = i,   N.w = 0;
			map[i+n+n*n].push_back(N);
			// ������ڽ�ԭ����
			N.c = INF,   N.f = 0,   N.next = i+n,   N.w = 0;
			map[i+n*n].push_back(N);
			N.c = 0,   N.f = 0,   N.next = i+n*n,   N.w = 0;
			map[i+n].push_back(N);
		}
	}
}

int main()
{
	int i, j;
	while(scanf("%d %d", &n, &k)!=EOF){
		s = 0,   t = 2*n*n+1;
		for(i=1; i<=n; i++){
			for(j=1; j<=n; j++){
				scanf("%d", &m[i][j]);
			}
		}
		for(i=0; i<=t; i++){
			map[i].clear();
		}
		build();
		printf("%d\n", -maxcostflow());
	}

	return 0;
}