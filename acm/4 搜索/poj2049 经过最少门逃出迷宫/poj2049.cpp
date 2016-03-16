/*
8 8
1 1 1 3
2 1 1 2
3 1 1 3
4 1 1 3
1 1 0 3
2 2 0 2
2 3 0 2
1 4 0 3
2 1 1
2 2 1
3 1 1
3 2 1
3 3 1
1 1 0
3 3 0
4 3 1
2.5 3.5
1

1 6
1 2 1 5
0 2 0
0 3 0
0 4 0
0 5 0
0 6 0
0 7 0
0.5 5.5
2

*/

/*
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

int xdoor[201][201];
int ydoor[201][201];
int dis[201][201];

struct point
{
	int x, y;
};

int xx[4] = {1, 0, -1, 0};
int yy[4] = {0, -1, 0, 1};
int maxx, maxy, minx, miny;


int main()
{
	int m, n;
	int i, j;
	
	int x, y, d, t;

	while( cin >> m >> n && m!=-1 && n!=-1 )
	{
		memset(xdoor, 0, sizeof(xdoor));
		memset(ydoor, 0, sizeof(ydoor));
		memset(dis, 0, sizeof(dis));
		for(i=0; i<201; i++)
		{
			xdoor[0][i] = 1; 
			ydoor[i][0] = 1;
		}

		 minx = 200; miny = 200; maxx = -1; maxy = -1;
		 for(i=0; i<m; i++)
		 {
			 int mx=-1, my=-1;
			 cin >> x >> y >> d >> t;
			 if(d==0)
			 {
				 for(j=x; j<x+t; j++)
					ydoor[j][y] = 1;
				 mx = x + t;
			 }
			 else 
			 {
				 for(j=y; j<y+t; j++)
					xdoor[x][j] = 1;
				 my = y + t;
			 }

			 if(x<minx)
				 minx = x;
			 if(mx>maxx)
				 maxx = mx;
			 if(y<miny)
				 miny = y;
			 if(my>maxy)
				 maxy = my;
		 }

		 for(i=0; i<n; i++)
		 {
			 cin >> x >> y >> d;
			 if(d==0)
			 {
				 ydoor[x][y] = 2;
				 if(x<minx)
					 minx = x;
				 if(x+1>maxx)
					 maxx = x+1;
				 if(y<miny)
					 miny = y;
				 if(y>maxy)
					 maxy = y;
			 }
			 else
			 {
				 xdoor[x][y] = 2;
				 if(x<minx)
					 minx = x;
				 if(x>maxx)
					 maxx = x;
				 if(y<miny)
					 miny = y;
				 if(y+1>maxy)
					 maxy = y+1;
			 }
		 }


		 int sx, sy;
		 double gg, hh;
		 cin >> gg >> hh;
		 sx = (int)gg;
		 sy = (int)hh;

		 if(sx<minx || sx>maxx || sy<miny || sy>maxy)
		 {
			 cout << 0 << endl;
			 continue;
		 }

		 //cout << minx << miny << maxx << maxy << endl;

		 queue<point> q;
		 point temp;
		 temp.x = sx;  temp.y = sy;
		 q.push(temp);
		 dis[sx][sy] = 0;
		 int key = 0;
		 int ans = 10000000;

		 while(!q.empty())
		 {
			 point tmp;
			 tmp = q.front();
			 q.pop();

			 //cout << tmp.x << " " << tmp.y << endl;
			 if(tmp.x<minx || tmp.x>=maxx || tmp.y<miny || tmp.y>=maxy)
			 {
				 key = 1;
				 if(ans>dis[tmp.x][tmp.y])
					ans = dis[tmp.x][tmp.y];
				 continue;
			 }

			 for(int i=0; i<4; i++)
			 {
					 temp.x = tmp.x + xx[i];
					 temp.y = tmp.y + yy[i];
				 
					 if(i==0 && xdoor[temp.x][temp.y]!=1 )
					 {
						 if(xdoor[temp.x][temp.y]==2)
						 {
							 if(dis[temp.x][temp.y]!=0 )
							 {
								 if(dis[tmp.x][tmp.y]<dis[temp.x][temp.y]-1)
									dis[temp.x][temp.y] = dis[tmp.x][tmp.y] + 1;
							 }
							 else
								 dis[temp.x][temp.y] = dis[tmp.x][tmp.y] + 1;
						 }
							 
						 q.push(temp);
					 }
					 else if(i==1 && ydoor[tmp.x][tmp.y]!=1 )
					 {
						 if(ydoor[tmp.x][tmp.y]==2 )
						 {
							  if(dis[temp.x][temp.y]!=0 )
							 {
								 if(dis[tmp.x][tmp.y]<dis[temp.x][temp.y]-1)
									dis[temp.x][temp.y] = dis[tmp.x][tmp.y] + 1;
							 }
							 else
								 dis[temp.x][temp.y] = dis[tmp.x][tmp.y] + 1;
						 }
						 q.push(temp);
					 }
					 else if(i==2 && xdoor[tmp.x][tmp.y]!=1 )
					 {
						 if(xdoor[tmp.x][tmp.y]==2)
						{
							  if(dis[temp.x][temp.y]!=0 )
							 {
								 if(dis[tmp.x][tmp.y]<dis[temp.x][temp.y]-1)
									dis[temp.x][temp.y] = dis[tmp.x][tmp.y] + 1;
							 }
							 else
								 dis[temp.x][temp.y] = dis[tmp.x][tmp.y] + 1;
						 }
						 q.push(temp);
					 }
					 else if(i==3 && ydoor[temp.x][temp.y]!=1) 
					 {
						 if(ydoor[temp.x][temp.y]==2)
						{
							  if(dis[temp.x][temp.y]!=0 )
							 {
								 if(dis[tmp.x][tmp.y]<dis[temp.x][temp.y]-1)
									dis[temp.x][temp.y] = dis[tmp.x][tmp.y] + 1;
							 }
							 else
								 dis[temp.x][temp.y] = dis[tmp.x][tmp.y] + 1;
						 }
						 q.push(temp);
					 }
			 }		 
		 }

		 if(key==1)
			 cout << ans << endl;
		 else
			 cout << "-1" << endl;

	}

	return 0;
}
//*/


