//   46MS	284K	711 B	C++
//   15MS	288K	781 B	C++
#include<iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define min(a, b) a<b?a:b
const int INF = 0x7fffff;
int W;
int dp[10010];

void completepack(int v, int w){
	for(int i=w; i<=W; i++){
		dp[i] = min(dp[i], dp[i-w]+v);
	}
}

int main(){
	int tc;
	int n, m;
	int i;
	int a, b;

	scanf("%d", &tc);

	while(tc--){
		scanf("%d %d", &n, &m);
		W = m - n;
		scanf("%d", &n);
		for(i=0; i<=W; i++){
			dp[i] = INF;
		}
		dp[0] = 0;
		for(i=0; i<n; i++){
			scanf("%d %d", &a, &b);
			if(dp[b]>a)
				completepack(a, b);
		}
		if(dp[W]!=INF){
			printf("The minimum amount of money in the piggy-bank is %d.\n", dp[W]);
		}
		else{
			printf("This is impossible.\n");
		}
	}

	return 0;
}