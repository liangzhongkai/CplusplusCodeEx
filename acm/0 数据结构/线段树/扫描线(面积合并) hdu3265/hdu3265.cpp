//*
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1

const int N = 50010;
int len[N<<2];
int cnt[N<<2];

struct seg{
	int l, r, h, s;
	seg(){}
	seg(int a, int b, int c, int d):l(a),r(b),h(c),s(d){}
	bool operator < (const seg &a) const{
		return h < a.h;
	}
}ss[N<<2];

// 下面两种操作必须对[a,b]进行+1操作，才能进行-1操作，这个区间是限得死死的，不能包含！
// 但是如果用成段更新就不受限制了。。。
void PushUP(int rt, int l, int r){
	cout << cnt[rt] << " ";

    if (cnt[rt])   len[rt]= r+1-l;
    else if (l==r)   len[rt]= 0;
    else   len[rt]= len[rt<<1]+ len[rt<<1|1];

	cout << l << " " << r << " " << len[rt] << endl;
}
void update(int L, int R, int c, int l, int r, int rt){
	if (L<=l && r<=R) {
		cnt[rt] += c;
		PushUP(rt, l, r);
		return ;
	}
	int m = (l + r) >> 1;
	if (L<=m)   update(L , R , c , lson);
	if (m<R)   update(L , R , c , rson);
	PushUP(rt, l, r);
}

int main()
{
	freopen("in.txt", "r", stdin);
	int n; 
	int x1, x2, x3, x4, y1, y2, y3, y4;
	int ct, i;
	int minl, maxr;
	memset(len, 0, sizeof(len));
	memset(cnt, 0, sizeof(cnt));

	while(scanf("%d", &n) && n!=0){
		ct = 0;
		minl = 50010;   maxr = -50010;
		for(i=0; i<n; i++){
			scanf("%d%d%d%d%d%d%d%d", &x1, &y1, &x4, &y4, &x2, &y2, &x3, &y3);
			if(minl>x1)   minl = x1;
			if(maxr<x4)   maxr = x4;
            ss[ct++]= seg(x1, x4, y1, 1); ss[ct++]= seg(x1, x4, y2, -1);
            ss[ct++]= seg(x1, x2, y2, 1); ss[ct++]= seg(x1, x2, y4, -1);
            ss[ct++]= seg(x3, x4, y2, 1); ss[ct++]= seg(x3, x4, y4, -1);
            ss[ct++]= seg(x2, x3, y3, 1); ss[ct++]= seg(x2, x3, y4, -1);
			/*
			scanf("%d %d %d %d", &a, &b, &c, &d);
			if(a<minl)   minl = a;
			if(c>maxr)   maxr = c;
			ss[ct++] = seg(a, c, b, 1);
			ss[ct++] = seg(a, c, d, -1);
			scanf("%d %d %d %d", &a, &b, &c, &d);
			if(a<minl)   minl = a;
			if(c>maxr)   maxr = c;
			ss[ct++] = seg(a, c, b, -1);
			ss[ct++] = seg(a, c, d, 1);
			*/
		}

		sort(ss, ss+ct);

		int ans = 0;
		for(i=0; i<ct; i++){
			cout << ss[i].l << " " << ss[i].r-1 << " " << ss[i].s << " " << minl << " " << maxr-1 << endl;  
			if(ss[i].l<ss[i].r)
				update(ss[i].l, ss[i].r-1, ss[i].s, minl, maxr-1, 1);
			//cout << len[1] << endl;
			ans += len[1] * (ss[i+1].h - ss[i].h);
		}

		printf("%d\n", ans);
	}

	return 0;
}
//*/




