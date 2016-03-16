//  796K	32MS	G++	2052B
//  264K	32MS	C++	2052B
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

#define maxn 101
#define maxm 10000

struct edge{
	int u, v, w;
	int equal; // 1表示权值相同的被标记
	int used;  // 1表示第一次mst时包含该边
	int del;   // 1表示删除
}edges[maxm];
int father[maxn];
int n, m;
bool first;

void Initset(){
	// memset(father, -1, sizeof(father));
	for(int i=0; i<n; i++)
		 father[i] = -1;
}

int Findset(int x){
	int s, tmp;
	for(s=x; father[s]>=0; s=father[s]);
	while(s!=x){
		tmp = father[x];
		father[x] = s;
		x = tmp;
	}
	return s;
}

void Unionset(int x, int y){
	int rx = Findset(x), ry = Findset(y);
	int tmp = father[rx] + father[ry];
	if(father[rx]>father[ry]){
		father[rx] = ry;
		father[ry] = tmp;
	}
	else{
		father[ry] = rx;
		father[rx] = tmp;
	}
}

bool cmp(const edge &a, const edge &b){
	return a.w<b.w;
}

// 删除边的Kruskal每次考虑只是忽略一条边，其他边仍生效
int Kruskal(){
	int sumweight = 0, num = 0;
	int u, v;
	Initset();
	// 对所有的边进行一次操作
	for(int i=0; i<m; i++){  
		if(edges[i].del==1)   continue;
		u = edges[i].u;   v = edges[i].v;
		if(Findset(u)!=Findset(v)){
			sumweight += edges[i].w;   num++;
			Unionset(u, v);
			if(first)   edges[i].used = 1;
		}
		if(num>=n-1)   break;
	}
	return sumweight;
}

int main()
{
	int u, v, w;
	int t, i, j, k;
	scanf("%d", &t);
	for(i=1; i<=t; i++){

		scanf("%d%d", &n, &m);

		for(j=0; j<m; j++){
			scanf("%d%d%d", &u, &v, &w);
			edges[j].u = u-1;   edges[j].v = v-1;   edges[j].w = w;
			edges[j].equal = 0;   edges[j].del = 0;   edges[j].used = 0;
		}
		for(j=0; j<m; j++){
			for(k=j+1; k<m; k++){
				if(edges[k].w==edges[j].w)   edges[j].equal = edges[k].equal = 1;
			}
		}

		sort(edges, edges+m, cmp);
		first = true;
		int weight1 = Kruskal(), weight2;
		first = false;
		for(j=0; j<m; j++){
			if(edges[j].used && edges[j].equal){
				edges[j].del = 1;
				weight2 = Kruskal();
				if(weight2==weight1){
					printf("Not Unique!\n");  break;
				}
				edges[j].del = 0;
			}
		}
		if(j>=m)   printf("%d\n", weight1);
	}

	return 0;
}