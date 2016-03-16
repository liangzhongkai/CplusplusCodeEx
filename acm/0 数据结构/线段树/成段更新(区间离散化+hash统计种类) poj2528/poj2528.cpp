/*
1
5
1 4
2 6
8 10
3 4
7 10

4
*/
//  1088K	79MS	C++	1890B
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
 
const int maxn = 11111;
bool hash[maxn];
int li[maxn] , ri[maxn];
int X[maxn*3];     // 离散化后的点数 2*maxn + ？
int col[maxn<<4];  // 底层区间是双倍的点数 和 ？，所以是2*maxn+？<<2
int cnt;
 
void PushDown(int rt) {
	if (col[rt] != -1) {
		col[rt<<1] = col[rt<<1|1] = col[rt];
		col[rt] = -1;
	}
}

void update(int L,int R,int c,int l,int r,int rt) {
	if (L <= l && r <= R) {
		col[rt] = c;
		return ;
	}
	PushDown(rt);                  // 当前点
	int m = (l + r) >> 1;
	if (L <= m) update(L , R , c , lson);
	if (m < R) update(L , R , c , rson);
}

// 这个查询没有更新col[]，因为只要查找有多少种col[i]值，即多少个海报被看到
void query(int l,int r,int rt){
	if (col[rt] != -1) {           // 当l-r区间内的col[]值不同时，col[rt] == -1
		if (!hash[ col[rt] ]) cnt ++;
		hash[ col[rt] ] = true;
		return ;
	}
	if (l == r) return ;
	int m = (l + r) >> 1;
	query(lson);
	query(rson);
}

int Bin(int key,int n,int X[]){
	int l = 0 , r = n - 1;
	while (l <= r) {
		int m = (l + r) >> 1;
		if (X[m] == key) return m;
		if (X[m] < key) l = m + 1;
		else r = m - 1;
	}
	return -1;
}

int main() 
{
	int T , n, i;
	scanf("%d",&T);
	while (T --) {
		scanf("%d",&n);
		int nn = 0;
		for (i = 0 ; i < n ; i ++) {
			scanf("%d%d",&li[i] , &ri[i]);
			X[nn++] = li[i];
			X[nn++] = ri[i];
		}

		////////////////////////////////////// 离散化 : 是为了节约空间////////////////////////////////////////
		sort(X , X + nn);
		int m = 1;
		for (i = 1 ; i < nn; i ++) {
			if (X[i] != X[i-1]) X[m ++] = X[i];
		}
		// 因为离散化后，所有点的序号都是连续的，这样会覆盖底层的海报，即使实际上没有完全覆盖
		// 例如：1-10 1-4 6-10， 对应的离散号如下：
		//       1-4  1-2 3-4 ， 这样后两个就完全覆盖了，但是实际上没有覆盖完。
		for (i = m - 1 ; i > 0 ; i --) {
			if (X[i] != X[i-1] + 1) X[m ++] = X[i-1] + 1;
		}
		sort(X , X + m);
		//////////////////////////////////////////////////////////////////////////////////////////////////////

		memset(col , -1 , sizeof(col));
		for (i = 0 ; i < n ; i ++) {
			int l = Bin(li[i] , m , X);   // 将li[i]、ri[i]用序号代替
			int r = Bin(ri[i] , m , X);   // 即将所有海报变成width=1  ——  离散化的用意
			update(l , r , i , 0 , m , 1);
		}
		cnt = 0;
		memset(hash , false , sizeof(hash));
		query(0 , m , 1);
		printf("%d\n",cnt);
	}
	return 0;
}



