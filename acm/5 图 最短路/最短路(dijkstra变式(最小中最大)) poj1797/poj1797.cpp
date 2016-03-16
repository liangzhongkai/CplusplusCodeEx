/*
//   4248K	1844MS	C++	1052B  cin
//   4240K	422MS	C++	1138B  scanf
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>

using namespace std;


#define INF 0x7fffffff

int mp[1010][1010], dist[1010];
bool vis[1010];

inline int min(int a, int b){
	return a>b?b:a;
}

int main()
{
	int tc;
	int n, m;
	int i, j;
	int a, b, c;
	int cnt = 1;

	cin >> tc;
	while(tc--){
		memset(vis, false, sizeof(vis));
		//memset(dist, 0, sizeof(dist));
		memset(mp, 0, sizeof(mp));

		scanf("%d%d", &n, &m);
		for(i=0; i<m; i++){
			scanf("%d%d%d", &a, &b, &c);
			mp[a][b] = mp[b][a] = c;
		}

		for(i=1; i<=n; i++){
			mp[i][i] = INF;
			dist[i] = mp[1][i];
		}
		
		for(i=1; i<=n; i++){
			int p = -1;
			for(j=1; j<=n; j++){
				if(!vis[j] && (p==-1 || dist[p]<dist[j]))
					p = j;
			}

			if(p==-1)
				break;

			vis[p] = true;

			for(j=1; j<=n; j++){
				if(!vis[j] && dist[j]<min(dist[p], mp[p][j]))
					dist[j] = min(dist[p], mp[p][j]);
			}
		}


		printf("Scenario #%d:\n", cnt);
		printf("%d\n\n", dist[n]);
		//cout << "Scenario #" << cnt << ":" << endl;
		//cout << dist[n] << endl << endl;
		cnt++;
	}

	return 0;
}
//*/




/*      二分+并查的代码，200多ms
//       780K	250MS	C++	1326B
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Scenario;
int VN,ArcN;
int Start[1000005],End[1000005],Weight[1000005];

int ufs[1005];

int find(int x)
{
	if(ufs[x]<0)
		return x;
	else
		return ufs[x] = find(ufs[x]);
}

void setUnion(int r1,int r2)
{
	if(ufs[r1]<ufs[r2])
	{
		ufs[r1] += ufs[r2];
		ufs[r2] = r1;
	}
	else
	{
		ufs[r2] += ufs[r1];
		ufs[r1] = r2;
	}
}

void addConnection(int elem1,int elem2)
{
	int r1 = find(elem1),r2 = find(elem2);
	if( r1 != r2 )
		setUnion(r1,r2);
}

bool connected(int elem1,int elem2)
{
	int r1 = find(elem1),r2 = find(elem2);
	return r1 == r2;
}

bool Good(int k)
{
	int j;
	memset(ufs,-1,sizeof(ufs));
	for(j=1;j<=ArcN;++j)
	{
		if(Weight[j]>=k)
			addConnection(Start[j],End[j]);
	}
	if( !connected(1,VN) )
		return false;
	else
		return true;
}

int main()
{
	int i,j;
	int b,e,m;
	scanf("%d",&Scenario);
	for(i = 1;i<=Scenario;++i)
	{
		scanf("%d%d",&VN,&ArcN);
		for(j=1;j<=ArcN;++j)
			scanf("%d%d%d",&Start[j],&End[j],&Weight[j]);

		b = 1;
		e = 1000000;
		while( b != e )
		{
			m = (b+e)/2;
			if( Good(m) )
				b = m + 1;
			else
				e = m;
		}
		if( Good(b) )
			printf("Scenario #%d:\n%d\n\n",i,b);
		else
			printf("Scenario #%d:\n%d\n\n",i,b-1);

	}
	return 0;
}
//*/




/*  4164K	422MS	C++	1683B

#include <stdio.h>
#include <string.h>

#define MAX_INT 0x7fffffff
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int n, m, path[1010][1010];// 双向有向图 
int map[1010]; // 记录点的当前最优值
int processed[1010]; // 标记该点是否已被抽取

//  初始化map,为了抽取最大值
void init_single_source(int size)
{
    memset(map, 0, sizeof(map));
    map[1] = MAX_INT;
}

int extract_max(int size)
{
    int i, max, max_idx;

    max = 0;
    for (i=1 ; i<=size ; i++)
    {
        if (0 == processed[i] && map[i] > max)
        {
            max = map[i];
            max_idx = i;
        }
    }
    processed[max_idx] = 1;
    return max_idx;
}

int solve(int size)
{
    int i, j, max_idx, min;

    init_single_source(size);
    for (i=1 ; i<=size ; i++)
    {
        max_idx = extract_max(size);
        for (j=1 ; j<=size ; j++)
        {
            if (0 == processed[j] && 0 != path[max_idx][j])
            {
                // 选择这条路径上的边的最小值
                min = MIN(map[max_idx], path[max_idx][j]);
                // 选取可到达当前点的路径中的最小边值的最大值
                if (min > map[j])
                    map[j] = min;
            }
        }
    }

    return map[size];
}

int main(int argc, char *argv[])
{
    int cas, i, j, a, b, w, ret;

    scanf("%d", &cas);
    for (i=1 ; i<=cas ; i++)
    {
        memset(path, 0, sizeof(path));
        memset(processed, 0, sizeof(processed));

        scanf("%d %d", &n, &m);
        for (j=1 ; j<=m ; j++)
        {
            scanf("%d %d %d", &a, &b, &w);
            path[a][b] = path[b][a] = w;
        }

        ret = solve(n);
        printf("Scenario #%d:\n%d\n\n", i, ret);
    }
	return 0;
}

//*/


/*   4096K	500MS	C	890B

#define maxn 1001
#include<string.h>
#include<stdio.h>

long int use[maxn],f[maxn][maxn],d[maxn];

long int min(long int a,long int b)
{
  long int z;
  if (a>=b) z=b;
     else z=a;
  return(z);
}

void main()
{
  long int max,k,q,i1,j1,i,j,x,y,n,m;
  scanf("%ld",&q);

  for(i1=1;i1<=q;i1++)
  {
	  scanf("%ld %ld",&n,&m);
	  memset(f,0,sizeof(f));
      
	  for (j1=1;j1<=m;j1++)
     {scanf("%ld %ld",&x,&y);
      scanf("%ld",&f[x][y]);
      f[y][x]=f[x][y];}

    memset(d,0,sizeof(d));
	memset(use,0,sizeof(use));

    for (i=1;i<=n;i++)
		d[i]=f[1][i];use[1]=1;
    for (k=1;k<=n-1;k++)
     {
		  max=0;
		  for (i=1;i<=n;i++)
			  if (use[i]==0&&d[i]>max)
				{j=i;max=d[i];}
		  use[j]=1;
		  for (i=1;i<=n;i++)
		  if ((use[i]==0)&&(min(d[j],f[j][i])>d[i]))
			  d[i]=min(d[j],f[j][i]);
     }

    printf("Scenario #%ld:\n",i1);
    printf("%ld\n",d[n]);
    printf("\n");
   }
}
//*/