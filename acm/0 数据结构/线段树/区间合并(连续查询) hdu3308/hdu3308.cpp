//*    578MS	5420K	  2217 B	C++
#include<iostream>
#include<cstdio>

using namespace std;

#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

const int N = 100010;
int mmax[N<<2], lmax[N<<2], rmax[N<<2];
int lm[N<<2], rm[N<<2];

void pushup(int rt, int m){
	lmax[rt] = lmax[rt<<1];
	rmax[rt] = rmax[rt<<1|1];
	mmax[rt] = MAX(mmax[rt<<1], mmax[rt<<1|1]);
	lm[rt] = lm[rt<<1];   rm[rt] = rm[rt<<1|1];

	if(rm[rt<<1]<lm[rt<<1|1]){     // 合并的条件
		if( lmax[rt]==(m-(m>>1)) )   lmax[rt] += lmax[rt<<1|1];
		if( rmax[rt]==(m>>1) )    rmax[rt] += rmax[rt<<1];
		mmax[rt] = MAX(mmax[rt], rmax[rt<<1]+lmax[rt<<1|1]);
	}
}

void build(int l, int r, int rt){
	if(l==r){
		scanf("%d", &lm[rt]);
		//printf("%d  %d     ", l, lm[rt]);
		rm[rt] = lm[rt];
		mmax[rt] = lmax[rt] = rmax[rt] = 1;
		return; 
	}
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
	pushup(rt, r-l+1);
}

void update(int p, int add, int l, int r, int rt){
	if(l==r){
		lm[rt] = rm[rt] = add;
		return ;
	}
	int m = (l + r) >> 1;
	if(p<=m)   update(p, add, lson);
	else   update(p, add, rson);
	pushup(rt, r-l+1);
}

int query(int L, int R, int l, int r, int rt){
	if(L<=l && r<=R){
		return mmax[rt];
	}
	int m = (l + r) >> 1;
	if(R<=m){   
		return query(L, R, lson);
	}
	if(L>m){
		return query(L, R, rson);
	}
	int ans = MAX(query(L, m, lson), query(m+1, R, rson));
	//cout << "&" << l << " " << r << " " << rm[rt<<1] << " " << lm[rt<<1|1] << "&";
	if(rm[rt<<1]<lm[rt<<1|1]){
		//cout << "^" << rmax[rt<<1] << " " << lmax[rt<<1|1] << "^";
		ans = MAX(ans, MIN(m-L+1,rmax[rt<<1])+MIN(R-m,lmax[rt<<1|1]));    ///   令我错了无数次！！！！！！！！！
	}                  

	return ans;
}

int main()
{
	freopen("data.in", "r", stdin);    // 会引发这个错误的： Runtime Error  (STACK_OVERFLOW)
	int tc;
	int n, m;
	int i;
	int a, b;
	char ch;

	scanf("%d", &tc);
	while(tc--){
		scanf("%d %d", &n, &m);
		build(1, n, 1);
		for(i=0; i<m; i++){
			scanf("\n%c %d %d", &ch, &a, &b);
			if(ch=='Q'){
				printf("%d\n", query(a+1, b+1, 1, n, 1));
			}
			else{
				update(a+1, b, 1, n, 1);
			}
		}
	}

	return 0;
}
//*/





/*
#include<iostream>
using namespace std;

//经典的线段树，类似题目POJ 3667 2750 比较难的一个是hust 1235
//这题跑了250ms，暂时第一哈^_^ 

const int maxn=200005;

typedef struct node
{
    int l,r,flag;
    int lmax,rmax,mmax;    
}node;

node tree[4*maxn];
int n,m;
int a[maxn];
inline int min(int x,int y){return x<y?x:y;}
inline int max(int x,int y){return x>y?x:y;}     

void DP(int k){ 
    int mid=(tree[k].l+tree[k].r)>>1; 

    tree[k].lmax=tree[k*2].lmax;
    tree[k].rmax=tree[k*2+1].rmax;
    tree[k].mmax=max(tree[k*2].mmax,tree[k*2+1].mmax);

    if(a[mid]<a[mid+1]){
       if(tree[k*2].flag)tree[k].lmax+=tree[k*2+1].lmax;//左子树满 
       if(tree[k*2+1].flag)tree[k].rmax+=tree[k*2].rmax;//右子树满
       tree[k].mmax = max(tree[k].mmax, tree[k*2].rmax+tree[k*2+1].lmax);           
    }

    if(tree[k].mmax==tree[k].r-tree[k].l+1)tree[k].flag=1;
    else tree[k].flag=0;

//    test    
//    cout<<"l="<<tree[k].l<<" r="<<tree[k].r<<endl;
//    for(int i=tree[k].l;i<=tree[k].r;i++)cout<<a[i]<<" ";
//    cout<<endl; 
//    cout<<"lmax="<<tree[k].lmax<<" rmax="<<tree[k].rmax<<" mmax="<<tree[k].mmax<<endl;
//    cout<<"flag="<<tree[k].flag<<endl;system("pause");
}

void build(int k,int l,int r){
    tree[k].l=l;tree[k].r=r;
    tree[k].lmax=tree[k].rmax=tree[k].mmax=tree[k].flag=1;
    if(l<r){
       int mid=(l+r)>>1;
       build(k*2,l,mid);
       build(k*2+1,mid+1,r); 
       DP(k);   
    } 
}    

void update(int k,int i,int x){
    if(tree[k].l==tree[k].r){a[i]=x;return ;}
    int mid=(tree[k].l+tree[k].r)>>1;
    if(i<=mid)update(k*2,i,x);
    else update(k*2+1,i,x);
    DP(k);
}

int query(int k,int l,int r){
    if(tree[k].l==l&&tree[k].r==r)
		return tree[k].mmax;
    int mid=(tree[k].l+tree[k].r)>>1;

    if(r<=mid)
		return query(k*2,l,r);
    if(l>mid)
		return query(k*2+1,l,r);

    int mmax=max(query(k*2,l,mid), query(k*2+1,mid+1,r));
    if(a[mid]<a[mid+1])
		mmax=max(mmax,min(mid-l+1,tree[k*2].rmax)+min(r-mid,tree[k*2+1].lmax));                
    return mmax;    
}   
     
int main()
{
    freopen("data.in", "r", stdin);
    int i,j,k,test,x,y;
    char op[100];
    scanf("%d",&test);
    while(test--)
    {
          scanf("%d%d",&n,&m);   
          for(i=0;i<n;i++)scanf("%d",&a[i]);
          build(1,0,n-1);
          while(m--)
          {
                scanf("%s%d%d",op,&x,&y);
                if(op[0]=='U')update(1,x,y);
                else printf("%d\n",query(1,x,y));     
                }    
          }
    return 0;
    }
//*/