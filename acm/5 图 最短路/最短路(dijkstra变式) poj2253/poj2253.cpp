//   各种路径中最大边之间的最小值
//    212K	0MS	C++	1186B
#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;

const int INF = 0x7fffffff;

struct point{
	float x, y;
}mp[205];

bool vis[205];
float dist[205];

float max(float a, float b){
	return a>b?a:b;
}

float distance(int a, int b)
{
	point m = mp[a];
	point n = mp[b];
	float tmp =  (m.x-n.x)*(m.x-n.x) + (m.y-n.y)*(m.y-n.y);
	return (float)sqrt((double)tmp);
}

int main()
{
	freopen("data.txt", "r", stdin);
	int n;
	int cnt = 1;
	int i, j;

	while(cin >> n && n!=0){
		for(i=1; i<=n; i++){
			scanf("%f%f", &mp[i].x, &mp[i].y);
		}

		memset(vis, 0, sizeof(vis));
		// 此路径的最大边
		for(i=1; i<=n; i++){
			dist[i] = 99999999.0f;
		}
		dist[1] = 0.0;

		for(i=1; i<=n; i++){
			int p = -1;
			for(j=1; j<=n; j++){
				if(!vis[j] && (p==-1 || dist[p]>dist[j])){//路径最大边的最小值
					p = j;
				}
			}
			if(p==-1)  break;
			vis[p] = true;
			for(j=1; j<=n; j++){
				if(!vis[j]){
					float mi = max(dist[p], distance(p, j));
					if(dist[j]>mi)
						dist[j] = mi;
				}
			}
		}

		printf("Scenario #%d\n", cnt++);
		printf("Frog Distance = %.3f\n\n", dist[2]);
	}

	return 0;
}