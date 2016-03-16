//  171MS	640K	954 B	
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 100010;
int dp[N];
int a[105], b[105];
int n, m;

void zeroonepack(int c){
	for(int i=m; i>=c; i--){
		dp[i] = dp[i]|dp[i-c];
	}
}

void completepack(int c){
	for(int i=c; i<=m; i++){
		dp[i] = dp[i]|dp[i-c];
	}
}
 

void multiplepack(int c, int n){
	if(c*n>=m){
		completepack(c);
	}
	else{
		int k = 1;
		while(k<n){
			zeroonepack(c*k);
			n -= k;
			k = k<<1;
		}
		zeroonepack(c*n);
	}
}

int main()
{
	int i;
	int count;

	while(scanf("%d %d", &n, &m)){
		if(n==0 && m==0)
			break;
		for(i=0; i<n; i++){
			scanf("%d", a+i);
		}
		for(i=0; i<n; i++){
			scanf("%d", b+i);
		}

		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		for(i=0; i<n; i++){
			multiplepack(a[i], b[i]);
		}
		count = 0;
		for(i=1; i<=m; i++){
			if(dp[i])
				count++;
		}
		printf("%d\n", count);
	}


	return 0;
}
