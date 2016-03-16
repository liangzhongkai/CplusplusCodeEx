//  732K	79MS	G++	1292B
#include<iostream>
#include<cstdio>
#include<vector>
#include <cstring>

using namespace std;

const int N = 5050;
int a[N];
int dp[N];
__int64 count[N];

int main()
{
	int n;
	int i, j, k;

	memset(dp, 0, sizeof(dp));
	memset(count, 0, sizeof(count));

	scanf("%d", &n);
	for(i=0; i<n; i++){
		scanf("%d", a+i);
		for(j=i-1; j>=0; j--){
			if(a[i]<a[j] && dp[i]<dp[j]+1){
				dp[i] = dp[j] + 1;
			}
		}
	}
	a[n] = -1;
	for(i=n-1; i>=0; i--){
		if(a[n]<a[i] && dp[n]<dp[i]+1){
			dp[n] = dp[i] + 1;
		}
	}

	vector<int> vec;
	bool flag, key;
	count[0] = 1;
	for(i=1; i<=n; i++){
		vec.clear();
		key = false;
		for(j=i-1; j>=0; j--){
			if(dp[i]==dp[j]+1 && a[i]<a[j]){   // dp[i]==dp[j]+1 使之成为路径！
				flag = false;
				for(k=0; k<vec.size(); k++){
					if(a[vec[k]]==a[j]){
						flag = true;
						break;
					}
				}
				if(!flag)   vec.push_back(j);
				key = true;
			}
		}
		if(key){
		//	printf("%d ", i);
			for(j=0; j<vec.size(); j++){
				count[i] += count[vec[j]];
			//	printf("%d ", vec[j]);
			}
			//printf("\n");
		}
		else
			count[i] = 1;
	}
/*
	for(i=0; i<=n; i++){
		//printf("%d ", dp[i]);
		printf("%I64d ", count[i]);
	}
	cout << endl;
*/
	printf("%d %I64d\n", dp[n], count[n]);

	return 0;
}

/*
6
5 6 4 3 1 2
*/