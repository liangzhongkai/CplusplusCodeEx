//*
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

bool vis[65];
int ans[65];
int map[9][9];

struct point
{
	int num;
	int value;
};

int x[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
int y[8] = {-2, -2, -1, -1, 1, 1, 2, 2};


bool cmp( const point &a, const point &b )
{
	return a.value<b.value;
}

bool dfs(int n, int ceng)
{
	int i;


	if( ceng==64 )
	{
		for(i=1; i<64; i++)
		{
			cout << ans[i] << " ";
		}
		cout << ans[64] << endl;
		return true;
	}
	else
	{
		vector<int> v;
		int x1 = (n-1)%8;
		int y1 = n/8;
		for(int i=0; i<8; i++)
		{
			int xx = x1 + x[i];
			int yy = y1 + y[i];
			if( xx>=0 && xx<8 && yy>=0 && yy<8 && !vis[map[yy][xx]]  )
				v.push_back(map[yy][xx]);
		}

		point pt[8];
		int size = v.size();
		for(i=0; i<size; i++)
		{
			pt[i].num = i;

			int sum = 0;
			for(int j=0; j<8; j++)
			{
				int xx = x1 + x[j];
				int yy = y1 + y[j];
				if( xx>=0 && xx<8 && yy>=0 && yy<8 && !vis[map[yy][xx]]  )
					sum++;
			}
			pt[i].value = sum;
		}

		sort(pt, pt+size, cmp);

		for(i=0; i<size; i++)
		{
			ceng++;
			ans[ceng] = v[pt[i].num];
			vis[v[pt[i].num]] = true;

			if(dfs( v[pt[i].num], ceng ))
				return true;


			ceng--;
			vis[v[pt[i].num]] = false;
		}
	}
	return false;
}

int main()
{
	int n;
	int cc = 1;
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			map[i][j] = cc++;

	while( cin >> n && n!=-1 )
	{
		memset(vis, false, sizeof(vis));
		memset(ans, 0, sizeof(ans));

		ans[1] = n;
		vis[n] = true;

		
		dfs(n, 1);
	}
		
	return 0;
}

//*/










/*                    Run Time: 0secs    Run Memory: 312KB


#include<iostream>
#include<cstring>
#include<string>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<map>

using namespace std;

bool used[10][10];
int f[90];

const int row=8;
const int colum=8;

int d[8][2]={{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2},{1,2},{2,1}};
int last;

bool out(int x,int y)    //判断是否出界 
{
    if(x<0||x>7)
         return 1;
    if(y<0||y>7)
          return 1;
    return 0;
}

struct point{
  int x,y;
  int k;
};

bool cmp(const point&x,const point&y)
{
    return x.k<y.k;
}


int cnt(int a,int b)   //计算权值 
{
    int x,y;
    int ret=0;
      for(int i=0;i<8;i++)
      {
              x=a+d[i][0];
              y=b+d[i][1];
              if(!out(x,y)&&used[x][y]==0)ret++;
      }
    return ret;
}

bool solve(int a,int b,int n)
{
    if(n==64){
       last=8*a+b+1;
       return 1;
    }
    
    int c=0;
    point p[10];//此处不可作为全局变量，由于有回溯。
    int x,y;
    
    for(int i=0;i<8;i++)
    {
          x=a+d[i][0];
          y=b+d[i][1];
          if(!out(x,y)&&used[x][y]==0)
          {
               p[c].x=x;
               p[c].y=y;
               p[c].k=cnt(x,y);
               c++;
          }
    }
    
    sort(p,p+c,cmp);
    
    for(int i=0;i<c;i++)
    {
          used[p[i].x][p[i].y]=1;
          if(solve(p[i].x,p[i].y,n+1))
          {
             f[8*p[i].x+p[i].y+1]=8*a+b+1;
             //cout<<p[i].x<<" "<<p[i].y<<endl;
             return 1;
         }
          else  used[p[i].x][p[i].y]=0;
    }
    return 0;
}


void print(int n)
{
     if(f[n]==n)return ;
     print(f[n]);
     cout<<" "<<n;
}


int main()
{
    int n;
    while(cin>>n&&n!=-1)
     {
     memset(used,0,sizeof(used));
     f[n]=n;
     cout<<n;
      n--; 
     used[n/8][n%8]=1;
     solve(n/8,n%8,1);
    // cout<<endl<<"fsdfsd:"<<last<<endl;
     print(last);
     cout<<endl;
     }

} 
//*/




















/*                               Run Time: 0secs    Run Memory: 312KB

#include <iostream>
#include <vector>
#include <algorithm>
#include<cstring>
using namespace std;

int mov_x[8]={1,1,2,2,-1,-1,-2,-2};
int mov_y[8]={2,-2,1,-1,2,-2,1,-1};
int step;//已走步数
int path[65];//马周游路径
bool isv[8][8];//记录一个点有没有被走过

struct point
{
 int x;
 int y;
 int expand;
};

bool cmp(point t1,point t2)//比较函数，拓展点小的排在前面
{
 return (t1.expand<t2.expand);
}

bool dfs(int x,int y)//递归搜索
{
     //将当前点放入路径数组
     isv[x][y]=1;
     path[step]=(8*x+y+1);
     step++;

     //搜完
     if(step==64)
     {
         for(int i=0;i<63;i++)
            cout << path[i]<< " ";
         cout << path[63]<< endl;
         return true;
     }

     int i;
     vector<point> vec; // 存放当前点的8个拓展点
     // 计算8个拓展点各自的拓展点个数
     for(i=0;i<8;i++)
     {
          point k;
          k.x=x+mov_x[i];
          k.y=y+mov_y[i];
          k.expand=0;

          if(k.x>-1&&k.x<8&&k.y>-1&&k.y<8&&isv[k.x][k.y]==0)
          {
              point t;
              for(int j=0;j<8;j++)
              {
                  t.x = k.x + mov_x[j];
                  t.y = k.y + mov_y[j];
                  if(t.x>-1 && t.x<8 && t.y>-1 && t.y<8 && isv[t.x][t.y]==0)
                    k.expand++;
              }
              vec.push_back(k);
          }
     }

     sort(vec.begin(),vec.end(),cmp);//将拓展点个数小的点优先处理
     for(i=0;i<vec.size();i++)//对可能的拓展点进行处理
     {
         if(dfs(vec[i].x,vec[i].y))
			 return true;
     }

     step--;//若当前点不可能继续往下走，则从路径数组中弹出，并置为可访问点
     isv[x][y]=0;
     return false;
}

int main()
{
     int bp;
     cin >> bp;

     while(bp!=-1)
     {
          step=0;
          memset(isv, 0, sizeof(isv));
          dfs((bp-1)/8,(bp-1)%8);

          cin >> bp;
     }
     return 0;
}

//*/
