//*   904K	313MS	C++	2130B
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

#define MAXN 100001
#define INF 1000000000
int T;
int N;
char word[1001];
int od[26], id[26];
int bused[26];
int parent[26];

struct edge{
	int u, v;
}edges[MAXN];

void ufset(){
	 memset(parent, -1, sizeof(parent));
}

int Find(int x){
	int s;
	for(s=x; parent[s]>=0; s=parent[s])   ;
	while(s!=x){
		int tmp = parent[x];
		parent[x] = s;
		x = tmp;
	}
	return s;
}

void Union(int r1, int r2){
	int R1 = Find(r1), R2 = Find(r2);
	int tmp = parent[R1] + parent[R2];
	if(parent[R1]>parent[R2]){
		parent[R1] = R2;
		parent[R2] = tmp;
	}
	else{
		parent[R2] = R1;
		parent[R1] = tmp;
	}
}

bool connect(){
	int u, v, i;
	ufset();
	for(i=0; i<N; i++){
		u = edges[i].u;   v = edges[i].v;
		if(u!=v && Find(u)!=Find(v)){
			Union(u, v);
		}
	}
	int first = -1;
	for(i=0; i<26; i++){
		if(bused[i]==0)   continue;
		if(first==-1)   first = i;
		else if(Find(i)!=Find(first))   break;
	}
	if(i<26)   return false;
	else return true;
}

int main()
{
	int u, v;
	int i, j;
	scanf("%d", &T);
	for(i=0; i<T; i++){
		memset(od, 0, sizeof(od));
		memset(id, 0, sizeof(id));
		memset(bused, 0, sizeof(bused));
		scanf("%d", &N);
		for(j=0; j<N; j++){
			scanf("%s", word);
			u = word[0]-'a';   v = word[strlen(word)-1]-'a';
			od[u]++;   id[v]++;
			bused[u] = bused[v] = 1;
			edges[j].u = u;   edges[j].v = v;
		}
		bool Euler = true;
		int one = 0, none = 0;
		for(j=0; j<26; j++){
			if(bused[j]==0)   continue;
			if(od[j]-id[j]>=2 || id[j]-od[j]>=2){
				Euler = false;   break;
			}
			if(od[j]==0 && id[j]==0){
				Euler = false;   break;
			}
			if(od[j]-id[j]==1){
				one++;
				if(one>1){
					Euler = false;   break;
				}
			}
			if(id[j]-od[j]==1){
				none++;
				if(none>1){
					Euler = false;   break;
				}
			}
		}
		if(none!=one){
			Euler = false;
		}
		if(!connect()){
			Euler = false;
		}

		if(Euler){
			printf("Ordering is possible.\n");
		}
		else{
			printf("The door cannot be opened.\n");
		}
	}

	return 0;
}
//*/