/*无论用什么方法，都是为了可以快速查找到当前位置后第K个位置是哪个？
//    12124K	1204MS	C++	1562B
#include<iostream>
#include<cstdio>

using namespace std;

int rprime[35]={1,2,4,6,12,24,36,48,60,120,180,240,360,720,840,1260,1680,2520,5040,7560,10080,15120,20160,25200,27720,45360,50400,55440,83160,110880,166320,221760,277200,332640,498960};  
int nprime[35]={1,2,3,4,6,8,9,10,12,16,18,20,24,30,32,36,40,48,60,64,72,80,84,90,96,100,108,120,128,144,160,168,180,192,200};  

#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1

const int N = 555555;
int sum[N<<2];

char name[N][12];
int d[N];
int t;
int ans;

void pushup(int rt){
	sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}

void build(int l, int r, int rt){
	if(l==r){
		sum[rt] = 1;
		return ;
	}
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
	pushup(rt);
}

void update(int p, int add, int l, int r, int rt){
	if(l==r){
		sum[rt] += add;
		ans = l;
		return ;
	}
	int m = (l + r) >> 1;
	if(p<=sum[rt<<1])   update(p,add, lson);
	else   update(p-sum[rt<<1],add, rson);
	pushup(rt);
}

int main()
{
	int n, k;
	int i;
	int tmp;
	int &mod = sum[1];

	while(scanf("%d%d", &n, &k)!=EOF){
		build(1, n, 1);
		for(i=1; i<=n; i++){
			scanf("%s %d", name+i, d+i);
		}
		for(i=0; i<35; i++){
			if(n<rprime[i])   break;
		}
		tmp = i - 1;

		ans = 0;
		d[0] = k+1;
		t = 0;
		for(i=0; i<rprime[tmp]; i++){
			if(d[ans]>0)
				t = (t-2 + d[ans]) % mod + 1;
			else
				t = (t-1 + d[ans]%mod + mod) % mod + 1;
			update(t, -1, 1, n, 1);
		}
		
		printf("%s %d\n", name[ans], nprime[tmp]);
	}
	return 0;
}
//*/


/*
3 1
Tom 2
Jack 4
Mary -1
4 1
Tom 2
Jack 4
Mary -1
Sam 1
*/






//*  树状数组
    #include <iostream>
    #include <string>

    #define F(i,a,b) for (int i=a;i<=b;i++)

    using namespace std;

    const int N = 500002;
     
    int people[N],n, f[N], k, card[N];
    string name[N];
     
    int lowbit(int x){
         return x&(-x);
    }
     
    void modify(int i,int d){
         while (i<=N){
            people[i] += d;
            i+=lowbit(i);
         }
    }
     
    int sum(int i){
         int ret;
         for (ret=0;i>0;i-=lowbit(i))
            ret+=people[i];
         return ret;
    }
     
    int bsearch(int left, int right, int v)
    {
        while (left<right)
        {
            int mid = (left+right)/2;
            if (sum(mid)<v)
                left = mid+1;
            else
                right = mid;
        }
     
        return left;
    }
     
    int main()
    {
        char str[15];
     
        scanf("%d%d\n", &n, &k);
        F(i,1,n)
        {
            scanf("%s%d", str, &card[i]);
            name[i] = string(str);
            modify(i, 1);
        }
        int total = n;
        // init
        int Max = 0, pos = 0;
        F(i,1,n)
            for (int j = i;j<=n;j+=i)
            {
                f[j]++;
                if (f[j]>Max)
                {
                    Max = f[i];
                    pos = j;
                }
            }
     
        int now = k;
        F(round, 1, pos-1)
        {
            modify(now, -1);
            n–;
     
            int num;
            if (card[now]>=0)
                num = (card[now]-1)%n+1;
            else
                num = n+1 +( (card[now]+1)%n-1);
            // count the one out
            // people sit on the left
            int sumnow = sum(now), sumn = sum(total);
     
            if (sumn – sumnow >= num)
                now = bsearch(now, total, sumnow+num);
            else
                now = bsearch(1, now, num-( sumn-sumnow ) );
        }
     
        cout << name[now] << " " << Max << endl;
     
     
        return 0;
    }


//*/








