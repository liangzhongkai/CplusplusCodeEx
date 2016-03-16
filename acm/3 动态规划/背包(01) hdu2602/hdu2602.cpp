//    15MS	260K	620 B	C++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define max(a, b) a>b?a:b

const int N = 1050;
int a[N], b[N], dp[N];
int n, V;

void ZeroOnePack(int cost, int value) 
{
	for(int v=V; v>=cost; v--)
		dp[v] = max(dp[v], dp[v-cost]+value);
}


int main()
{
	int tc;	
	int i;

	scanf("%d", &tc);

	while(tc--){
		scanf("%d %d", &n, &V);
		for(i=0; i<n; i++){
			scanf("%d", a+i);
		}
		for(i=0; i<n; i++){
			scanf("%d", b+i);
		}
		memset(dp, 0,sizeof(dp));
		for(i=0; i<n; i++){
			ZeroOnePack(b[i], a[i]);
		}
		printf("%d\n", dp[V]);
	}

	return 0;
}