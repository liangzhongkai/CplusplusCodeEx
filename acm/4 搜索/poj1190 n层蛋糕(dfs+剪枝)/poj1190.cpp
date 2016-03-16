/*   ���Խ���󡱣������Խ��С��
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
				dfs(i, j, V, ceng, i*i);   //  ��ʣ�����V�Ͳ���������£�ѡȡi,j��Ϊ��ǰԲ���塣
		}
	}

	if(minq==0x7fffffff)
		cout << 0 << endl;
	else
		cout << minq << endl;

	return 0;
}
//*/
//  �㷨:����+ ��֦
//	minv[i] i��ʱ����С���
//	mins[i] i��ʱ����С���
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
// ��ʣlevel��,ǰ������Ϊs
void search(int level, int lastR, int lastH, int leftv, int s){ 
	if( level == 0 ){
		if(0 == leftv && s < ans) ans = s ;
		return;
	}
	if (leftv <= 0 )   return ;       //level>0 �����Ѿ�û��ʣ�������
	if( s + mins[level] >= ans || 2*leftv/lastR + s >= ans) return; 
	//ʣ�µ����һ������ԭ���õ�����Сֵ�ˣ�����һ����֦����Ҫ������TLE��16ms����
	if( leftv < minv[level])   return ; //ʣ�µ����̫С��

	if( level == 1){
       // ���һ��
		if((lastR-1)*(lastR-1)*(lastH-1) < leftv) 
              return;              //ʣ�µ����̫���˲�������
		// int r = MIN( sqrt(leftv) , lastR-1);
		for(int r = lastR-1; r > 0; r--)     //�Ӵ�Сö�����е�r
			if(0 == leftv % (r*r) && leftv/(r*r) < lastH ) {   //���н�
				if( s + 2*leftv/r < ans){
					ans = s + 2*leftv/r ;  
					break;           //��һ���ҵ��Ŀ��н�һ������С��
				}
		}	
	}
	else{
		int i,j;
		for(i = lastR-1; i >= level; i--) //�뾶����Ҫ����level
			for(j= lastH - 1 ; j >= level; j--) //�߶����ٴ���level
				search(level-1,i,j,leftv - i*i*j, s+2*i*j); 
	}
}

int main(){
	scanf("%d%d",&n,&m);
	int i,j;
	for( i =MAXR; i>0; i--)
		for(j= MAXH; j>0; j--)
			if( n - i*i*j >= 0)
				search(m-1 , i,j, n - i*i*j , i*i+2*i*j); //��һ�㣬�����+�����
	if(INF == ans) //û�п��н�
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
	if(v+minv[level-1]>n || s+mins[level-1]>bests || 2*(n-v)/r+s>=bests)   //������������ڵ�level-1������level����32ms,���һ����������Ҫ��������
		return ;
	int i,j,hh;
	for(i=r-1;i>=level;i--)
	{
		if(level==m)
			s=i*i;
		hh=in((n-v-minv[level-1])/(i*i),h-1);                              //   û�����Ļ���Time Limit Exceeded
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
//  �㷨:����+ ��֦
//	minv[i] i��ʱ����С���
//	mins[i] i��ʱ����С���

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

void search(int level, int lastR, int lastH, int leftv, int s){ //��ʣlevel��,ǰ������Ϊs


	if( level == 0 ){
		if(0 == leftv && s < ans) ans = s ;
		
		return;
	}
	if (leftv <= 0 ) return ; //level>0 �����Ѿ�û��ʣ�������
	
	if( s + mins[level] >= ans || 2*leftv/lastR + s >= ans) return; 
	//����ʣ�µ����һ������ԭ���õ�����Сֵ�ˣ�����һ����֦����Ҫ������TLE��16ms����
	
	if( leftv < minv[level]) return ; //ʣ�µ����̫С��

	if( level == 1)
	{ //���һ��
		if((lastR-1)*(lastR-1)*(lastH-1) < leftv) return; //ʣ�µ����̫���˲�������

	
		//int r = MIN( sqrt(leftv) , lastR-1);
		for(int r = lastR-1; r > 0; r--) //�Ӵ�Сö�����е�r
			if(0 == leftv % (r*r) && leftv/(r*r) < lastH ) { //���н�
				if( s + 2*leftv/r < ans){
					ans = s + 2*leftv/r ;  
					break; //��һ���ҵ��Ŀ��н�һ������С��
				}
		}	
	}
	else{
		int i,j;
		for(i = lastR-1; i >= level; i--) //�뾶����Ҫ����level
			for(j= lastH - 1 ; j >= level; j--) //�߶����ٴ���level
				search(level-1,i,j,leftv - i*i*j, s+2*i*j); 
	}
}

int main(){
	scanf("%d%d",&n,&m);
	int i,j;
	for( i =MAXR; i>0; i--)
		for(j= MAXH; j>0; j--)
			if( n - i*i*j >= 0)
				search(m-1 , i,j, n - i*i*j , i*i+2*i*j); //��һ�㣬�����+�����
	
	if(INF == ans) //û�п��н�
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
    if (r>1)if (now+2*v/(r-1)>goodr)return 100000000;//----------------------------------------------������仰!
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
