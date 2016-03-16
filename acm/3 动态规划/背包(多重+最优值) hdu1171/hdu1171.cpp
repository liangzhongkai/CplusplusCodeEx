//  46MS	504K	881 B	
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
#define max(a,b) a>b?a:b

const int N = 55;
int a[N], b[N];
int V;
int dp[65000];

void zeroonepack(int c, int v){
	for(int i=V; i>=c; i--){
		dp[i] = max(dp[i], dp[i-c]+v);
	}
}

void completepack(int c, int v){
	for(int i=c; i<=V; i++){
		dp[i] = max(dp[i], dp[i-c]+v);
	}
}

void multiplepack(int v, int num){
	if(num*v>=V){
		completepack(v, v);
	}
	else{
		int k = 1;
		while(k<=num){                                 //   这个过程有漏洞！！！！！
			zeroonepack(v*k, v*k);
			num -= k;
			k = k<<1;
		}
	}
}

int main()
{
	int n;
	int i;

	while(scanf("%d", &n) && n>0){
		V = 0;
		for(i=0; i<n; i++){
			scanf("%d %d", a+i, b+i);
			V += a[i]*b[i];
		}
		int sum = V;
		V = V>>1;

		memset(dp, 0, sizeof(dp));
		for(i=0; i<n; i++){
			multiplepack(a[i], b[i]);
		}

		printf("%d %d\n", sum-dp[V], dp[V]);   //  sum is odd or even ?
	}

	return 0;
}