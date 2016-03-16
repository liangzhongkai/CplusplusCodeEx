/*
#include<iostream>
#include<queue>
#include<string>

using namespace std;

typedef pair<int, int> pii;

int tc, w, h, M;
int x[4]={1,0,-1,0};
int y[4]={0,1,0,-1};
int ex, ey;

short int map[2][100][100][100];

void inline swit( char ch )
{
	switch( ch )
	{
		case'R':ex++;break;
		case'L':ex--;break;
		case'U':ey++;break;
		case'D':ex--;break;
	}
}

bool inline is_inside( int a, int b )
{
	if( a>=0 && a<w && b>=0 && b<h )
		return true;
	else
		return false;
}

int main()
{
	string road;
	int i;
	int a, b, c, d;

	cin >> tc;
	while( tc-- )
	{
		cin >> w >> h;
		cin >> road;
		cin >> M;

		memset( map, 0, sizeof(map) );
		for( i=0; i<M; i++ )
		{
			cin >> a >> b >> c >> d;
			if( a==c )              //竖
			{
				map[0][a][b][d] = 1;
				map[0][a][d][b] = 1;
			}
			else if( b==d )
			{
				map[1][b][a][c] = 1;
				map[1][b][c][a] = 1;
			}
		}
		
		ex = 0; ey = 0;
		int sx = 0;
		int sy = 0;
		int flag = 0;
		for( i=0; i<road.size(); i++ )
		{
			if( road[i]=='R' )
			{
				if( map[1][ey][ex][ex+1] )
				{
					flag = 1; break;
				}
			}
			else if( road[i]=='L' )
			{
				if( map[1][ey][ex][ex-1] )
				{
					flag = 1; break;
				}
			}
			else if( road[i]=='U' )
			{
				if( map[0][ex][ey][ey+1] )
				{
					flag = 1; break;
				}
			}
			else if( road[i]=='D' )
			{
				if( map[0][ex][ey][ey-1] )
				{
					flag = 1; break;
				}
			}
			swit( road[i] );
		}
		if( flag==1 )
		{
			cout << "INCORRECT" << endl;
			continue;
		}

		queue<pii> q;
		q.push(make_pair(0,0));
		q.push(make_pair(-1,-1));
		int key = 0;
		int count = 1;

        //广搜要记录路径，我不会！
		//应该按照距的走法去试，看能不能去到，在判断是否最短，和是否唯一      ~~~~~~还有多余的没有考虑！
		while( !q.empty() )
		{
			pii temp;
			temp = q.front();
			q.pop();
			
			if( temp.first==ex && temp.second==ey )    //计算该层的可到达目标的路径数
				key++;
			
			if( key==2 )        //多过2条就可退出
				break;
			
			if( temp.first==-1 && temp.second==-1 )     //利用《-1，-1》统计层数
			{
				count++;
				if( key>0 )
					break;
				q.push(make_pair(-1, -1));
				continue;
			}
			
			for(i=0; i<4; i++)
			{
				int nx = temp.first + x[i];
				int ny = temp.second + y[i];
				
				if( is_inside(nx, ny) )
				{
					if( (i==0 || i==2) && !map[1][ny][temp.first][nx] )
					{
						q.push(make_pair(nx, ny));
					}
					else if( (i==1 || i==3) && !map[0][nx][temp.second][ny] )
					{
						q.push(make_pair(nx, ny));
					}
				}
			}

			
		}

		if( key==2 || (count-1)<road.size() )  //不唯一  &&  最短
		{
			cout << "INCORRECT" << endl;
			continue;
		}

		cout << "CORRECT" << endl;
	}

	return 0;
}
//*/











