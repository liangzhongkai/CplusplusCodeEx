/*   体积越“大”，表面积越“小”
//    Time Limit Exceeded
#include<iostream>
#include<cmath>
#define in(a,b) (a<b?a:b)
using namespace std;

int minq;
int mins[25], minv[25];
int minr, minh, ceng, V;

void dfs(int r, int h, int v, int ceng, int s)
{
	if(ceng<1)
	{}
	else if(ceng==1 )
	{
		if(r*r*h==v)
		{
			int tmp = s+2*r*h;
			if(tmp<minq)
				minq = tmp;
		}
	}
	else
	{
		if(minv[ceng]>v || mins[ceng]+s>minq || 2*v/r+s>minq)
			return;

		v = v - r*r*h;
		ceng--;
		s += 2*r*h;
		for(int i=r-1; i>=ceng; i--)
		{
			int j = in((v-minv[ceng-1])/(i*i), h-1);
			for(; j>=ceng; j--)
				dfs(i, j, v, ceng, s);
		}
	}
}




int main()
{
	
	int i,  j;
	

	mins[0] = 0;
	minv[0] = 0;

	cin >> V >> ceng;
	minh = minr = ceng;

	for(i=1; i<=ceng; i++)
	{
		mins[i] = mins[i-1] + 2*i*i;
		minv[i] = minv[i-1] + i*i*i;
	}

	minq = 0x7fffffff;
	for(i=25; 1; i--)
	{
		for(j=25; 1; j--)
		{
			if(i*i*j<=V)
				dfs(i, j, V, ceng, i*i);   //  在剩余体积V和层数的情况下，选取i,j作为当前圆柱体。
		}
	}

	if(minq==0x7fffffff)
		cout << 0 << endl;
	else
		cout << minq << endl;

	return 0;
}
//*/
//  算法:搜索+ 剪枝
//	minv[i] i层时的最小体积
//	mins[i] i层时的最小面积
#include <stdio.h>
#include <math.h>
#define MIN(x,y) ((x)<(y)?(x):(y))
#define INF 1000000
#define MAXR 25
#define MAXH 25

int minv[MAXH];
int mins[MAXR];
int n,m;
int ans = INF;

void build(){
	int i=1;
	minv[1] = 1;
	mins[1] = 2;
	for(i=2; i<MAXH; i++)
		minv[i] = minv[i-1] + i*i*i,
		mins[i] = mins[i-1] + 2*i*i;
};
// 还剩level层,前面的面积为s
void search(int level, int lastR, int lastH, int leftv, int s){ 
	if( level == 0 ){
		if(0 == leftv && s < ans) ans = s ;
		return;
	}
	if (leftv <= 0 )   return ;       //level>0 但是已经没有剩余体积了
	if( s + mins[level] >= ans || 2*leftv/lastR + s >= ans) return; 
	//剩下的面积一定大于原来得到的最小值了！！这一步剪枝最重要！！从TLE到16ms……
	if( leftv < minv[level])   return ; //剩下的体积太小了

	if( level == 1){
       // 最后一层
		if((lastR-1)*(lastR-1)*(lastH-1) < leftv) 
              return;              //剩下的体积太多了不可能了
		// int r = MIN( sqrt(leftv) , lastR-1);
		for(int r = lastR-1; r > 0; r--)     //从大到小枚举所有的r
			if(0 == leftv % (r*r) && leftv/(r*r) < lastH ) {   //可行解
				if( s + 2*leftv/r < ans){
					ans = s + 2*leftv/r ;  
					break;           //第一个找到的可行解一定是最小的
				}
		}	
	}
	else{
		int i,j;
		for(i = lastR-1; i >= level; i--) //半径至少要大于level
			for(j= lastH - 1 ; j >= level; j--) //高度至少大于level
				search(level-1,i,j,leftv - i*i*j, s+2*i*j); 
	}
}

int main(){
	scanf("%d%d",&n,&m);
	int i,j;
	for( i =MAXR; i>0; i--)
		for(j= MAXH; j>0; j--)
			if( n - i*i*j >= 0)
				search(m-1 , i,j, n - i*i*j , i*i+2*i*j); //第一层，底面积+侧面积
	if(INF == ans) //没有可行解
		printf("0\n");
	else	printf("%d\n",ans);
	return 0;
}





/*         164K	16MS	C++	843B

#include<stdio.h>
#include<math.h>
#define in(a,b) (a<b?a:b)
int n,m;
int minv[21],mins[21];
int bests;

void dfs(int v,int s,int level,int r,int h)
{
	if(level==0)
	{
		if(v==n && s<bests)
			bests=s;
		return ;
	}
	if(v+minv[level-1]>n || s+mins[level-1]>bests || 2*(n-v)/r+s>=bests)   //如果把中括号内的level-1都换成level就是32ms,最后一个条件最重要！！！！
		return ;
	int i,j,hh;
	for(i=r-1;i>=level;i--)
	{
		if(level==m)
			s=i*i;
		hh=in((n-v-minv[level-1])/(i*i),h-1);                              //   没有这句的话：Time Limit Exceeded
		for(j=hh;j>=level;j--)
			dfs(v+i*i*j,s+2*i*j,level-1,i,j);
	}
			
}

int main()
{
	int i;
	minv[0]=0;
	mins[0]=0;
	for(i=1;i<=20;i++)
	{
		minv[i] = minv[i-1] + i*i*i;
		mins[i] = mins[i-1] + 2*i*i;
	}
	while(scanf("%d%d",&n,&m)==2)
	{
		bests=0x7fffffff;
		dfs(0,0,m,int(sqrt(1.0*n/m)+1),int(1.0*n/(m*m)+1));       //   176K	0MS	C++	963B
		if(bests==0x7fffffff)
			printf("0\n");
		else
			printf("%d\n",bests);
	}
	return 0;
}
//*/





