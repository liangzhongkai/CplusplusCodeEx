///     268K	0MS	C++	283B
#include<iostream>
#include<cmath>

using namespace std;

int main()
{
	int tc;
	int n;
	int ans;

	cin >> tc;
	while(tc--){
		cin >> n;
		ans = 0.5 * log10(2*acos(-1.0)*n) + n * log10(n*1.0/exp(1.0));
		ans = (int)ans + 1;
		cout << ans << endl;
	}

	return 0;
}