/*
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cctype>
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define MID ((l+r)>>1)
using namespace std;
const int maxn= 200001;
struct Seg{
    int l, r, h, s;
    Seg() {}
    Seg(int a, int b, int c, int d): l(a), r(b), h(c), s(d) {}
    bool operator < (const Seg &cmp) const{
        return h<cmp.h;
    }
} ss[maxn<<1];
int sum[maxn<<2], cnt[maxn<<2];

void PushUp(int rt, int l, int r){
	cout << cnt[rt] << " ";

    if (cnt[rt]){
        sum[rt]= r+1-l;
    }
    else {
        if (l==r)   sum[rt]= 0;
        else    sum[rt]= sum[rt<<1]+ sum[rt<<1|1];
    }

	cout << l << " " << r << " " << sum[rt] << endl;
}

void UpDate(int L, int R, int c, int l, int r, int rt){
    if (L>R)    return;
    if (L<=l && r<=R){
        cnt[rt]+= c;
        PushUp(rt, l, r);
        return;
    }
    int m= MID;
    if (L<=m)   UpDate(L, R, c, lson);
    if (m<R)    UpDate(L, R, c, rson);
    PushUp(rt, l, r);
}
int main(){
	freopen("in.txt", "r", stdin);
    int n;
    while(scanf("%d", &n) && n){
        int x1, y1, x2, y2, x3, y3, x4, y4;
        sum[1]= 0;
        int m= 0;
		int minl = 50005, maxr = -50000;
        while(n--){
            scanf("%d%d%d%d%d%d%d%d", &x1, &y1, &x4, &y4, &x2, &y2, &x3, &y3);
			if(minl>x1)   minl = x1;
			if(maxr<x4)   maxr = x4;
            ss[m++]= Seg(x1, x4, y1, 1); ss[m++]= Seg(x1, x4, y2, -1);
            ss[m++]= Seg(x1, x2, y2, 1); ss[m++]= Seg(x1, x2, y4, -1);
            ss[m++]= Seg(x3, x4, y2, 1); ss[m++]= Seg(x3, x4, y4, -1);
            ss[m++]= Seg(x2, x3, y3, 1); ss[m++]= Seg(x2, x3, y4, -1);
        }
        sort(ss, ss+m);
        memset(sum, 0, sizeof(sum));
        memset(cnt, 0, sizeof(cnt));
        __int64 ret= 0;
        __int64 temp= 0;
        for (int i=0;i<m-1;i++){
			//cout << "*****" << ss[i].l << " " << ss[i].r-1 << " " << ss[i].s << " " << sum[1] << endl;  
            UpDate(ss[i].l, ss[i].r -1, ss[i].s, minl, maxr-1, 1);
            ret+= (__int64)((__int64)sum[1]*(__int64)(ss[i+1].h- ss[i].h));
        }
        printf("%I64d\n", ret);

    }

}
//*/


/*    578MS	9124K	2773 B	C++
#include<cstdio>
 #include<cstring>
 #include<cstdlib>
 #define MAXN 50010
 typedef __int64 LL;
 struct Line
 {
     int left,right,high,flag;
 };
 struct node
 {
     int cover,len;
 };
 Line p[MAXN<<3];
 node tree[MAXN<<5];
 int cnt,x[MAXN<<3];
 inline void Post(int x1,int y1,int x2,int y2)
 {
     if(x1!=x2&&y1!=y2)
     {
         x[cnt]=x1;
         p[cnt].left=x1;
         p[cnt].right=x2;
         p[cnt].high=y1;
         p[cnt++].flag=1;
         x[cnt]=x2;
         p[cnt].left=x1;
         p[cnt].right=x2;
         p[cnt].high=y2;
         p[cnt++].flag=-1;
     }
 }
 int cmp1(const void *a,const void *b)
 {
     return *(int *)a-*(int *)b;
 }
 int cmp2(const void *a,const void *b)
 {
     return (*(Line *)a).high-(*(Line *)b).high;
 }
 int Bin(int val,int low,int high)
 {
     int mid;
     while(low<high)
     {
         mid=(low+high)>>1;
         if(x[mid]==val)
             return mid;
         if(x[mid]<val)
             low=mid+1;
         else
             high=mid;
     }
 }
 void Build(int L,int R,int rt)
 {
     tree[rt].len=tree[rt].cover=0;
     if(L!=R)
     {
         int mid=(L+R)>>1;
         Build(L,mid,rt<<1);
         Build(mid+1,R,rt<<1|1);
     }
 }
 inline void PushUp(int L,int R,int rt)
 {
     if(tree[rt].cover)
         tree[rt].len=x[R+1]-x[L];
     else if(L==R)
         tree[rt].len=0;
     else
         tree[rt].len=tree[rt<<1].len+tree[rt<<1|1].len;
 }
 void Update(int st,int en,int flag,int L,int R,int rt)
 {
     if(st<=L&&R<=en)
     {
         tree[rt].cover+=flag;
         PushUp(L,R,rt);
     }
     else
     {
         int mid=(L+R)>>1;
         if(mid>=st)
             Update(st,en,flag,L,mid,rt<<1);
         if(en>mid)
             Update(st,en,flag,mid+1,R,rt<<1|1);
         PushUp(L,R,rt);
     }
 }
 int main()
 {
     LL ans;
     int i,n,m,st,en,x1,y1,x2,y2,x3,y3,x4,y4;
     while(scanf("%d",&n),n)
     {
         for(cnt=i=0;i<n;i++)
         {
             scanf("%d%d%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
             Post(x1,y1,x2,y3);
             Post(x1,y4,x2,y2);
             Post(x1,y3,x3,y4);
             Post(x4,y3,x2,y4);
         }
         qsort(x,cnt,sizeof(x[0]),cmp1);
         qsort(p,cnt,sizeof(p[0]),cmp2);
         for(i=m=0;i<cnt;i++)
         {
             if(x[i]!=x[m])
                 x[++m]=x[i];
         }
         Build(0,m,1);
         for(ans=i=0;i<cnt-1;i++)
         {
             st=Bin(p[i].left,0,m+1);
             en=Bin(p[i].right,0,m+1);
             Update(st,en-1,p[i].flag,0,m,1);
             ans+=(LL)(p[i+1].high-p[i].high)*tree[1].len;
         }
         printf("%I64d\n",ans);
     }
     return 0;
 }
//*/