/*          436K	0MS

//（1）判断最短路径是否唯一
//如果不唯一，对于那些unused的点，必存在一个点，
//从起点到这点的最短距离加上从终点到这点的最短距离等于题目给出的最短距离长度
//（2）判断墙是否多余
//检查题目给出的墙分隔的那些点对，对一个一个被墙分隔的点对(a1,b1),(a2,b2),如果分隔它们的墙是多余的，
//那么从起点到(a1,b1)的最短距离加上从终点到(a2,b2)的最短距离必大于题目给出的最短距离长度pathlen，
//且从起点到(a2,b2)的最短距离加上从终点到(a1,b1)的最短距离也必大于pathlen，也就是起点，(a1,b1),(a2,b2),
//终点不可能在一个最短路径上，也就没必要用墙分隔了

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define LEN 15000
#define MAXV 105


typedef struct Node
{
    int x, y;
    int step;
}node;

int dis1[MAXV][MAXV];
int dis2[MAXV][MAXV];
char vis[MAXV][MAXV];
node Q[LEN];
char str[LEN];
int used[MAXV][MAXV];
int notgo[MAXV][MAXV][4];
int tx,ty;
int n;
int trans[130];
int move[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int mlen;
int pair[LEN][4];
int end=0;
int w,h;

int in(int x,int y)
{
    if(x<0||y<0||x>=w||y>=h)
        return 0;
    return 1;
}
int solve()
{
    int i,j;
    int x=0,y=0;
    int x1,y1,x2,y2;
    int head,tail;
    int step,xx,yy;

    trans['U']=0;
    trans['R']=1;
    trans['D']=2;
    trans['L']=3;
    scanf("%s",str);
    memset(used,0,sizeof(used));
    used[0][0]=1;

    mlen=strlen(str);

    for(i=0;str[i];++i)
    {
        x+=move[trans[str[i]]][0];
        y+=move[trans[str[i]]][1];
        used[x][y]=1;
    }
    tx=x;
    ty=y;
    for(i=0;i<w;++i)
        for(j=0;j<h;++j)
            dis1[i][j]=dis2[i][j]=10000000;
    scanf("%d",&n);
    end=0;
    memset(notgo,0,sizeof(notgo));

    for(i=0;i<n;++i)
    {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        pair[end][0]=x1;
        pair[end][1]=y1;
        pair[end][2]=x2;
        pair[end][3]=y2;
        ++end;
        if(x1==x2+1)
            notgo[x1][y1][3]=notgo[x2][y2][1]=1;
        else if(x2==x1+1)
            notgo[x1][y1][1]=notgo[x2][y2][3]=1;
        else if(y1==y2+1)
            notgo[x1][y1][2]=notgo[x2][y2][0]=1;
        else
            notgo[x1][y1][0]=notgo[x2][y2][2]=1;
    }

	// 到源点的距离
    head=0;
    tail=1;
    Q[0].x=0;
    Q[0].y=0;
    Q[0].step=0;
    dis1[0][0]=0;
    memset(vis,0,sizeof(vis));
    vis[0][0]=1;

    while(head<tail)
    {
        x=Q[head].x;
        y=Q[head].y;
        step=Q[head].step;
        for(i=0;i<4;++i)
        {
            if(notgo[x][y][i])
                continue;
            xx=x+move[i][0];
            yy=y+move[i][1];
            if(in(xx,yy)&&vis[xx][yy]==0)
            {
                vis[xx][yy]=1;
                Q[tail].x=xx;
                Q[tail].y=yy;
                Q[tail].step=step+1;
                dis1[xx][yy]=step+1;
                ++tail;
            }
        }
        ++head;
    }

	// 到终点的距离
    head=0;
    tail=1;
    Q[0].x=tx;
    Q[0].y=ty;
    Q[0].step=0;
    memset(vis,0,sizeof(vis));
    vis[tx][ty]=1;
    dis2[tx][ty]=0;

    while(head<tail)
    {
        x=Q[head].x;
        y=Q[head].y;
        step=Q[head].step;
        for(i=0;i<4;++i)
        {
            if(notgo[x][y][i])
                continue;
            xx=x+move[i][0];
            yy=y+move[i][1];
            if(in(xx,yy)&& vis[xx][yy]==0)
            {
                vis[xx][yy]=1;
                Q[tail].x=xx;
                Q[tail].y=yy;
                Q[tail].step=step+1;
                dis2[xx][yy]=step+1;
                ++tail;
            }
        }
        ++head;
    }

    for(i=0;i<w;++i)
        for(j=0;j<h;++j)
        {
            if(used[i][j]==0 && dis1[i][j]+dis2[i][j]<=mlen) // 不是最短
            {
                return 0;
            }
            if(used[i][j]==1 && dis1[i][j]+dis2[i][j] >mlen) // 已知路径不成立
            {   
                return 0;
            }
        }

    for(i=0;i<end;++i)                                       // 多余的围墙
    {
        if(dis1[pair[i][0]][pair[i][1]] + dis2[pair[i][2]][pair[i][3]] >= mlen  &&
           dis2[pair[i][0]][pair[i][1]] + dis1[pair[i][2]][pair[i][3]] >= mlen)
            return 0;
    }
    return 1;
}

int main()
{
//    freopen("in.txt","r",stdin);
    int t;
    scanf("%d",&t);
    while(--t>=0)
    {
        scanf("%d%d",&w,&h);
        if(solve())
            printf("CORRECT\n");
        else
            printf("INCORRECT\n");
    }
    return 0;
}
//*/






