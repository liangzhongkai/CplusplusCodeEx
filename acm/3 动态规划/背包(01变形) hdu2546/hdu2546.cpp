//   15MS	256K	1708 B	C++



#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
#define max(a,b) a>b?a:b

const int N = 1050;
int cost[N], dp[N];
int V;

void zeroonepack(int c, int w){
	for(int i=V; i>=c; i--){
		dp[i] = max(dp[i], dp[i-c]+w);
	}
}

int main()
{
	int n;
	int i;
	int a;
	int ans;
	
	while(scanf("%d", &n) && n!=0){
		ans = 0;
		for(i=0; i<n; i++){
			scanf("%d", cost+i);
			if(cost[i]>ans){
				ans = cost[i];
				a = i;
			}
		}
		scanf("%d", &V);
		if(V>=5){
			V = V - 5; 
			memset(dp, 0, sizeof(dp));
			for(i=0; i<n; i++){
				if(i!=a)
					zeroonepack(cost[i], cost[i]);
			}
			printf("%d\n", (V+5)-(ans+dp[V]));
		}
		else{
			printf("%d\n", V);
		}
	}
	
	return 0;
}