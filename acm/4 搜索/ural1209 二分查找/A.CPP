//* 62 MS	188 KB	GNU C++
#include<iostream>

using namespace std;

unsigned int n;

bool bs()                                      // 二分查找，  unsigned int才能相乘
{
	unsigned int s=1, m, e=65537;   //65537
	unsigned int mm; //unsigned int
	
	while(s<=e)
	{
		//m = (s+e)/2;
		m = s + ((e - s)>>1);
		mm = m * m;
		unsigned int tmp = (mm-m)/2;
		
		if(tmp==n)
			return true;
		else if(tmp>n)
		{
			e = m-1;
		}
		else if(tmp<n)
		{
			s = m+1;
		}
	}
	return false;
}
int main()
{
	int tc;
	int i=0;
	cin >> tc; 
	while(tc--)
	{
		scanf("%d", &n);
		n--;
		if(bs())
		{
			cout << "1 " ;
		}
		else
		{
			cout << "0 ";
		}
	
	}

	return 0;
}
//*/
/*
65536  2147450881
65537  2147516417
       2147483648
*/

/*
12
1
2
4
7
11
16
22
29
37
46
56
2147450881

*/

/*

#include<stdio.h>
#include<math.h>
int main()
{
    int i,n;
    double j,x;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
    	scanf("%lf",&j);
    	x=8*j-7;
    	printf("%d ",sqrt(x)==floor(sqrt(x)));
    }
    return 0;
}
*/