//*                         972K	250MS	C++	2366B
#include <iostream>
#include <queue>

using namespace std;

#define MAX(a,b) (a>b ? a:b)

const int INF=100000000;
const int MAX_SIZE=256;

struct State
{
	int x,y;
	int c;
	bool operator < (const State &a) const
	{
		return  a.c<c;
	}
};
priority_queue<State> qu;
int vE[MAX_SIZE][MAX_SIZE];
int hE[MAX_SIZE][MAX_SIZE];
int dist[MAX_SIZE][MAX_SIZE];

int N,M;
int Xmax,Ymax;   
int xd,yd;           

void Clear(void)
{
	while(!qu.empty())
	{
		qu.pop();
	}
}

void BFS(void)
{
	int x,y;
	for(x=0; x<Xmax+1; x++)
		for(y=0; y<Ymax+1; y++)
			dist[x][y]=INF;
		
	State pn;
	pn.x=0; pn.y=0;
	pn.c=0;

	dist[0][0]=0;
	qu.push(pn);
	while(!qu.empty())
	{
		pn=qu.top();
		qu.pop();
		x=pn.x; y=pn.y;
		if(x==xd && y==yd)
		{
			return;    
		}
		// 上
		if(y+1 <= Ymax && dist[x][y+1]>dist[x][y]+vE[x][y+1])
		{
			dist[x][y+1]=dist[x][y]+vE[x][y+1];
			pn.x=x; pn.y=y+1; pn.c=dist[x][y+1];
			qu.push(pn);
		}
		// 右
		if(x+1 <=Xmax && dist[x+1][y]>dist[x][y]+hE[x+1][y])
		{
			dist[x+1][y]=dist[x][y]+hE[x+1][y];
			pn.x=x+1; pn.y=y; pn.c=dist[x+1][y];
			qu.push(pn);
		}
		// 下
		if(y-1 >=0 && dist[x][y-1]> dist[x][y]+vE[x][y])
		{
			dist[x][y-1]=dist[x][y]+vE[x][y];
			pn.x=x; pn.y=y-1; pn.c=dist[x][y-1];
			qu.push(pn);
		}
		// 左
		if(x-1 >=0 && dist[x-1][y]>dist[x][y]+hE[x][y])
		{
			dist[x-1][y]=dist[x][y]+hE[x][y];
			pn.x=x-1; pn.y=y; pn.c=dist[x-1][y];
			qu.push(pn);
		}
	}
	dist[xd][yd]=-1;
}

int main(void)
{
	int i,j;
	int x,y,d,t;
	x=INF;
	double ex,ec;

	while(cin>>N>>M)
	{
		if(N==-1 && M==-1)
			break;
		memset(vE,0,sizeof(vE));
		memset(hE,0,sizeof(hE));
		Xmax=0; Ymax=0;

		for(i=0; i<N; i++)
		{
			cin>>x>>y>>d>>t;
			if(d==0)
			{
				for(j=0; j<t; j++)
				{
					vE[x+j][y]=INF;
				}
				Xmax=MAX(x+t,Xmax);
				Ymax=MAX(y,Ymax);
			}
			else


			{
				for(j=0; j<t; j++)
				{
					hE[x][y+j]=INF;
				}
				Xmax=MAX(x,Xmax);
				Ymax=MAX(y+t,Ymax);
			}
		}

		for(i=0; i<M; i++)
		{
			cin>>x>>y>>d;
			if(d==0)
			{
				vE[x][y]=1;  //水平
			}
			else
			{
				hE[x][y]=1;
			}
		}

		cin>>ex>>ec;
		if(ex>Xmax || ec>Ymax)
		{
			cout<<"0"<<endl;
		}
		else
		{
			xd=int(ex); yd=int(ec);
			BFS();
			cout<<dist[xd][yd]<<endl;
			Clear();
		}
	}
	return 0;
}
//*/



