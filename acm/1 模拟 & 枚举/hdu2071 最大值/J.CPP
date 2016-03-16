/* 62 MS	468 KB	GNU C++
#include<iostream>
#include<cstdio>

using namespace std;

int main()
{
	int tc; 
	int n; 
	int i;
	double tmp, a;

	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d", &n);
		tmp=0.0;
		for(i=0; i<n; i++)
		{
			scanf("%lf", &a);
			if(tmp<a)
				tmp = a;
		}

		printf("%.2lf\n", tmp);
	}


	return 0;
}

/*
2
4 165.00 182.00 172.00 160.00
3 170.00 165.00 180.00

*/




