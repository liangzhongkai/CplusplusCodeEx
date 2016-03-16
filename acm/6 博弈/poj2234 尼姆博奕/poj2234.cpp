//  240K	0MS	C++	290B

#include<iostream>

using namespace std;

int main()
{
	int n;
	int i;
	int a;

	while(cin >> n)
	{
		int ans = 0;
		for(i=0; i<n; i++)
		{
			cin >> a; 
			ans = ans ^ a;
		}

		if(ans)
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	

	return 0;
}