/*打表反素数代码：

#include<stdio.h>


__int64 bestNum;   //约数最多的数
__int64 bestSum;   //约数最多的数的约数个数

__int64 n;

__int64 sushu[7]={2,3,5,7,11,13,17}; //2*3*5*7*11*13*17>500000，所以只需考虑到17即可

void getNum(__int64 num,__int64 k,__int64 sum,__int64 limit) 
//当前走到num这个数，接着用第k个素数，num的约数个数为sum，第k个素数的个数上限为limit
{
 if(num>n)
  return;
 if(sum>bestSum)
 {
  bestSum = sum;
  bestNum = num;
 }
 else if(sum == bestSum && num < bestNum) //约数个数一样时，取小数
 {
  bestNum = num;
 }
 if(k>=7) //只需考虑到素数17,即sushu[6]
  return;
 __int64 i;
 __int64 p = 1;
 for(i=1;i<=limit;i++) //素数k取i个
 {
  p*=sushu[k];
  getNum(num*p,k+1,sum*(i+1),i);
 }
}

__int64 log2(__int64 n) //求大于等于log2（n）的最小整数
{
 __int64 i = 0;
 __int64 p = 1;
 while(p<n)
 {
  p*=2;
  i++;
 }
 return i;
}

int main()
{
 FILE * cfPtr;
 cfPtr = fopen("out.txt","w");
 n = 500000;
 int i = 0;
 while(n>0)
 {
  bestNum = 1;
  bestSum = 1;
  getNum(1,0,1,log2(n));
  fprintf(cfPtr,"%d,",bestNum);
  fprintf(cfPtr,"%d,",bestSum);
  n = bestNum - 1;
  i++;
 }
 fclose(cfPtr);
 printf("%d\n",i); //反素数的个数
 return 0;


}
//*/
 

/* 线段树

#include<stdio.h>
#include<math.h>

struct aNode{
	int l,r;
	int n;
};

aNode node[2000000];
char name[500001][12];
int num[500001];
int p[500001];


void makeTree(int k,int l,int r)
{
	node[k].l = l;
	node[k].r = r;
	node[k].n = r-l+1;
	if(l==r)
		return;
	int mid = (l+r)/2;
	makeTree(2*k,l,mid);
	makeTree(2*k+1,mid+1,r);
}


int query(int k,int n)   //查询当前第n个数的号码
{
	if(node[k].l == node[k].r)
		return node[k].l;
	if(n<=node[2*k].n)
		return query(2*k,n);
	else
		return query(2*k+1,n-node[2*k].n);
}

void deleteNum(int k,int n)   //删去号为n的数
{
	node[k].n--;
	if(node[k].l == node[k].r)
		return;
	int mid = (node[k].l + node[k].r)/2;
	if(n<=mid)
		deleteNum(2*k,n);
	else
		deleteNum(2*k+1,n);
}


int main()
{
	int n,k;
	int i;
	int no;
	int t;
	int x;
	int p;

       //打表出来的反素数
	int max[35][2] = {498960,200,332640,192,277200,180,221760,168,166320,160,110880,144,83160,128,55440,120,50400,108,45360,100,27720,96,25200,90,20160,84,15120,80,10080,72,7560,64,5040,60,2520,48,1680,40,1260,36,840,32,720,30,360,24,240,20,180,18,120,16,60,12,48,10,36,9,24,8,12,6,6,4,4,3,2,2,1,1};
	while(scanf("%d%d",&n,&k)!=EOF)
	{
		p = 0;
		while(n<max[p][0])
			p++;
		x = max[p][0];   //x为小于等于n的最大反素数
		makeTree(1,0,n-1);
		for(i=0;i<n;i++)
		{
			scanf("%s",name[i]);
			scanf("%d",&num[i]);
		}
		i=1;
		t = n;
		no=k;    //号为k，在剩下数中排第no个
		k--;
		while(i<x)    //算到第x个人后即可
		{
 			n--;
			if(n>0)
			{
				deleteNum(1,k);   //删除号为k的数
				//推算出no值（在剩下人中的排号）

                                no+=num[k];
				if(num[k]>0)
					no--;
				no = (no%n+n)%n;
				if(no==0)
					no+=n;
				k=query(1,no);	//求原来的序号
				i++;
			}
		}
		printf("%s %d\n",name[k],max[p][1]);

	}
	return 0;
}
//*/








