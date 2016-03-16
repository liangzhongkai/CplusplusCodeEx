//   976K	1610MS	C++	2145B
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int N = 250;
const int INF = 1000000000;

int K, C, M;
int n;

int dist[N][N];   // FLOYD
int map[N][N];    // ��������
int sign[N][N];   // �ֲ�����
int used[N];      // ����

#define MIN(a, b)  ((a)>(b)?(b):(a))

void Build_Graph(int min_max){
	int i, j;
	memset(map, 0, sizeof(map));           // û��Ϊ0
	for(i=1; i<=K; i++)   map[i][n+1] = M; // machineΪM
	for(i=K+1; i<=n; i++)   map[0][i] = 1; // ţΪ1
	for(i=K+1; i<=n; i++){                 // ѡ�񲿷ֱ�
		for(j=1; j<=K; j++){
			if(dist[i][j]<=min_max)
				map[i][j] = 1;
		}
	}
}

// ��map�������硪��>sign�ֲ�����
bool bfs(){
	memset(used, 0, sizeof(used));  // �ж��Ƿ��ڶ�����
	memset(sign, 0, sizeof(sign));
	int queue[100*N] = {0};
	queue[0] = 0;
	used[0] = 1;
	int qe = 1, qs = 0;
	while(qs<qe){
		for(int i=0; i<=n+1; i++){
			if(!used[i] && map[queue[qs]][i]){
				queue[qe++] = i;
				used[i] = 1;
				sign[queue[qs]][i] = 1;
			}
		}
		qs++;
	}
	if(used[n+1])   return true; // ����յ��ڷֲ����磬�ͼ���
	else   return false;
}

// �����ֲ����磬������������Ѱ������·����������
int dfs(int v, int sum){ 
	int i, s, t;
	if(v==n+1)   return sum;
	s = sum;
	for(i=0; i<=n+1; i++){
		if(sign[v][i]){
			t = dfs(i, MIN(map[v][i], sum));
			// ͳһ����
			map[v][i] -= t;
			map[i][v] += t;
			sum -= t;   // �о�����ǳ����׳���
		}
	}
	return s - sum;
}

int main()
{
	int i, j, k, L, R, mid, ans;
	scanf("%d %d %d", &K, &C, &M);
	n = K + C;

	// FLOYD
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			scanf("%d", &dist[i][j]);
			if(dist[i][j]==0)
				dist[i][j] = INF;
		}
	}
	for(k=1; k<=n; k++){
		for(i=1; i<=n; i++){
			if(dist[i][k]!=INF){
				for(j=1; j<=n; j++){
					if(dist[j][k]!=INF && dist[i][j] > dist[i][k] + dist[k][j]){
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}
	}

	// �����������ù�ͼ�������ȷ��һ�������Ƿ����
	L = 0,   R = 10000;
	// ƽʱ�Ķ��ַ���mid�ǲ����������ģ������ﲻ��
	while(L<R){
		mid = (L+R)/2;
		ans = 0;
		Build_Graph(mid);
		while(bfs())   ans += dfs(0, INF);
		if(ans>=C)   R = mid;  // ��Ϊmid�Ƿ���������
		else L = mid + 1;
	}

	printf("%d\n", R);
		 
	return 0;
}