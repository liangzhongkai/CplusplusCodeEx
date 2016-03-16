/*
6 6
WWSBBB
WSSBBB
WSBBBB
WSBBBB
WSSSBB
WWWSBB
7

6 7
WWSSBBB
WSSSBBB
WSSBBBB
WSSBBBB
WSSSSBB
WWSSBBB

6 6
WWSBBB
WWSSBB
WWSBBB
WWSSBB
WWWSSB
WWWWSB
*/
/*
#include<iostream>
#include<queue>

using namespace std;

const int INF = 1000000000;

int r, c; 
int ans;
char map[201][201];
bool vis[201][201];
int dist[201][201];

struct point
{
	int x, y;
	int v;
	bool operator < (const point &a) const
	{
		return a.v<v;
	}
};

void BFS(int n)
{
	int i, j;
	for(i=0; i<r; i++)
		for(j=0; j<c; j++)
			dist[i][j] = INF;

	priority_queue<point> q;
	point temp;
	temp.x = 0; temp.y = n; temp.v = 0;
	q.push(temp);
	dist[temp.x][temp.y] = 1;

	while(!q.empty())
	{
		point tmp;
		tmp = q.top();
		q.pop();

		if(tmp.x==r-1)
			continue;

		if(map[tmp.x+1][tmp.y]=='S' && dist[tmp.x+1][tmp.y]>dist[tmp.x][tmp.y] + 1)
		{
			dist[tmp.x+1][tmp.y] = dist[tmp.x][tmp.y] + 1;
			temp.x = tmp.x + 1; temp.y = tmp.y; temp.v = 0;
			q.push(temp);
		}
		if(map[tmp.x][tmp.y-1]=='S' && dist[tmp.x][tmp.y-1]>dist[tmp.x][tmp.y] + 1)
		{
			dist[tmp.x][tmp.y-1] = dist[tmp.x][tmp.y] + 1;
			temp.x = tmp.x; temp.y = tmp.y - 1; temp.v = 1;
			q.push(temp);
		}
		if(map[tmp.x][tmp.y+1]=='S' && dist[tmp.x][tmp.y+1]>dist[tmp.x][tmp.y] + 1)
		{
			dist[tmp.x][tmp.y+1] = dist[tmp.x][tmp.y] + 1;
			temp.x = tmp.x; temp.y = tmp.y + 1; temp.v = 1;
			q.push(temp);
		}
	}

	int min = 500;
	for(i=1; i<r-1; i++)
		if( map[r-1][i]=='S' && min>dist[r-1][i])
			min = dist[r-1][i];

	if(min<ans)
		ans = min;
}

int main()
{
	int i, j;
	while(cin >> r >> c && r!=0 && c!=0)
	{
		char tmp = cin.get();
		for(i=0; i<r; i++)
		{
			 gets(map[i]);
		}

		for(i=0; i<r; i++)
		{
			for(j=c-1; j>0; j--)
				if(map[i][j]=='S')
				{
					map[i][j+1] = 'S';
					break;
				}
		}

		ans = 500;
		for(i=1; i<c-1; i++)
			if(map[0][i]=='S')
				BFS(i);

		cout << ans << endl;
	}

	return 0;
}
//*/


//*  164K	16MS	C++	688B
#include <iostream>
using namespace std;

char s[202];
int pos[202];

int main()
{
	int M,N,i,j;
	while(scanf("%d%d",&N,&M)!=EOF&&M&&N)
	{
		int sum_S=0,mark=0;
		for(i=1;i<=N;i++)
		{
			mark=0;
			scanf("%s",s);
			for(j=M-1;j>=0;j--)
				if(s[j]=='S')
				{
					sum_S++;       // 计算S的总个数
					if(mark==0)
					{
						pos[i]=j+1;   // 得出各行最右S的B位置
						mark=1;
					}
				}
		}

		int k=2, count=0, special=0;  // special是开头与结尾时考虑的
		for(i=2;i<=N;i++)             // count是计算左右个数
		{ //　不考虑相等
			if(pos[i]<pos[i-1])  // 左
				k=1;
			if(pos[i]>pos[i-1] && k>=1)  // 右 & 前面那个是向左 
			{
				if(k==2)      
					special++;
				k=0;
				count++;
			}
			if(i==N&&k==1)
			{
				count++;
				special++;
			}
		}

		printf("%d\n",sum_S-count*2+special);
	}
	return 0;
}

//*/






/*      568K	16MS	C++	2945B
#include<stdio.h>
#include<string.h>

struct node
{
    int x;
    int y;
}q[50000];

int n,m;
int head,rear;
char map[210][210];
int gra[210][210];
int step[210][210];

void extendnode(struct node cur)
{
    int i,j;
    int tx=cur.x;
    int ty=cur.y;
    int td=step[tx][ty];
    tx++;
    if(tx==n-1)
    {
        if(!gra[tx][ty])
        {
            step[tx][ty]=td+1;
        }
    }
    else
    {
        while(!gra[tx][ty])
        {
            if(!gra[tx+1][ty])
            {
                int dist=td+cur.y-ty+1;
                if(step[tx][ty]==0)
                {
                    struct node temp;
                    step[tx][ty]=dist;
                    temp.x=tx;
                    temp.y=ty;
                    q[rear++]=temp;
                }
                else if(step[tx][ty]>dist)
                {
                    step[tx][ty]=dist;
                }
            }
            ty--;
        }
        ty=cur.y+1;
        while(!gra[tx][ty])
        {
            if(!gra[tx+1][ty])
            {
                int dist=td-cur.y+ty+1;
                if(step[tx][ty]==0)
                {
                    struct node temp;
                    step[tx][ty]=dist;
                    temp.x=tx;
                    temp.y=ty;
                    q[rear++]=temp;
                }
                else if(step[tx][ty]>dist)
                {
                    step[tx][ty]=dist;
                }
            }
            ty++;
        }
    }
}

int main()
{
    int i,j,k;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        if(n==0&&m==0) break;
        memset(step,0,sizeof(step));
        for(i=0;i<n;i++)
        {
            scanf("%s",map[i]);
        }
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
            {
                if(map[i][j]=='W') gra[i][j]=-1;
                else if(map[i][j]=='S') gra[i][j]=0;
                else if(map[i][j]=='B') gra[i][j]=1;
            }
            for(j=m-1;j>=0;j--)
                if(gra[i][j]==1&&gra[i][j-1]==0) gra[i][j]=0;
        }

        struct node start,start1;
        for(i=0;i<m;i++)
            if(!gra[0][i])
            {
                start.x=0;
                start.y=i;
                break;
            }

        head=0,rear=0;
        step[start.x][start.y]=1;
        q[rear++]=start;
        if(start.y+1<m-1)
        {
            start1.x=0;
            start1.y=start.y+1;
            q[rear++]=start1;
            step[start1.x][start1.y]=1;
        }
        while(head<rear)
        {
            struct node top=q[head];
            head++;
            extendnode(top);
        }
        int res=1000000;
        for(i=0;i<m;i++)
        {
            if(step[n-1][i]&&step[n-1][i]<res)
                res=step[n-1][i];
        }
        printf("%d\n",res);
    }
}
//*/

