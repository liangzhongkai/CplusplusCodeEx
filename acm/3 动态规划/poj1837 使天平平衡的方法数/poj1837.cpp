//         1072K	141MS	C++	623B
//         1072K	32MS	C++	656B
#include<iostream>
#include<cstring>

using namespace std;

int dp[20][15000];
int cc[20];
int gg[20];

int main()
{
	int c, g;
	int i, j, k;
	cin >> c >> g;

	for(i=0; i<c; i++)
		cin >> cc[i];
	for(i=0; i<g; i++)
		cin >> gg[i];

	for(i=0; i<g; i++)
		for(j=0; j<15000; j++)
			dp[i][j] = 0;

	// ³õÊ¼»¯
	for(j=0; j<c; j++)
	{
		int tmp = cc[j]*gg[0];
		dp[0][7500+tmp]++;
	}
	
	for(i=1; i<g; i++)
		for(k=0; k<15000; k++)
			if(dp[i-1][k])
			{
				for(j=0; j<c; j++)
				{
					dp[i][k+gg[i]*cc[j]] += dp[i-1][k];
				}
			}


	cout << dp[g-1][7500] << endl;
			

	return 0;
}