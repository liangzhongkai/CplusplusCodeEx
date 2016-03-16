/*      3038	31MS	1400K	910 B	C++
#include<iostream>
#include<cstdio>

using namespace std;

const int MAXN = 200010;
int father[MAXN], val[MAXN];
int n, m;

int Find(int a){
	if(father[a]!=a){
		int fa = father[a];
		father[a] = Find(father[a]);
		val[a] += val[fa];
	}
	return father[a];
}

void Union(int a, int b, int c){
	int X = Find(a);
	int Y = Find(b);
	if(X>Y){
		father[X] = Y;
		val[X] = val[b] - val[a] - c;
	}
	else{
		father[Y] = X;
		val[Y] = val[a] + c - val[b];
	}
}

int main()
{
	int i, cnt;
	int a, b, c;
	int X, Y;

	while(scanf("%d%d", &n, &m)!=EOF){
		cnt = 0;
		for(i=0; i<=n; i++){
			father[i] = i;
			val[i] = 0;
		}

		for(i=1; i<=m; i++){
			scanf("%d%d%d", &a, &b, &c);
			a--;
			X = Find(a);
			Y = Find(b);
			if(X!=Y){
				Union(a, b, c);
			}
			else{
				if(val[b]-val[a]!=c){
					cnt++;
				}
			}
		}
		printf("%d\n", cnt);
	}

	return 0;
}
//*/
/*
10 6
1 10 100
7 10 28
1 3 32
4 6 41
6 6 1
8 9 60
*/

/*   3038	31MS	1592K	1393 B	C++
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define FOR(i,a,b) for(i = (a); i < (b); ++i)
#define FORE(i,a,b) for(i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(i = (a); i > (b); --i)
#define FORDE(i,a,b) for(i = (a); i >= (b); --i)
#define CLR(a,b) memset(a,b,sizeof(a))

const int MAXN = 200100;

int p[MAXN], sum[MAXN], ans, n, m;

void init() {
    int i;
    ans = 0;
    CLR(sum, 0);
    FORE(i, 0, n)
        p[i] = i;
}

int find_set(int x) {
    if (p[x] == x)
        return x;
    int t = p[x];
    p[x] = find_set(p[x]);
    sum[x] += sum[t];
    return p[x];
}

void union_set(int a, int b, int pa, int pb, int c) {
    if (pa > pb) {
        p[pb] = pa;
        sum[pb] = sum[a] - sum[b] - c;
    }
    else {
        p[pa] = pb;
        sum[pa] = sum[b] + c - sum[a];
    }
}

int main() {
    int i, a, b, c, pa, pb;

    while (scanf("%d %d", &n, &m) != EOF) {
        init();
        FOR(i, 0, m) {
            scanf("%d %d %d", &a, &b, &c);
            a--;
            pa = find_set(a);
            pb = find_set(b);
            if (pa == pb) {
                if (sum[a] != sum[b] + c) {
                    ans++;
                }
            }
            else
                union_set(a, b, pa, pb, c);
        }
        printf("%d\n", ans);
    }
    return 0;
}

//*/

/*
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define SIZE 200005
int parent[SIZE], relation[SIZE];
int stack[SIZE], stack_cnt;
int N,M;

int get_root(int a){
	int root;
	stack_cnt=0;
	while (a!=parent[a]){
		stack[stack_cnt++]=a;
		a=parent[a];
	}

	root=parent[a];
	for (int i=stack_cnt-1;i>=0;i--){
		a=stack[i];   //wrong 原来没写
		relation[a] += relation[parent[a]];
		parent[a] = root;
	}
	return root;
}

void Union(int a,int b,int value){
	int root_a,root_b;
	root_a=get_root(a);
	root_b=get_root(b);

	relation[root_a]=-relation[a]-value+relation[b];
	parent[root_a]=root_b;  //parent[a]=b;
}

void init(){
	int i;
	for (i=0;i<=N;i++) parent[i]=i,relation[i]=0;
}

int main()
{
	int result=0,a,b,value,root_a,root_b;
	while (  scanf ("%d %d",&N,&M)==2)
	{
		init();
		result=0;

		while (M--)
		{
			scanf ("%d %d %d",&a,&b,&value);
			a--;
			root_a=get_root(a);
			root_b=get_root(b);
			if (root_a==root_b)
			{
				//printf ("here!");调试
				if (relation[b]-relation[a]==value)   continue;
				else
				{
					result++;
				//    printf ("fuck"); 调试
				}
			}
			else Union(a,b,value);
		}
		printf ("%d\n",result);
	}
	return 0;
}
//*/
