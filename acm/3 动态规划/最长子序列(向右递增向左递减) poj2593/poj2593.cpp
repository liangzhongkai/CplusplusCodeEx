//  1424K	235MS	C++	722B
#include<iostream>

using namespace std;

#define N -999999999

int dp1[100001];
int dp2[100001];
int a[100001];

int main()
{
	int n;
	int i;

	while(cin >> n && n!=0)
	{
		for(i=1; i<=n; i++)
			scanf("%d", a+i);

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

		cout << ans << endl;
	}
		
	return 0;
}