/*     反质数表
    #include<iostream>  
    using namespace std;  
    #define MAXN 500002  
    struct Person{  
           char name[12];  
           int step;  
    }person[MAXN];  
    int rprime[]={1,2,4,6,12,24,36,48,60,120,180,240,360,720,840,1260,1680,2520,5040,7560,10080,15120,20160,25200,27720,45360,50400,55440,83160,110880,166320,221760,277200,332640,498960};  
    int nprime[]={1,2,3,4,6,8,9,10,12,16,18,20,24,30,32,36,40,48,60,64,72,80,84,90,96,100,108,120,128,144,160,168,180,192,200};  
    int binarySearch(int target){  
        int low=0,high=34,mid;  
        while(low<=high){  
           mid=(low+high)>>1;  
           if(rprime[mid]==target) return mid;  
           if(target>rprime[mid]) low=mid+1;  
           else high=mid-1;  
        }  
        return high;  
    }  
    struct SegmentTree{  
           int left[MAXN*4],right[MAXN*4];  
           int sum[MAXN*4];  
             
           inline void build(int k,int l,int r){  
                 left[k]=l;  
                 right[k]=r;  
                 sum[k]=1;  
                 if(l==r) return ;  
                 int m=(l+r)>>1;  
                 build(k*2,l,m);  
                 build(k*2+1,m+1,r);  
                 push_up(k);  
           }  
             
           inline void push_down(int k){  
                 return ;  
           }  
             
           inline void push_up(int k){  
                 if(left[k]!=right[k])  
                   sum[k]=sum[k*2]+sum[k*2+1];  
           }  
             
           inline int update(int k,int n){  
                 if(left[k]==right[k]){  
                     sum[k]=0;  
                     return left[k];  
                 }  
                 else{  
                     int tmp=sum[k*2];  
                     int ret;  
                     if(tmp>=n)  
                       ret=update(k*2,n);  
                     else  
                       ret=update(k*2+1,n-tmp);  
                     push_up(k);  
                     return ret;  
                 }  
           }  
             
           inline void run(int m,int k){  
                  int i;  
                  int total=sum[1];  
                  k--;  
                  int ind;  
                  for(i=0;i<rprime[m];i++){  
                      if(k<0)  
                        k=k+(-k)/total*total;  
                      k=(k+total)%total;  
                      k++;  
                      ind=update(1,k);  
                      total--;  
                      k=(k-1)+person[ind].step;  
                      if(person[ind].step>0)  
                        k--;  
                  }  
                  printf("%s %d/n",person[ind].name,nprime[m]);  
           }  
             
    }sgt;  
    int main()  
    {  
        int n,k;  
        while(scanf("%d%d",&n,&k)!=EOF){  
            int i;  
            for(i=0;i<n;i++)  
              scanf("%s%d",person[i].name,&person[i].step);
            int m=binarySearch(n);  
            sgt.build(1,0,n-1);  
            sgt.run(m,k);  
        }  
    }  
//*/



/*    线段树  14044K	1110MS	C++	1766B
#include <cstdio>
#include <cmath>
#include <algorithm>
 
using namespace std;

#define REP(i,n) for(i=0;i<(n);++i)
#define FOR(i,l,h) for(i=(l);i<=(h);++i)
#define FORD(i,h,l) for(i=(h);i>=(l);--i)
 
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1 | 1
 
#define N 500010
 
int tree[N<<2];

// 反质数表
const int antiprime[]={1,2,4,6,12,24,36,48,60,120,180,240,360,720,840,1260,1680,2520,5040,7560,10080,15120,20160,25200,27720,
45360,50400,55440,83160,110880,166320,221760,277200,332640,498960,554400,665280};
// 约数个数
const int factorNum[]={1,2,3,4,6,8,9,10,12,16,18,20,24,30,32,36,40,48,60,64,72,80,84,90,96,100,108,120,128,144,160,168,180,192,200,216,224};

struct child
{
    char name[15];
    int val;
}c[N];

void build(int l,int r,int rt)        // 这种设计可能会更好
{
    tree[rt]=r-l+1;
    if(l==r)    return;
    int m=(l+r)>>1;
    build(lson);
    build(rson);
}

int update(int p,int l,int r,int rt)
{
    tree[rt]--;
    if(l==r)    return l;
    int m=(l+r)>>1;
    if(p<=tree[rt<<1]) return update(p,lson);
    return update(p-tree[rt<<1],rson);
}

int main(void)
{
    int n,k,&mod=tree[1];
	int i;
    while(scanf("%d%d",&n,&k)==2)
    {
        FOR(i,1,n)
			scanf("%s%d",c[i].name,&c[i].val);
        build(1,n,1);

		//  只要知道n，就可以求出n的反质数多大
        int cnt=0;
        while(cnt<35 && antiprime[cnt]<=n)    cnt++;
		
        cnt--;
		printf("%d\n", cnt);
        int pos=0;
        c[pos].val=0;

		// 这里只为求name
        REP(i,antiprime[cnt])    // 第cnt个就是
        {
            if(c[pos].val>0)
				k=((k+c[pos].val-2)%mod+mod)%mod+1;
            else    
				k=((k+c[pos].val-1)%mod+mod)%mod+1;
            pos=update(k,1,n,1);
        }

        printf("%s %d\n",c[pos].name,factorNum[cnt]);
    }
    return 0;
}
//*/