/*                                164K	0MS	C++	1538B
//  算法:搜索+ 剪枝
//	minv[i] i层时的最小体积
//	mins[i] i层时的最小体积

#include <stdio.h>
#include <math.h>
#define MIN(x,y) ((x)<(y)?(x):(y))
#define INF 1000000
#define MAXR 25
#define MAXH 25

int minv[MAXH];
int mins[MAXR];
int n,m;
int ans = INF;

void build()
{
	int i=1;
	minv[1] = 1;
	mins[1] = 2;
	for(i=2; i<MAXH; i++)
		minv[i] = minv[i-1] + i*i*i,
		mins[i] = mins[i-1] + 2*i*i;
};

void search(int level, int lastR, int lastH, int leftv, int s){ //还剩level层,前面的面积为s


	if( level == 0 ){
		if(0 == leftv && s < ans) ans = s ;
		
		return;
	}
	if (leftv <= 0 ) return ; //level>0 但是已经没有剩余体积了
	
	if( s + mins[level] >= ans || 2*leftv/lastR + s >= ans) return; 
	//！！剩下的面积一定大于原来得到的最小值了！！这一步剪枝最重要！！从TLE到16ms……
	
	if( leftv < minv[level]) return ; //剩下的体积太小了

	if( level == 1)
	{ //最后一层
		if((lastR-1)*(lastR-1)*(lastH-1) < leftv) return; //剩下的体积太多了不可能了

	
		//int r = MIN( sqrt(leftv) , lastR-1);
		for(int r = lastR-1; r > 0; r--) //从大到小枚举所有的r
			if(0 == leftv % (r*r) && leftv/(r*r) < lastH ) { //可行解
				if( s + 2*leftv/r < ans){
					ans = s + 2*leftv/r ;  
					break; //第一个找到的可行解一定是最小的
				}
		}	
	}
	else{
		int i,j;
		for(i = lastR-1; i >= level; i--) //半径至少要大于level
			for(j= lastH - 1 ; j >= level; j--) //高度至少大于level
				search(level-1,i,j,leftv - i*i*j, s+2*i*j); 
	}
}

int main(){
	scanf("%d%d",&n,&m);
	int i,j;
	for( i =MAXR; i>0; i--)
		for(j= MAXH; j>0; j--)
			if( n - i*i*j >= 0)
				search(m-1 , i,j, n - i*i*j , i*i+2*i*j); //第一层，底面积+侧面积
	
	if(INF == ans) //没有可行解
		printf("0\n");
	else	printf("%d\n",ans);
	return 0;
}
//*/





/*          1360K	32MS	C++	1288B
#include <cstdio>
#include <string.h>
using namespace std;
int N,V,goodr,MinV[30],maxv[30][101][101];
int MaxV(int n,int r,int h){int s;s=0;
    if (maxv[n][r][h]>-1)return maxv[n][r][h];
    for (int i=0;i<n;i++)s+=(r-i)*(r-i)*(h-i);
    return maxv[n][r][h]=s;
}
int Min(int a,int b){return a>b?b:a;}
int f(int n,int v,int r,int h,int now){
    if (n==0){if (v==0)return now;return 100000000;}
    if (v<0 || now>goodr)return 100000000;
    int m;
    if (r==-1){
       for (int i=n;i*i<=v;i++)for (int j=(v-MinV[n-1])/i/i;j>=n;j--){
           m=f(n-1,v-i*i*j,i,j,i*i+2*i*j);
           if (m<goodr)goodr=m;
       }
       return goodr;
    }
    if (v<MinV[n])return 100000000;
    if (v>MaxV(n,r-1,h-1))return 100000000;
    if (r>1)if (now+2*v/(r-1)>goodr)return 100000000;//----------------------------------------------就是这句话!
    m=100000000;
    for (int i=r-1;i>=n;i--)for (int j=Min(((v-MinV[n-1])/i)/i,h-1);j>=n;j--){
        int w;
        w=f(n-1,v-i*i*j,i,j,2*i*j+now);
        if (w<m)m=w;
    }
    return m;
}     
int main()
{
    memset(maxv,0xff,sizeof(maxv));
    MinV[0]=0;
    for (int i=1;i<30;i++)MinV[i]=MinV[i-1]+i*i*i;
    goodr=100000000;
    scanf("%d %d",&V,&N);
    printf("%d\n",f(N,V,-1,-1,0));
    return 0;
}

//*/
