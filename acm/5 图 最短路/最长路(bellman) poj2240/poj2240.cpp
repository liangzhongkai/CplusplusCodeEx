///   200K	47MS	C++	1170B
#include<iostream>
#include<cstdio>

using namespace std;

#define maxn 50
#define maxm 1000
#define max(a, b)   ((a)>(b)?(a):(b))

struct exchange{
	int ci, cj;
	double cij;
}ex[maxm];

int i, j, k;
int n, m;
char name[maxn][20], a[20], b[20];
double x;
double maxdist[maxn];
int flag;
int kase = 0;

int readcase(){
	scanf("%d", &n);
	if(n==0)   return 0;
	for(i=0; i<n; i++)
		scanf("%s", name[i]);
	scanf("%d", &m);
	for(i=0; i<m; i++){
		scanf("%s %lf %s", a, &x, b);
		for(j=0;  strcmp(a, name[j]); j++)
			;
		for(k=0;  strcmp(b, name[k]); k++)
			;
		ex[i].ci = j; ex[i].cij = x; ex[i].cj = k;
	}
	return 1;
}

void bellman(int v0){
	flag = 0; 
	memset(maxdist, 0, sizeof(maxdist));
	maxdist[v0] = 1;
	for(k=1; k<=n; k++){
		for(i=0; i<m; i++){
			if(maxdist[ex[i].ci]*ex[i].cij > maxdist[ex[i].cj])
				maxdist[ex[i].cj] = maxdist[ex[i].ci] * ex[i].cij;
		}
	}
	if(maxdist[v0]>1.0)   flag = 1;
}

int main()
{
	while( readcase() ){
		for(i=0; i<n; i++){
			bellman(i);
			if(flag) break;
		}

		if(flag)   printf("Case %d: Yes\n", ++kase);
		else printf("Case %d: No\n", ++kase);
	}

	return 0;
}