/*
#include<iostream>

using namespace std;

vector<int> vecx[30001];
vector<int> vecy[30001];



int main()
{
	int m, n, k;
	int a, b;
	int i, j;

	while(cin >> m >> n >> k)
	{
		memset(mp, false, sizeof(mp));

		for(i=0; i<k; i++)
		{
			cin >> a >> b;
			vecx[a].push_back(b);
			vecy[b].push_back(a);
		}

		for(i=1; i<=m; i++)
			sort(vecx[i].begin(), vecx[i].end());

		for(i=1; i<=n; i++)
			sort(vecy[i].begin(), vecy[i].end());

		for(i=1; i<=m; i++)
	}
	

	return 0;
}
//*/

//*
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int n,m,k,ans;
vector<int> x[30001],y[30001];
vector<int>::iterator t;

int main()
{
    int i,j,a,b;
    scanf("%d%d%d",&n,&m,&k);
    for (ans=0,i=1;i<=n;++i)
    {
        y[i].push_back(0);
        y[i].push_back(m+1);
    }
    for (i=1;i<=m;++i)
    {
        x[i].push_back(0);
        x[i].push_back(n+1);
    }
    for (i=1;i<=k;++i)
    {
        scanf("%d%d",&a,&b);
        y[a].push_back(b);
        x[b].push_back(a);
    }

    for (i=1;i<=n;++i)  sort(y[i].begin(),y[i].end());
    for (i=1;i<=m;++i)  sort(x[i].begin(),x[i].end());

    for (i=1;i<=n;++i)
        for (j=1;j<y[i].size();++j)
		{
            if (y[i][j]-y[i][j-1] > 2)
                ++ans;
            else if (y[i][j]-y[i][j-1] == 2)
            {
                a=y[i][j]-1;
                t=upper_bound(x[a].begin(),x[a].end(),i);  // >iµÄÖµ
                b=*t;
                if (b-(*(--t)) == 2)  ++ans;
            }
		}

    for (i=1;i<=m;++i)
        for (j=1;j<x[i].size();++j)
            if (x[i][j]-x[i][j-1] > 2)
                ++ans;

    printf("%d\n",ans);
    return 0;
}
//*/