//*                          360K	0MS

 //(1)求各点到源点的最小步数（BFS）
 //(2)求各点到终点的最小步数（BFS）
 //(3)如果点不是给定路径上的点，那么：该点到源点的最小步数＋该点到终点的最小步数<给定路径的步数，否则给定路径不是唯一最短的
 //(4)如果两相邻点a、b之间存在墙，那么：a到源点的最小步数＋1＋b到终点的最小步数<=给定路径的步数
 //                             或者 a到终点的最小步数＋1＋b到源点的最小步数<=给定路径的步数，否则墙多余
 //(5)如果存在点不可达，说明存在墙将该点封闭起来，可以证明墙至少有一块多余

#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct Grid
{
    bool inpath;    // 是否是路径方格
    bool uwal;      // 是否有上墙
    bool rwal;      // 是否有右墙
    int scnt;       // 到源点步数
    int dcnt;       // 到终点步数
};

int main(int argc, char** argv)
{
    bool ok;
    int w, h, cnt, steps;   // 1 <= w, h <= 100
    string path;
    Grid grid[100][100];
    queue<pair<int, int> > q;

    int t, x, y, desx, desy, x2, y2, i;
    for (cin >> t; t > 0; --t)
    {
        //  初始化数据
        cin >> w >> h;
        for (y = 0; y < h; ++y)
            for (x = 0; x < w; ++x)
            {
                grid[y][x].inpath = false;
                grid[y][x].uwal = false;
                grid[y][x].rwal = false;
                grid[y][x].scnt = -1;
                grid[y][x].dcnt = -1;
            }

		//  输入路径
        cin >> path;     
        x = 0, y = 0;
        grid[0][0].inpath = true;
        steps = path.size();
        for (i = 0; i < steps; ++i)
        {
            switch(path[i])
            {
                case 'U': ++y; break;
                case 'D': --y; break;
                case 'L': --x; break;
                case 'R': ++x; break;
            }
            grid[y][x].inpath = true;//该点在指定路径上 
        }

		//  标记围栏
        desx = x, desy = y;
        cin >> cnt;
        for (i = 0; i < cnt; ++i)        
        {
            cin >> x >> y >> x2 >> y2;
            if (x == x2)
                if (y + 1 == y2) grid[y][x].uwal = true;
                else grid[y2][x].uwal = true;
            else
                if (x + 1 == x2) grid[y][x].rwal = true;
                else grid[y][x2].rwal = true;
        }

        //  求各点到源点的最小步数（BFS）
        q.push(make_pair(0, 0));
        grid[0][0].scnt = 0;    //到源点的步数
        while (!q.empty())
        {

            y = q.front().first, x = q.front().second;
			q.pop();
            if (y < h - 1 && grid[y][x].uwal == false && grid[y + 1][x].scnt == -1)   //如果不等于-1，就已最短步数！
            {                                                                              //（dijsktra算法的原理）
                grid[y + 1][x].scnt = grid[y][x].scnt + 1;                               //刚好遍历地图上所有的点
                q.push(make_pair(y + 1, x));
            }
            if (0 < y && grid[y - 1][x].uwal == false && grid[y - 1][x].scnt == -1)
            {
                grid[y - 1][x].scnt = grid[y][x].scnt + 1;
                q.push(make_pair(y - 1, x));
            }
            if (0 < x && grid[y][x - 1].rwal == false && grid[y][x - 1].scnt == -1)
            {
                grid[y][x - 1].scnt = grid[y][x].scnt + 1;
                q.push(make_pair(y, x - 1));
            }
            if (x < w - 1 && grid[y][x].rwal == false && grid[y][x + 1].scnt == -1)
            {
                grid[y][x + 1].scnt = grid[y][x].scnt + 1;
                q.push(make_pair(y, x + 1));
            }
        }

        // 求各点到终点的最小步数（BFS）
        q.push(make_pair(desy, desx));
        grid[desy][desx].dcnt = 0;
        while (!q.empty())
        {
            y = q.front().first, x = q.front().second;
			q.pop();
            if (y < h - 1 && grid[y][x].uwal == false && grid[y + 1][x].dcnt == -1)
            {
                grid[y + 1][x].dcnt = grid[y][x].dcnt + 1;
                q.push(make_pair(y + 1, x));
            }
            if (0 < y && grid[y - 1][x].uwal == false && grid[y - 1][x].dcnt == -1)
            {
                grid[y - 1][x].dcnt = grid[y][x].dcnt + 1;
                q.push(make_pair(y - 1, x));
            }
            if (0 < x && grid[y][x - 1].rwal == false && grid[y][x - 1].dcnt == -1)
            {
                grid[y][x - 1].dcnt = grid[y][x].dcnt + 1;
                q.push(make_pair(y, x - 1));
            }
            if (x < w - 1 && grid[y][x].rwal == false && grid[y][x + 1].dcnt == -1)
            {
                grid[y][x + 1].dcnt = grid[y][x].dcnt + 1;
                q.push(make_pair(y, x + 1));
            }
        }

        //  判断路径是否唯一最短？ 墙是否多余？
        ok = true;
        for (y = 0; y < h && ok; ++y)
            for (x = 0; x < w && ok; ++x)
            {
                if (grid[y][x].scnt == -1 || grid[y][x].dcnt == -1)         // 是否有封闭区域
                    ok = false;     

                if (y < h - 1 && grid[y][x].uwal                            // 是否上墙多余
                        && grid[y][x].scnt + grid[y + 1][x].dcnt + 1 > steps
                        && grid[y][x].dcnt + grid[y + 1][x].scnt + 1 > steps)
                    ok = false;     

                if (x < w - 1 && grid[y][x].rwal                            // 是否右墙多余
                        && grid[y][x].scnt + grid[y][x + 1].dcnt + 1 > steps
                        && grid[y][x].dcnt + grid[y][x + 1].scnt + 1 > steps)
                    ok = false;     
                                                                            // 是否存在更短路径或另一最短路径 “<=”
                if (!grid[y][x].inpath && grid[y][x].scnt + grid[y][x].dcnt <= steps)
                    ok = false;     
            }

        if(ok) cout << "CORRECT" << endl;
        else cout << "INCORRECT" << endl;
    }

    return 0;
}

