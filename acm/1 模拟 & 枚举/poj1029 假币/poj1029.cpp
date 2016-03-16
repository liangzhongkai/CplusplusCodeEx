/*         260K	63MS
#include<iostream>
#include<vector>

using namespace std;

int main()
{
	int N, K;
	int n;
	int i;
	int count = 0;
	int equal[1001]={0}, spe[1001]={0}, temp[1001];
	
	cin >> N >> K;

	while( K-- )
	{
		cin >> n;

		for( i=0; i<2*n; i++ )
		{
			cin >> temp[i];
		}
		
		char ch;
		cin >> ch;
		
		if( ch=='=' )
		{
			for( i=0; i<2*n; i++ )
			{
				equal[temp[i]] = 1;
			}
		}
		else if( ch=='<' )
		{
			count++;
			for( i=0; i<n; i++ )
			{
				spe[temp[i]]--;
			}
			for( i=n; i<2*n; i++ )
			{
				spe[temp[i]]++;
			}
		}
		else if( ch=='>' )
		{
			count++;
			for( i=0; i<n; i++ )
			{
				spe[temp[i]]++;
			}
			for( i=n; i<2*n; i++ )
			{
				spe[temp[i]]--;
			}
		}
	}

	int num=0, cn=0;
	for( i=1; i<=N; i++ )
	{
		if( equal[i]==1 )
			continue;
		if( count==spe[i] || count==-spe[i] )
		{
			cn++;
			num = i;
		}
	}

	if( cn==1 )
		cout << num << endl;
	else
		cout << 0 << endl;

	

	return 0;
}
//*/


//*
#include <iostream>
#include <string>
 
using namespace std;
 
const int MAX = 1001;
 
int main()
{
    int n, i, k, p, total = 0;
    char sign;
    int t[MAX] = {0};
    int r[MAX] = {0};
    int w[MAX] = {0};
 
    cin >> n >> k;
 
    while (k--)
    {
        cin >> p;
        for (i = 0; i < 2 * p; i++)
        {
            cin >> t[i];
        }
 
        cin >> sign;
		
        if (sign == '=')
        {
            for (i = 0; i < 2 * p; i++)
            {
                r[t[i]] = 1;
            }
        }
        else if (sign == '<')
        {
            total++;
            for (i = 0; i < p; i++)
            {
                w[t[i]]--;
            }
            for (i = p; i < 2 * p; i++)
            {
                w[t[i]]++;
            }
        }
        else if (sign == '>')
        {
            total++;
            for (i = 0; i < p; i++)
            {
                w[t[i]]++;
            }
            for (i = p; i < 2 * p; i++)
            {
                w[t[i]]--;
            }
        }
    }
 
    int count = 0, pos = 0;
    for (i = 1; i <= n; i++)
    {
        if (r[i])
        {
            continue;
        }
        if (w[i] == total || w[i] ==  - total)
        {
            count++;
            pos = i;
        }
    }
 
    if (count != 1)
    {
        cout << 0 << endl;
    }
    else
    {
        cout << pos << endl;
    }
 
    return 0;
}
//*/


