//  752K	438MS	C++	777B
#include<iostream>
#include<cstdio>

using namespace std;

#define N -9999999

int dp1[50001],dp2[50001];
int a[50001];

int main()
{
	int tc;
	int i;
	int n;
	scanf("%d", &tc);

	while(tc--)
	{
		scanf("%d", &n);
		
		for(i=1; i<=n; i++)
		{
			scanf("%d", a+i);
		}

		int temp = N, max = N;
		for(i=1; i<=n; i++)
		{
			if(temp>=0)
				temp += a[i];
			else
				temp = a[i];
			max = max>temp?max:temp;
			dp1[i] = max;
		}

		temp = N, max = N;
		for(i=n; i>=1; i--)
		{
			if(temp>=0)
				temp += a[i];
			else
				temp = a[i];
			max = max>temp?max:temp;
			dp2[i] = max;
		}

		int ans = N;
		for(i=1; i<n; i++)
		{
			ans = ans>(dp1[i]+dp2[i+1])?ans:(dp1[i]+dp2[i+1]);
		}
		printf("%d\n", ans);
	}

	return 0;
}