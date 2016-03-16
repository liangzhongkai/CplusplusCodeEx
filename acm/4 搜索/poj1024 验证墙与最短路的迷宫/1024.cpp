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
			if( a==c )              //��
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

        //����Ҫ��¼·�����Ҳ��ᣡ
		//Ӧ�ð��վ���߷�ȥ�ԣ����ܲ���ȥ�������ж��Ƿ���̣����Ƿ�Ψһ      ~~~~~~���ж����û�п��ǣ�
		while( !q.empty() )
		{
			pii temp;
			temp = q.front();
			q.pop();
			
			if( temp.first==ex && temp.second==ey )    //����ò�Ŀɵ���Ŀ���·����
				key++;
			
			if( key==2 )        //���2���Ϳ��˳�
				break;
			
			if( temp.first==-1 && temp.second==-1 )     //���á�-1��-1��ͳ�Ʋ���
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

		if( key==2 || (count-1)<road.size() )  //��Ψһ  &&  ���
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

//��1���ж����·���Ƿ�Ψһ
//�����Ψһ��������Щunused�ĵ㣬�ش���һ���㣬
//����㵽������̾�����ϴ��յ㵽������̾��������Ŀ��������̾��볤��
//��2���ж�ǽ�Ƿ����
//�����Ŀ������ǽ�ָ�����Щ��ԣ���һ��һ����ǽ�ָ��ĵ��(a1,b1),(a2,b2),����ָ����ǵ�ǽ�Ƕ���ģ�
//��ô����㵽(a1,b1)����̾�����ϴ��յ㵽(a2,b2)����̾���ش�����Ŀ��������̾��볤��pathlen��
//�Ҵ���㵽(a2,b2)����̾�����ϴ��յ㵽(a1,b1)����̾���Ҳ�ش���pathlen��Ҳ������㣬(a1,b1),(a2,b2),
//�յ㲻������һ�����·���ϣ�Ҳ��û��Ҫ��ǽ�ָ���

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

	// ��Դ��ľ���
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

	// ���յ�ľ���
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
            if(used[i][j]==0 && dis1[i][j]+dis2[i][j]<=mlen) // �������
            {
                return 0;
            }
            if(used[i][j]==1 && dis1[i][j]+dis2[i][j] >mlen) // ��֪·��������
            {   
                return 0;
            }
        }

    for(i=0;i<end;++i)                                       // �����Χǽ
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

 //(1)����㵽Դ�����С������BFS��
 //(2)����㵽�յ����С������BFS��
 //(3)����㲻�Ǹ���·���ϵĵ㣬��ô���õ㵽Դ�����С�������õ㵽�յ����С����<����·���Ĳ������������·������Ψһ��̵�
 //(4)��������ڵ�a��b֮�����ǽ����ô��a��Դ�����С������1��b���յ����С����<=����·���Ĳ���
 //                             ���� a���յ����С������1��b��Դ�����С����<=����·���Ĳ���������ǽ����
 //(5)������ڵ㲻�ɴ˵������ǽ���õ�������������֤��ǽ������һ�����

#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct Grid
{
    bool inpath;    // �Ƿ���·������
    bool uwal;      // �Ƿ�����ǽ
    bool rwal;      // �Ƿ�����ǽ
    int scnt;       // ��Դ�㲽��
    int dcnt;       // ���յ㲽��
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
        //  ��ʼ������
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

		//  ����·��
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
            grid[y][x].inpath = true;//�õ���ָ��·���� 
        }

		//  ���Χ��
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

        //  ����㵽Դ�����С������BFS��
        q.push(make_pair(0, 0));
        grid[0][0].scnt = 0;    //��Դ��Ĳ���
        while (!q.empty())
        {

            y = q.front().first, x = q.front().second;
			q.pop();
            if (y < h - 1 && grid[y][x].uwal == false && grid[y + 1][x].scnt == -1)   //���������-1��������̲�����
            {                                                                              //��dijsktra�㷨��ԭ��
                grid[y + 1][x].scnt = grid[y][x].scnt + 1;                               //�պñ�����ͼ�����еĵ�
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

        // ����㵽�յ����С������BFS��
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

        //  �ж�·���Ƿ�Ψһ��̣� ǽ�Ƿ���ࣿ
        ok = true;
        for (y = 0; y < h && ok; ++y)
            for (x = 0; x < w && ok; ++x)
            {
                if (grid[y][x].scnt == -1 || grid[y][x].dcnt == -1)         // �Ƿ��з������
                    ok = false;     

                if (y < h - 1 && grid[y][x].uwal                            // �Ƿ���ǽ����
                        && grid[y][x].scnt + grid[y + 1][x].dcnt + 1 > steps
                        && grid[y][x].dcnt + grid[y + 1][x].scnt + 1 > steps)
                    ok = false;     

                if (x < w - 1 && grid[y][x].rwal                            // �Ƿ���ǽ����
                        && grid[y][x].scnt + grid[y][x + 1].dcnt + 1 > steps
                        && grid[y][x].dcnt + grid[y][x + 1].scnt + 1 > steps)
                    ok = false;     
                                                                            // �Ƿ���ڸ���·������һ���·�� ��<=��
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

  //˵��ͬ��

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
	   while ((c=getchar())!='\n' && c!=EOF)    //���뷽���ַ�
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
			if (x==0 && y==1)         //x��ͬ�� ��¼ yֵ��С ���Ǹ�
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