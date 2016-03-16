//*
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

struct point
{
	int x, y;
}plant[5001];

bool Field[5001][5001];

bool cmp( const point &a, const point &b )
{
	if( a.x!=b.x )
		return a.x<b.x;
	else
		return a.y>b.y;
}

int CalFrog( int m, int n, int num, int l, int r )
{
	int ax = plant[l].x;
	int ay = plant[l].y;
	int bx = plant[r].x;
	int by = plant[r].y;

	int nx, ny, count = 2;
	while(1)
	{
		nx = bx * 2 - ax;
		ny = by * 2 - ay;
		if( nx>0 && nx<=m && ny>0 && ny<=n )
		{
			if( Field[nx][ny] )   //有被踩过吗？
			{
				count++;
				ax = bx; 
				ay = by;
				bx = nx;
				by = ny;
			}
			else
				return 0;
		}
		else
		{
			if( count>=3 )
				return count;
			else
				return 0;
		}			
	}
}

int Frog( int m, int n, int num )
{
	int i, j, dx, dy, a, b, A, sum = 0;

	sort( plant, plant+num, cmp );

	for( i=0; i<num; i++ )
		for( j=i+1; j<num; j++ )
		{
			dx = plant[i].x - plant[j].x;
			dy = plant[i].y - plant[j].y;

			if( dx>0 && ((m-plant[i].x)/dx)<sum )   // 没前景
				continue;
			
			a = plant[i].x - dx; 
			b = plant[i].y - dy;
			if( a>0 && b>0 && b+plant[i].y<=n )     // 不合理
				continue;

			A = CalFrog( m, n, num, i, j );
			if( sum<A )
				sum = A;
		}

	return sum;
}

int main()
{
	int m, n, num, i, len;

	    cin >> m >> n;
	
		cin >> num;

		memset( Field, false, sizeof(Field) );
		for( i=0; i<num; i++ )
		{
			cin >> plant[i].x >> plant[i].y;
			Field[plant[i].x][plant[i].y] = true;
		}

		len = Frog( m, n, num );
		cout << len << endl;
	

	return 0;
}
//*/



/*    24880K	1719MS

#include<iostream>
#include<algorithm>

using namespace std;

struct Point
{
    int x,y;
};

int R,C,cnt;
Point pos[5010];
bool map[5010][5010];

int cmp(Point A,Point B)
{
    if(A.x==B.x)
        return A.y<B.y;
    else
        return A.x<B.x;
}

void Solve()
{
    int i,j,CC,ans=-1;
    int disx,disy,tmpx,tmpy;

    sort(pos,pos+cnt,cmp);

    for(i=0;i<cnt;i++)
    {
        for(j=i+1;j<cnt;j++)
        {
            disx=pos[j].x-pos[i].x;
            disy=pos[j].y-pos[i].y;
            tmpx=pos[j].x;
            tmpy=pos[j].y;
            CC=2;
            if((pos[i].x-disx>=1&&pos[i].x-disx<=R&&pos[i].y-disy>=1&&pos[i].y-disy<=C))
                continue;
            while(tmpx+disx>=1 && tmpx+disx<=R && tmpy+disy>=1 && tmpy+disy<=C)
            {
                if(map[tmpx+disx][tmpy+disy])
                {
                    tmpx=tmpx+disx;
                    tmpy=tmpy+disy;
                    CC++;
                }
                else
                    goto L;                
            }            
            if(CC>ans)
                ans=CC;
L:
            ;
        }
    }
    
    if(ans<3)
        cout<<"0"<<endl;
    else
        cout<<ans<<endl;
}

int main()
{
    int i;

    cin>>R>>C;
    cin>>cnt;

    memset(map,0,sizeof(map));

    for(i=0;i<cnt;i++)
    {
        cin>>pos[i].x>>pos[i].y;
        map[pos[i].x][pos[i].y]=1;
    }

    Solve();
    return 0;
}
//*/



/*   16700K	797MS
#include <iostream>
#include <algorithm>
using namespace std;

struct point {
	short x, y;
};

int comp (const void *a, const void *b)
{
	if (((point*)a)->x > ((point*)b)->x) return 1;
	if (((point*)a)->x < ((point*)b)->x) return -1;
	return ((point*)a)->y - ((point*)b)->y;
}

point p[5001];
bool tab[5001][5001];

int main()
{
//	freopen("1.txt", "r", stdin);
	short max, tmp, r, c, n, i, j, cx, cy, dx, dy;  // 如果把此处的变量定义成全局变量的话，耗时就是3700ms了
	bool flag;

	max = 0;
	cin >> r >> c >> n;
	for (i = 0; i < n; ++i)
	{
		scanf ("%d %d", &p[i].x, &p[i].y);
		tab[p[i].x][p[i].y] = true;
	}

	qsort (p, n, sizeof (point), comp);
	for (i = 0; i < n; ++i)
	{
		for (j = i + 1; j < n; ++j)
		{
			dx = p[j].x - p[i].x;
			dy = p[j].y - p[i].y;
			cx = p[i].x - dx;
			cy = p[i].y - dy;

			if (cx >= 1 && cy >= 1 && cy <= c) continue;
			if (dx && dx * max > r) continue;
			if (dy && (dy * max > c || -dy * max > c)) continue;
			
			cx = p[j].x + dx;
			cy = p[j].y + dy;
			tmp = 2;

			flag = true;
			while (cx <= r && cy <= c && cy >= 1) 
			{
				if (!tab[cx][cy]) 
				{
					flag = false;
					break;
				}
				cx += dx;
				cy += dy;
				tmp++;
			}
			if (flag && tmp > 2 && tmp > max) max = tmp;
		}
	}
	cout << max << endl;
	return 0;
}
//*/
