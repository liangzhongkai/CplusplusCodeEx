//  268K	0MS	C++	2018B
// 268K	16MS	C++	1761B    用我的Isok()函数
#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

#define INF 2000000000
#define MAXN 100

struct point{
	double x, y;
};

struct edge{
	int u, v;
};

int n;
double wx[20];
point p[MAXN];
int ps;
double py[20][4];
double g[MAXN][MAXN];
edge e[MAXN*MAXN];
int es;
int i, j;

double Dis(point a, point b){
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

//*
bool Isok(point a, point b){
	int i = 0;
	double tmp;
	while(wx[i]<=a.x && i<n)   i++;
	while(wx[i]<b.x && i<n){
		tmp = (wx[i]-a.x)*(b.y-a.y)/(b.x-a.x) + a.y;
		if(tmp>=0 && tmp<py[i][0] ||
			tmp>py[i][1] && tmp<py[i][2] ||
			tmp>py[i][3])
			return false;
		i++;
	}
	return true;
}
//*/

/*
//  判断（x3, y3）是否位于点（x1, y1）和点（x2, y2）确定的直线的上方还是下方
double Cross(double x1, double y1, double x2, double y2, double x3, double y3){
	return (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);
}

bool Isok(point a, point b){
	if(a.x>=b.x)   return false;
	int i = 0;
	while(wx[i]<=a.x && i<n)   i++;
	while(wx[i]<b.x && i<n){
		if(Cross(a.x, a.y, b.x, b.y, wx[i], 0)*Cross(a.x, a.y, b.x, b.y, wx[i], py[i][0])<0 ||
			Cross(a.x, a.y, b.x, b.y, wx[i], py[i][1])*Cross(a.x, a.y, b.x, b.y, wx[i], py[i][2])<0 ||
			Cross(a.x, a.y, b.x, b.y, wx[i], py[i][3])*Cross(a.x, a.y, b.x, b.y, wx[i], 10)<0)
			return false;
		i++;
	}
	return true;
}
//*/
double bellman(int beg, int end){
	double d[MAXN];
	for(i=0; i<MAXN; i++)
		d[i] = INF;
	d[beg] = 0;
	bool flag = true;
	for(i=0; i<ps && flag; i++){
		flag = false;
		for(j=0; j<es; j++){
			if(d[e[j].u]<INF && d[e[j].v] > d[e[j].u] + g[e[j].u][e[j].v]){
				d[e[j].v] = d[e[j].u] + g[e[j].u][e[j].v];
				flag = true;
			}
		}
	}
	return d[end];
}

void solve(){
	p[0].x = 0;
	p[0].y = 5;
	ps = 1; 
	for(i=0; i<n; i++){
		scanf("%lf", &wx[i]);
		for(j=0; j<4; j++){
			p[ps].x = wx[i];
			scanf("%lf", &p[ps].y);
			py[i][j] = p[ps].y;
			ps++;
		}
	}
	p[ps].x = 10;
	p[ps++].y = 5;

	for(i=0; i<ps; i++){
		for(j=0; j<ps; j++)
			g[i][j] = INF;
	}
	es = 0; 
	for(i=0; i<ps; i++){
		for(j=i+1; j<ps; j++ ){
			if(Isok(p[i], p[j])){
				g[i][j] = Dis(p[i], p[j]);
				e[es].u = i;
				e[es].v = j;
				es++;
			}
		}
	}
	printf("%.2lf\n", bellman(0, ps-1));
}

int main()
{
	while(scanf("%d", &n)!=EOF){
		if(n==-1)   break;
		solve();
	}

	return 0;
}


/*
#include <iostream>
#include <cmath>
#define eps 1e-8
#define inf 100000000
using namespace std;

struct Wall{
    double x;
    double y[6];
}wall[20];
double dist[80][80];
double xmult(double x0,double y0,double x1,double y1,double x2,double y2){
    return (x1-x0)*(y2-y0)-(x2-x0)*(y1-y0);
}
int dblcmp( double a ){
    if( fabs(a)< eps )    return 0;
    return (a>0)?1:-1;
}
bool Cross( double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3 ){
    return (dblcmp(xmult(x0,y0,x2,y2,x3,y3))^dblcmp(xmult(x1,y1,x2,y2,x3,y3)))==-2 &&
        (dblcmp(xmult(x2,y2,x0,y0,x1,y1))^dblcmp(xmult(x3,y3,x0,y0,x1,y1)))==-2;
}
bool Direct( int i, int j, int p, int q ){        //判断从墙i的第j个点到墙p第q个点是否直达
    int k, l;
    for( k= i+1; k< p; k++ ){
        for( l= 0; l< 6; l+= 2 )
            if( Cross(wall[i].x,wall[i].y[j],wall[p].x,wall[p].y[q],
                wall[k].x,wall[k].y[l],wall[k].x,wall[k].y[l+1]) )
                return false;
    }
    return true;
}
inline double Dist( double x1, double y1, double x2, double y2 ){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
};
typedef double elem_t;
double dijkstra(int n){
    int v[81],i,j,k;
    double min[81];
    for (i=0;i<=n;i++)
        min[i]=inf,v[i]=0;
    for (min[0]=0,j=0;j<=n;j++){
        for (k=-1,i=0;i<=n;i++)
            if (!v[i]&&(k==-1||min[i]<min[k]))
                k=i;
        for (v[k]=1,i=0;i<=n;i++)
            if (!v[i]&&min[k]+dist[k][i]<min[i])
                min[i]=min[k]+dist[k][i];
    }
    return min[n];
}
int main(){
    int n, i, j, k, l;
    wall[0].x= 0;
    wall[0].y[0]= 5;
    while( scanf("%d",&n) && n!=-1 ){
        for( i= 0; i<= n*4+1; i++ )
            for( j= 0; j<= n*4+1; j++ )
                dist[i][j]= inf;
        wall[n+1].x= 10;
        wall[n+1].y[1]= 5;
        bool con= true;
        for( i= 1; i<= n; i++ ){
            scanf("%lf",&wall[i].x);
            for( j= 1; j< 5; j++ )
                scanf("%lf",&wall[i].y[j]);
            if( wall[i].y[1]>5 || wall[i].y[4]<5 || wall[i].y[2]<5&&wall[i].y[3]>5 )
                con= false;
            wall[i].y[0]= 0;
            wall[i].y[5]= 10;
        }
        if( con ){
            puts("10.00");
            continue;
        }
        for( i= 1; i<= n; i++ ){
            for( j= 1; j< 5; j++ ){
                if( i< n )
                    for( k= 1; k< 5; k++ )
                        dist[i*4+j-4][i*4+k]= Dist(wall[i].x,wall[i].y[j],wall[i+1].x,wall[i+1].y[k]);
                if( Direct( 0, 0, i, j ) )
                    dist[0][i*4+j-4]= Dist(0,5,wall[i].x,wall[i].y[j]);
                if( Direct( i, j, n+1, 1 ) )
                    dist[i*4+j-4][n*4+1]= Dist(wall[i].x,wall[i].y[j],10,5);
                for( k= i+2; k<= n; k++ )
                    for( l= 1; l< 5; l++ )
                        if( Direct(i,j,k,l) )    
                            dist[i*4+j-4][k*4+l-4]= Dist(wall[i].x,wall[i].y[j],wall[k].x,wall[k].y[l]);
            }
        }
        printf("%.2lf\n",dijkstra(n*4+1));
    }
    return 0;
}
//*/