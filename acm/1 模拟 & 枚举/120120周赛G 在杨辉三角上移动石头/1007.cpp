//    1007	250 MS	256 KB	Visual C++	Ð¡¿­
#include<iostream>

using namespace std;

int main()
{
	int tc;
	int x, y;
	cin >> tc;

	while( tc-- )
	{
		cin >> x >> y;

		if( x&1 && y&1 )
		{
			cout << "NO" << endl;
		}
		else
		{
			cout << "YES" << endl;
		}

	}

	return 0;
}