//*/








/*                176K	16MS	C++	1976B

  //说明同上

#include <stdio.h>
#include <string.h>

struct pos
{
	int len[2];
	int used;
	int r;
	int u;
}p[20][20];

int num, wallNum, w, h, Dx, Dy, minPath;

void DFS(int x, int y, int len, int flag)
{
	if (len >= p[x][y].len[flag] && p[x][y].len[flag]!=0)
	   return;
	if (x+y!=0 && (x!=Dx||y!=Dy))
	   p[x][y].len[flag] = len;

	len++;

	if (p[x][y].r==0 && x+1<w)
	   DFS(x+1, y, len, flag);
	if (p[x][y].u==0 && y+1<h)
	   DFS(x, y+1, len, flag);
	if (p[x-1][y].r==0 && x-1>=0)
	   DFS(x-1, y, len, flag);
	if (p[x][y-1].u==0 && y-1>=0)
	   DFS(x, y-1, len, flag);
}

int judge()
{
	int i, j;
	for (i=0; i<w; i++)
	   for (j=0; j<h; j++)
	   {
		if (p[i][j].used==0 && p[i][j].len[0]+p[i][j].len[1]<=minPath)
			return 0;
		if (p[i][j].r==1 && i+1<w && p[i][j].len[0]+p[i+1][j].len[1]+1>minPath &&
			p[i][j].len[1]+p[i+1][j].len[0]+1>minPath)
			return 0;
		if (p[i][j].u==1 && j+1<h && p[i][j].len[0]+p[i][j+1].len[1]+1>minPath &&
		    p[i][j].len[1]+p[i][j+1].len[0]+1>minPath)
			return 0;
	   }
	return 1;
}


int main()
{
	int x, y, x1, y1, x2, y2;
	char c;
	scanf("%d", &num);
	while (num--)
	{
	   memset(p, 0, sizeof(p));
	   scanf("%d %d\n", &w, &h);
	   p[0][0].used = 1;
	   Dx = Dy = minPath = 0;
	   while ((c=getchar())!='\n' && c!=EOF)    //读入方向字符
	   {
			if (c == 'U')
			 p[Dx][++Dy].used = 1;
			else if (c == 'D')
			 p[Dx][--Dy].used = 1;
			else if (c == 'L')
			 p[--Dx][Dy].used = 1;
			else if (c == 'R')
			 p[++Dx][Dy].used = 1;
			minPath++;
	   }

	   scanf("%d", &wallNum);

	   while (wallNum--)
	   {
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			x = x1 - x2;
			y = y1 - y2;
			if (x==0 && y==1)         //x相同， 记录 y值较小 的那个
			 p[x2][y2].u = 1;
			else if (x==0 && y==-1)
			 p[x1][y1].u = 1;
			else if (x==1 && y==0)
			 p[x2][y2].r = 1;
			else if (x==-1 && y==0)
			 p[x1][y1].r = 1;
	   }

	   DFS(0, 0, 0, 0);
	   DFS(Dx, Dy, 0, 1);

	   if(judge())
		printf("CORRECT\n");
	   else
		printf("INCORRECT\n");
	}

	return 0;
}
//*/