/*    1516K	63MS	C++	2668B
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#define MAX 10005
using namespace std;
 
struct node{
    int a,b,color,flag;
}s[8*MAX];
 
struct st{
    int x,y;
}t[2*MAX];
 
int N[2*MAX],vs[2*MAX],sim[4*MAX],times,ans;
 
int cmp(int a,int b){
    return a<b;
}
 
int getidex(int y){
    int i=1,j=times+1,mid;
    while(i<=j){
        mid=(i+j)/2;
        if(N[mid]==y)   return mid;
        if(N[mid]>y) j=mid;
        else i=mid+1;
    }
    return 0;
}
 
int Build(int x,int y,int num){
    s[num].color=0;
    s[num].flag=0;
    s[num].a=x; 
    s[num].b=y;
    if(x==y)
        return 0;
    int mid=(x+y)/2;
        Build(x,mid,num+num);
        Build(mid+1,y,num+num+1);
}
 
int modify(int x,int y,int num,int color){
    if(s[num].color>0) //说这个区间会被覆盖，不用再讨论了！
        return 0;
    if(x==s[num].a&&y==s[num].b){//找到查询区间
        if(s[num].flag==0){//判断是否被完全覆盖
            s[num].color=color;
            s[num].flag=1;//染色
            if(!vs[color]){//如果这个颜色没有出现过，计数！
                               //先前我这里忘记考虑了，其实这个也许是这次查询的一个子区间
                              //这里是对其中一个子区间进行染色，计数，当然，其他的子区间肯定也染色！
                              //但是计数只需要一次！！
                ans++;
                vs[color]=1;
            }
        }
        return 0;
    }
    int mid=(s[num].a+s[num].b)/2;
    if(y<=mid)
        modify(x,y,num+num,color);
    else if(x>mid)
        modify(x,y,num+num+1,color);
    else{
        modify(x,mid,num+num,color);
        modify(mid+1,y,num+num+1,color);
    }
        //重点注意一下这里：如果左右子树都被染色了
        //很显然要往上更新父亲节点的染色状态即flag!
    if(s[num+num].flag&&s[num+num+1].flag)
        s[num].flag=1;
}
 
int main(){
    int cas,n,i,j;
    scanf("%d",&cas);
    while(cas--){
        memset(vs,0,sizeof(vs));
        ans=0;
        scanf("%d",&n);
        for(i=1;i<=n;i++)
            scanf("%d%d",&t[i].x,&t[i].y);
                //把左右边界的存放在sim[]里面一边，以便下面的离散操作！
        for(i=1;i<=n;i++){
            sim[i]=t[i].x;
        }
        for(i=n+1,j=1;j<=n;j++,i++){
            sim[i]=t[j].y;
        }
        sort(sim+1,sim+1+2*n,cmp);//升序排序
                //去除重复的边界值
        N[1]=sim[1];
        times=1;
        for(i=2;i<=2*n;i++){
            if(N[times]!=sim[i])
                N[++times]=sim[i];
        }
        Build(1,times,1);
        int color=0;
        for(i=n;i>=1;i--){
            int sx=getidex(t[i].x);
                 //以边界值在sim[]里面的位置，作为当前的边界值，这就是离散的核心思想！
            int sy=getidex(t[i].y);
            modify(sx,sy,1,++color);
        }
        printf("%d\n",ans);
    }
    return 0;
}
//*/


    #include<iostream>
  2 #include<cstdio>
  3 #include<algorithm>
  4 #include<string.h>
  5 #define MAX 20001
  6 
  7 using namespace std;
  8 
  9 int c,n,ls[MAX];

 10 struct node{
 11     int l,r;
 12     int c;
 13 }tree[MAX*4];

 14 struct ln{
 15     int li,num;//num表示第几张海报
 16 }line[MAX];

 17 int set[MAX][2];
 18 bool visit[MAX];
 19 int ans;
 20 
 21 bool cmp(struct ln a,struct ln b){
 22     return a.li<b.li;
 23 }
 24 
 25 void Inittree(int pos,int ll,int rr){
 26     tree[pos].l = ll;
 27     tree[pos].r = rr;
 28     tree[pos].c = 0;
 29     if(ll!=rr){
 30         int mid = (ll+rr)>>1;
 31         Inittree(pos*2,ll,mid);
 32         Inittree(pos*2+1,mid+1,rr);
 33     }
 34 }
 35 
 36 void Insert(int pos,int ll,int rr,int color){
 37     if(tree[pos].l == ll && tree[pos].r == rr){
 38         tree[pos].c = color;
 39         return;
 40     }
 41     if(tree[pos].c > 0 && tree[pos].c != color){
 42         tree[pos*2].c = tree[pos].c;
 43         tree[pos*2+1].c = tree[pos].c;
 44         tree[pos].c = 0;
 45     }
 46     int mid = (tree[pos].l + tree[pos].r)>>1;
 47     if(rr<=mid){
 48         Insert(pos*2,ll,rr,color);
 49     }
 50     else if(ll>mid){
 51         Insert(pos*2+1,ll,rr,color);
 52     }
 53     else{
 54         Insert(pos*2,ll,mid,color);
 55         Insert(pos*2+1,mid+1,rr,color);
 56     }
 57 }
 58 
 59 void Search(int pos){
 60     if(tree[pos].c!=0){
 61         if(!visit[tree[pos].c]){//tree[pos].c
 62             visit[tree[pos].c] = true;
 63             ans++;
 64         }
 65         return ;
 66     }
 67     Search(2*pos);
 68     Search(2*pos+1);
 69 }
 70 
 71 int main()
 72 {
 73     int i;
 74     while(scanf("%d",&c)!=EOF){
 75         while(c--){
 76             scanf("%d",&n);
 77             for(i = 0;i < n;++i){//离散化
 78                 scanf("%d%d",&set[i][0],&set[i][1]);
 79                 line[2*i].li = set[i][0];
 80                 line[2*i].num = -(i+1);//用负数表示 线段起点
 81                 line[2*i+1].li = set[i][1];
 82                 line[2*i+1].num = i+1;
 83             }
 84             sort(line,line+2*n,cmp);
 85             int temp = line[0].li,tp = 1;
 86             for(i = 0;i < 2*n;++i){
 87                 if(line[i].li != temp){
 88                     tp++;
 89                     temp = line[i].li;
 90                 }
 91                 if(line[i].num < 0){
 92                     set[-line[i].num-1][0] = tp;
 93                 }
 94                 else{
 95                     set[line[i].num-1][1] = tp;
 96                 }
 97             }//离散化
 98         
 99             Inittree(1,1,tp);
100             for(i = 0;i < n;++i){
101                 Insert(1,set[i][0],set[i][1],i+1);
102             }
103             memset(visit,0,sizeof(visit));
104             ans = 0;
105             Search(1);
106             printf("%d\n",ans);
107         }
108     }
109     return 0;
110 }