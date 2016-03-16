//  88MS 	796K 	451B 	KCT
#include<iostream>
#include<cmath>

using namespace std;

const  int N = 1000010;
double mp[N];

int main()
{
	int n, m;
	int i, a;
	while(scanf("%d%d", &n, &m)!=EOF){
		mp[0] = 0.0;
		for(i=1; i<=n; i++){
			scanf("%lf", mp+i);
			mp[i] += mp[i-1];
		}	

		double ans = 10000000000.0;
		for(i=0; i<=n-m; i++){
			a = mp[i+m]-mp[i];
			if(fabs(ans)>fabs(a))
				ans = a;
		}

		printf("%d\n", int(ans));
	}

	return 0;
}