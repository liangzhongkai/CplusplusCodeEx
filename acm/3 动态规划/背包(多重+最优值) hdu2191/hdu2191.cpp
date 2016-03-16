//   15MS	248K	971 B	
//   0MS	248K	970 B	C++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define max(a, b) a>b?a:b

const int N = 110;
int dp[N];
int n, m;

void zeroonepack(int p, int w){
	for(int i=n; i>=p; i--){
		dp[i] = max(dp[i], dp[i-p]+w);
	}
}

void completepack(int p, int w){
	for(int i=p; i<=n; i++){
		dp[i] = max(dp[i], dp[i-p]+w);
	}
}

void multiplepack(int p, int w, int num){
	if(num*p>=n){
		completepack(p, w);
	}
	else{
		int k = 1;
		while(k<num){               //改为<之后 0MS	248K	970 B	C++
			zeroonepack(p*k, w*k);
			num -= k;
			k = k<<1;
		}
		zeroonepack(p*num, w*num);
	}
}

int main()
{
	int tc;
	int p, w, num;
	int i;

	scanf("%d", &tc);

	while(tc--){
		scanf("%d %d", &n, &m);
		memset(dp, 0, sizeof(dp));
		for(i=0; i<m; i++){
			scanf("%d %d %d", &p, &w, &num);
			multiplepack(p, w, num);
		}
		printf("%d\n", dp[n]);
	}

	return 0;
}

/*
测试考虑：
算法：状态转移有错吗？
      初始化有错吗？
程序初始化了吗？
数据范围？
*/