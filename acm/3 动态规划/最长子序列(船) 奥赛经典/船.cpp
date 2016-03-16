#include <iostream>
#include <cstdio>
#include "cstring"
#include "algorithm"

using namespace std;

const int N = 5050;
struct point{
	int x, y;
}a[N];
int dp[N];

bool cmp(const point &a, const point &b){
	if(a.x==b.x)
		return a.y<b.y;
	else 
		return a.x<b.x;
}

int main(){
	int n; 
	int p, q;
	int i, j;
	
	scanf("%d %d\n%d", &p, &q, &n);

	for(i=0; i<n; i++){
		scanf("%d %d", &a[i].x, &a[i].y);
	}
	a[n].x = p;   a[n].y = p;
	n++;

	sort(a, a+n, cmp);

	memset(dp, 0, sizeof(dp));
	bool flag = false;
	for(i=0; i<n; i++){
		flag = false;
		for(j=i-1; j>=0; j--){
			if(a[i].y>a[j].y && dp[j]+1>dp[i]){
				dp[i] = dp[j]+1;
				flag = true;
			}
		}
		if(!flag)   dp[i] = 1;
	}

	printf("%d\n", dp[n-1]-1);

	return 0;
}

/*
30 4
7
22 4
2 6
10 3
15 12
9 8
17 17		  
4 2
*/