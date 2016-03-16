//*     156MS	340K	695 B	
#include <iostream>
#include <cstdio>

using namespace std;

int V;
const int N = 10010;
double dp[N];
int v[110];
double f[110];

void zeroonepack(double f, int v){
	for(int i=V; i>=v; i--){
		if(dp[i]<dp[i-v]*f)
			dp[i] = dp[i-v] * f;
	}
}

int main()
{
	int tc;
	int m, i;
	double ff;

	scanf("%d", &tc);

	while(tc--){
		scanf("%lf %d", &ff, &m);
		ff = 1.0 - ff;
		V = 0;
		for(i=0; i<m; i++){
			scanf("%d %lf", v+i, f+i);
			V += v[i];
		}
		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		for(i=0; i<m; i++){
			zeroonepack(1.0-f[i], v[i]);
		}
		for(i=V; i>=0; i--){   // i>0 is wrong
			if(dp[i]>ff){      // dp[i]>=ff is wrong
				printf("%d\n", i);
				break;
			}
		}
	}

	return 0;
}
//*/


/*    78MS	356K	857 B	C++
#include <iostream>
using namespace std;

int main()
{
	int t, i;
	int banks , money[110], sum;
	double probability,  //给的概率
		probas[110],   //
		f[110*110/2] ;    //转换背包
	
	cin >> t;
	while(t--)
	{
		sum = 0;
		memset(f,0,sizeof(f));
		f[0]  = 1;    //抢0万时不被抓
		
		cin >> probability >> banks;
		for(i = 0 ; i < banks ; i++)
			cin >> money[i] >> probas[i] , sum += money[i];  //将钱转换为背包容量， 概率转化为价值
		
		//背包过程
		for(i = 0 ; i < banks ; i++)
			for(int j = sum ; j >= money[i] ; j--)
				if(f[j] < f[ j - money[i]]* (1.0 - probas[i]))
					f[j] = f[ j - money[i]]* (1.0 - probas[i]) ;   //普通dp状态方程
				
				for(i = sum ; i >= 0 ; i--)   //遍历概率,找出符合的
					if(probability > 1.0 - f[i])
					{
						cout << i << endl;
						break;
					}
	}
	return 0;
}
//*/