//*         264K	735MS	C++	1156B
#include<iostream>
#include<cstdio>

using namespace std;

int father[2001];   // 指向同一个father
int rink[2001];  // 0为同类， 1为异类 ，仅存在与父子之间
int a, b;

void init_set()
{
	for(int i=1; i<2002; i++)
		father[i] = i;
	memset(rink, 0, sizeof(rink));
}

int find_set(int a)
{
	if(father[a]==a)
		return a;
	
	int na = father[a];
	father[a] = find_set(father[a]);            //  将一路上的子节点都指向同一个祖宗 a==father[a] 时的 a !
	rink[a] = (rink[a] + rink[na]) % 2 ;

	return father[a];
}

void union_set(int x, int y)  // a, b都为根
{
	father[x] = y;
	rink[x] = (rink[b] + rink[a] + 1) % 2;
}

int main()
{
	int tc;
	int n, m;
	int i, cnt=1;
	int key;

	cin >> tc;
	while(tc--)
	{
		init_set();
		key = 0;

		printf("Scenario #%d:\n", cnt++);
		scanf("%d%d", &n, &m);
		for(i=0; i<m; i++)
		{
			scanf("%d%d", &a, &b);
			int fa = find_set(a);
			int fb = find_set(b);
			if(fa!=fb)
			{
				union_set(fa, fb);
			}
			else
			{
				if(rink[a]==rink[b])
				{
					key = 1;
				}
			}
		}
		if(key!=1)
			printf("No suspicious bugs found!\n\n");
		else
			printf("Suspicious bugs found!\n\n");
	}

	return 0;
}
//*/




/*      192K	735MS	C	1165B
#include <stdio.h>

int father[100010], kind[100010];

void makeset(int n)
{
	int i;
	for(i=1;i<=n;++i)
	{
		father[i]=i;
		kind[i]=0;
	}
}

int findset(int x)
{
	int temp;
	if(x!=father[x])
	{
		temp=father[x];
		father[x]=findset(father[x]);
		kind[x]=(kind[x]+kind[temp])%2;   // 这个temp相当重要！
	}

	return father[x];
}

void Union(int x, int y)
{
	int xx, yy;
	xx=findset(x);
	yy=findset(y);

	father[yy]=xx;
	kind[yy]=(kind[x]-kind[y]+1)%2;
}

int main()
{
	int T, N , M, ai, bi, aai, bbi, kk, tt, tag;

	scanf("%d", &T);

	for(kk=0;kk<T;++kk)
	{
		scanf("%d%d", &N, &M);
		
		makeset(N);
		tag=0;

		for(tt=0;tt<M;++tt)
		{
			scanf("%d%d",&ai, &bi);

			aai=findset(ai);
			bbi=findset(bi);

			if(aai!=bbi)
			{
				Union(ai, bi);
			}
			else 
			{
				if(kind[bi]==kind[ai])
				{
					tag=1;
				}
			}
		}

		if(tag==0) 
		{
			printf("Scenario #%d:\n", kk+1);
			printf("No suspicious bugs found!\n\n");
		}
		else
		{
			printf("Scenario #%d:\n", kk+1);
			printf("Suspicious bugs found!\n\n");

		}
	}

	return 0;
}
//*/