//*
//  0MS	340K	558 B	C++
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define min(a, b) a<b?a:b

const int N = 10010;
double dp[N];
int n, m;

void zeroonepack(int a, double ff){
	for(int i=n; i>=a; i--){ 
		dp[i] = min(dp[i], dp[i-a]*ff);
	}
}

int main()
{
	int i, a;
	double ff;

	while(scanf("%d %d", &n, &m)){
		if(n==0 && m==0)     // 这个数据非常贱！！！
			break;

		for(i=0; i<=n; i++){
			dp[i] = 1.0;
		}

		for(i=0; i<m; i++){
			scanf("%d %lf", &a, &ff);
			
			zeroonepack(a, 1.0-ff);
		}


		printf("%.1lf%%\n", (1.0-dp[n])*100);
	}

	return 0;
}
//*/
