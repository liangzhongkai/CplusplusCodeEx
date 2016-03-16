#include<iostream>

using namespace std;

int main()
{
	int tc;
	int a, b;
	int b1, b2;
	double sum1, sum2;
	int ans1, ans2;

	cin >> tc;

	while(tc--){
		cin >> a >> b;
		if(b%5)  b1 = b/5 + 1;
		else   b1 = b/5;
		if(b%4)  b2 = b/4 + 1;
		else   b2 = b/4;
		if(a<=3){
			sum1 = 11 + b1 * 2.0;
			sum2 = 11 + b2 * 2.5;
		}
		else if(a<=10){
			sum1 = 11 + b1 * 2.0 + (a-3) * 2.0;
			sum2 = 11 + b2 * 2.5 + (a-3) * 2.5;
		}
		else{
			sum1 = 11 + b1 * 2.0 + 7*2.0 + (a-10) * 3.0;
			sum2 = 11 + b2 * 2.5 + 7*2.5 + (a-10) * 3.75;
		}
		ans1 = int(sum1+0.5);
		ans2 = int(sum2+0.5);
		cout << ans2-ans1 << endl;
	}
	
	return 0;
}




#include "iostream"
using namespace std;

int main()
{
	int testcase, s;
	double d, t, s1, s2;
	cin >> testcase;
	while (testcase--)
	{
		cin >> d >> t;
		s1 = s2 = s = 0;
		if (d <= 3)
		{
			s1 = 10 + 1 + 2 * t / 5 ;
			s2 = 11 + 2.5 * t / 4;
		}
		else if (d > 3 && d <= 10)
		{
			s1 = 10 + 1 + (d-3)* 2 + 2 * t / 5 ;
			s2 = 11 + (d-3)*2.5 + 2.5 * t / 4;
		}
		else 
		{
			s1 = 10 + 1 + (d-10)*3 + (10-3)*2 + 2 * t / 5;
			s2 = 11 + (d-10)*3.75+ (10-3)*2.5 + 2.5 * t / 4;
		}
		s1 = (int)(s1+0.5);
		s2 = (int)(s2+0.5);
		s = s2 - s1;
		cout << s << endl;
	}
	return 0;
}
