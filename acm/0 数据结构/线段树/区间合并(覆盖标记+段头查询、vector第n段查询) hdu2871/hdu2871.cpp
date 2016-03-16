/*         218MS	1488K	3481 B	C++
#include<stdio.h>
#include<string.h>

#define max(a,b) a>b?a:b

int ch[51000][2],num[51000],Max[51000],fa[51000],root,end[51000],N;
bool is[51000];

inline void flow(int n)
{
    num[n]=num[ch[n][0]]+num[ch[n][1]]+is[n];
    Max[n]=max(Max[ch[n][0]],Max[ch[n][1]]);
    if(!is[n])
        Max[n]=max(end[n]-n+1,Max[n]);
}

inline void rotate(int n) 
{
    int t=fa[n],d=(ch[t][1]==n);
    ch[t][d]=ch[n][!d],fa[ch[n][!d]]=t;
    ch[n][!d]=t,fa[n]=fa[t],ch[fa[t]][ch[fa[t]][1]==t]=n,fa[t]=n;
    flow(t),flow(n);
}

void splay(int n,int goal)
{
    int f,ff;
    while(fa[n]-goal)
    {
        f=fa[n],ff=fa[f];
        if(ff==goal)
            rotate(n);
        else if((ch[ff][0]==f)==(ch[f][0]==n))
            rotate(f),rotate(n);
        else
            rotate(n),rotate(n);
    }
    if(goal==0)
        root=n;
}

int New(int l)
{
    int t=root;
    while(1)
    {
        if(Max[ch[t][0]]>=l)
            t=ch[t][0];
        else if(!is[t]&&end[t]-t+1>=l)
            break;
        else
            t=ch[t][1];
    }
    splay(t,0);
    is[t]=1;
    if(l+t-1<end[t])
    {
        ch[l+t][0]=0,ch[l+t][1]=ch[t][1],fa[ch[t][1]]=l+t;
        ch[t][1]=l+t,fa[l+t]=t;is[l+t]=0;end[l+t]=end[t];
        flow(l+t);
        end[t]=l+t-1;
    }
    flow(t);
    return t;
}

void search(int pos,int goal)  
{
    int t=root;
    while(1)
    {
        if(pos<t)
            t=ch[t][0];
        else if(pos>end[t])
            t=ch[t][1];
        else
            break;
    }
    splay(t,goal);
}

void Free(int pos)
{
    search(pos,0);
    if(!is[root])
    {
        printf("Reject Free\n");
        return ;
    }
    printf("Free from %d to %d\n",root,end[root]);
    if(root>1)
    {
        search(root-1,root);
        if(!is[ch[root][0]])
            root=ch[root][0],end[root]=end[fa[root]],ch[root][1]=ch[fa[root]][1],fa[ch[root][1]]=root;
    }
    if(end[root]<N)
    {
        search(end[root]+1,root);
        if(!is[ch[root][1]])
            end[root]=end[ch[root][1]],ch[root][1]=ch[ch[root][1]][1],fa[ch[root][1]]=root;
    }
    is[root]=0;fa[root]=0;
    flow(root);
}

inline void getk(int k)   
{
    int t=root;
    while(1)
    {
        if(num[ch[t][0]]>=k)
            t=ch[t][0];
        else if(num[ch[t][0]]==k-1&&is[t])
            break;
        else
            k-=num[ch[t][0]]+is[t],t=ch[t][1];
    }
    splay(t,0);
}

int main()
{
    int k,i,j;
    char s[10];
    while(scanf("%d%d",&N,&j)!=EOF)
    {
        is[1]=0,num[1]=0,ch[1][0]=ch[1][1]=0,fa[1]=0;
        root=1,end[1]=N,Max[1]=N;
        while(j--)
        {
            scanf("%s",s);
            if(s[0]-'R')
                scanf("%d",&k);
            if(s[0]=='N')
            {
                if(Max[root]>=k)
                    printf("New at %d\n",New(k));
                else
                    printf("Reject New\n");
            }
            else if(s[0]=='F')
                Free(k);
            else if(s[0]=='G')
            {
                if(num[root]<k)
                    printf("Reject Get\n");
                else
                    getk(k),printf("Get at %d\n",root);
            }
            else
            {
                is[1]=0,num[1]=0,ch[1][0]=ch[1][1]=0,fa[1]=0;
                root=1,end[1]=N,Max[1]=N;
                printf("Reset Now\n");
            }
        }
        printf("\n");
    }
}
//*/







/*         375MS	4368K	4811 B	
#include<cstdio>
 #include<cstring>
 #include<algorithm>
 using namespace std;
#define max(a,b) a>b?a:b
 #define MAXN 50010
 struct node
 {
     int left,right,sum,lazy,s,e,cnt,cover;
 };
 node tree[MAXN<<2];
 inline void PushUp(int mid,int L,int R,int rt)
 {
     tree[rt].left=tree[rt<<1].left;
     tree[rt].right=tree[rt<<1|1].right;
     if(tree[rt].left==mid-L+1)
         tree[rt].left+=tree[rt<<1|1].left;
     if(tree[rt].right==R-mid)
         tree[rt].right+=tree[rt<<1].right;
     tree[rt].sum=max(tree[rt<<1].sum,tree[rt<<1|1].sum);
     tree[rt].sum=max(tree[rt].sum,tree[rt<<1].right+tree[rt<<1|1].left);
 }
 inline void PushDown(int mid,int L,int R,int rt)
 {
     if(tree[rt].lazy!=-1)
     {
         tree[rt<<1].lazy=tree[rt<<1|1].lazy=tree[rt].lazy;
         tree[rt<<1].sum=tree[rt<<1].left=tree[rt<<1].right=(mid-L+1)*tree[rt].lazy;
         tree[rt<<1|1].sum=tree[rt<<1|1].left=tree[rt<<1|1].right=(R-mid)*tree[rt].lazy;
         tree[rt<<1].s=tree[rt<<1|1].s=tree[rt].s;
         tree[rt<<1].e=tree[rt<<1|1].e=tree[rt].e;
         tree[rt].lazy=-1;
     }
 }
 void Update(int x,int y,int val,int L,int R,int rt)
 {
     if(x<=L&&R<=y)
     {
         tree[rt].lazy=val;
         tree[rt].sum=tree[rt].left=tree[rt].right=val*(R-L+1);
         if(val)
             tree[rt].s=tree[rt].e=-1;
         else
         {
             tree[rt].s=x;
             tree[rt].e=y;
         }
     }
     else
     {
         int mid=(L+R)>>1;
         PushDown(mid,L,R,rt);
         if(x<=mid)
             Update(x,y,val,L,mid,rt<<1);
         if(y>mid)
             Update(x,y,val,mid+1,R,rt<<1|1);
         PushUp(mid,L,R,rt);
     }
 }
 int New(int x,int L,int R,int rt)
 {
     if(L==R)
         return L;
     int mid=(L+R)>>1;
     PushDown(mid,L,R,rt);
     if(tree[rt<<1].sum>=x)
         return New(x,L,mid,rt<<1);
     else if(tree[rt<<1].right+tree[rt<<1|1].left>=x)
         return mid-tree[rt<<1].right+1;
     else
         return New(x,mid+1,R,rt<<1|1);
 }
 int Free(int x,int L,int R,int rt)
 {
     if(L==R)
         return rt;
     int mid=(L+R)>>1;
     PushDown(mid,L,R,rt);
     if(x<=mid)
         return Free(x,L,mid,rt<<1);
     else
         return Free(x,mid+1,R,rt<<1|1);
 }
 inline void CountUp(int rt)
 {
     tree[rt].cnt=tree[rt<<1].cnt+tree[rt<<1|1].cnt;
 }
 inline void CountDown(int rt)
 {
     if(tree[rt].cover)
     {
         tree[rt<<1].cnt=tree[rt<<1|1].cnt=0;
         tree[rt<<1].cover=tree[rt<<1|1].cover=1;
         tree[rt].cover=0;
     }
 }
 int Get(int x,int L,int R,int rt)
 {
     if(L==R)
         return L;
     else
     {
         int mid=(L+R)>>1;
         CountDown(rt);
         if(tree[rt<<1].cnt>=x)
             return Get(x,L,mid,rt<<1);
         else
             return Get(x-tree[rt<<1].cnt,mid+1,R,rt<<1|1);
     }
 }
 void Count(int x,int val,int L,int R,int rt)
 {
     if(L==R)
         tree[rt].cnt=val;
     else
     {
         int mid=(L+R)>>1;
         CountDown(rt);
         if(x<=mid)
             Count(x,val,L,mid,rt<<1);
         else
             Count(x,val,mid+1,R,rt<<1|1);
         CountUp(rt);
     }
 }
 inline void Reset(int n)
 {
     Update(1,n,1,1,n,1);
     tree[1].cover=1;
     tree[1].cnt=0;
 }
 int main()
 {
	 freopen("in1.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
     char s[12];
     int n,m,x,y;
     while(~scanf("%d%d",&n,&m))
     {
         Reset(n);
         while(m--)
         {
             scanf(" %s",s);
             if(!strcmp(s,"Reset"))
             {
                 Reset(n);
                 puts("Reset Now");
             }
             else if(!strcmp(s,"New"))
             {
                 scanf("%d",&x);
                 if(tree[1].sum>=x)
                 {
                     y=New(x,1,n,1);
                     printf("New at %d\n",y);
                     Count(y,1,1,n,1);
                     Update(y,y+x-1,0,1,n,1);
                 }
                 else
                     puts("Reject New");
             }
             else if(!strcmp(s,"Free"))
             {
                 scanf("%d",&x);
                 y=Free(x,1,n,1);
                 if(tree[y].s<0)
                     puts("Reject Free");
                 else
                 {
                     printf("Free from %d to %d\n",tree[y].s,tree[y].e);
                     Count(tree[y].s,0,1,n,1);
                     Update(tree[y].s,tree[y].e,1,1,n,1);
                 }
             }
             else
             {
                 scanf("%d",&x);
                 if(x>tree[1].cnt)
                     puts("Reject Get");
                 else
                     printf("Get at %d\n",Get(x,1,n,1));
             }
         }
         putchar('\n');
     }
     return 0;
 }
//*/







/*    328MS	   2624K	3209 B	C++

#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int maxn = 55555;
int lsum[maxn<<2],rsum[maxn<<2],msum[maxn<<2],cover[maxn<<2];
struct node {
    int l,r;
    bool operator < (const node &cmp) const {
        return l<cmp.l;
    }
}tno;
vector<node> mem;
void pushup(int rt,int m){
    lsum[rt]=lsum[rt<<1];
    rsum[rt]=rsum[rt<<1|1];
    if(lsum[rt] == m-(m>>1)) lsum[rt]+=lsum[rt<<1|1];
    if(rsum[rt] == (m>>1)) rsum[rt]+=rsum[rt<<1];
    msum[rt]=max(lsum[rt<<1|1]+rsum[rt<<1],max(msum[rt<<1],msum[rt<<1|1]));
}
void pushdown(int rt ,int m){
    if(cover[rt]!=-1){
        cover[rt<<1]=cover[rt<<1|1]=cover[rt];
        msum[rt<<1]=lsum[rt<<1]=rsum[rt<<1]=cover[rt] ? 0 :m-(m>>1);
        msum[rt<<1|1]=lsum[rt<<1|1]=rsum[rt<<1|1]=cover[rt] ? 0 : (m>>1);
        cover[rt]=-1;
    }
}
void build(int l,int r,int rt){
    msum[rt]=lsum[rt]=rsum[rt]=r-l+1;
    cover[rt]=-1;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(lson);
    build(rson);
}
void update(int L,int R,int c,int l,int r,int rt){
    if(L<=l&&r<=R){
        msum[rt]=lsum[rt]=rsum[rt]= c ? 0 : r-l+1;
        cover[rt]=c;
        return ;
    }
    pushdown(rt,r-l+1);
    int m=(l+r)>>1;
    if(L <= m) update(L,R,c,lson);
    if(R > m) update(L,R,c,rson);
    pushup(rt,r-l+1);
}
int query(int w,int l,int r,int rt){
    if(l==r) return l;
    pushdown(rt,r-l+1);
    int m=(l+r)>>1;
    if(msum[rt<<1]>=w) return query(w,lson);
    else if(rsum[rt<<1]+lsum[rt<<1|1]>=w) return m-rsum[rt<<1]+1;
    return query(w,rson);
}
int main(){
    int n,m,i,j,k,a,b,c,pos;
    char str[10];
    vector<node> :: iterator it;
    while(~scanf("%d%d",&n,&m)){
        build(1,n,1);
        mem.clear();
        while(m--){
            scanf("%s",str);
            if(str[0]=='N'){    
                scanf("%d",&a);
                if(msum[1]<a) puts("Reject New");
                else {
                    b=query(a,1,n,1);
                    update(b,b+a-1,1,1,n,1);
                    tno.l=b;tno.r=b+a-1;
                    it=upper_bound(mem.begin(),mem.end(),tno);
                    mem.insert(it,tno);
                    printf("New at %d\n",b);
                }
            }
            else if(str[0]=='F'){
                scanf("%d",&a);
                tno.l=a;tno.r=a;
                pos=upper_bound(mem.begin(),mem.end(),tno)-mem.begin()-1;
                if(pos==-1||mem[pos].r<a) puts("Reject Free");
                else {
                    printf("Free from %d to %d\n",mem[pos].l,mem[pos].r);
                    update(mem[pos].l,mem[pos].r,0,1,n,1);
                    mem.erase(mem.begin()+pos);
                }
            }
            else if(str[0]=='G'){
                scanf("%d",&a);
                if(a>mem.size()) puts("Reject Get");
                else     printf("Get at %d\n",mem[a-1].l);
            }
            else if(str[0]=='R'){
                update(1,n,0,1,n,1);
                puts("Reset Now");
                mem.clear();
            }
        }
      puts("");
    }
    return 0;
}
//*/





//* 
//     359MS	2620K	3023 B	C++
//     328MS	2620K	2987 B	C++
#include<iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define max(a,b) a>b?a:b

const int N = 51111;    // 50010也可以
int n, m;
int cover[N<<2];
int msum[N<<2], lsum[N<<2], rsum[N<<2];  // 0的个数

struct node{
	int s, e;
	bool operator < (const node &a) const {
		return s<a.s;
	}
};
vector<node> vec;

void init(){
	cover[1] = 0;
	msum[1] = lsum[1] = rsum[1] = n;
	vec.clear();
}

void pushdown(int rt, int m){
	if(cover[rt]!=-1){
		cover[rt<<1] = cover[rt<<1|1] = cover[rt];
		msum[rt<<1] = lsum[rt<<1] = rsum[rt<<1] = cover[rt]?0:m-(m>>1);
		msum[rt<<1|1] = lsum[rt<<1|1] = rsum[rt<<1|1] = cover[rt]?0:(m>>1);
		cover[rt] = -1;
	}
}

void pushup(int rt, int m){
	if(cover[rt<<1]==cover[rt<<1|1])
		cover[rt] = cover[rt<<1];
	else
		cover[rt] = -1;
	lsum[rt] = lsum[rt<<1];
	rsum[rt] = rsum[rt<<1|1];
	msum[rt] = max(msum[rt<<1], msum[rt<<1|1]);
	if(lsum[rt]==m-(m>>1))   lsum[rt] += lsum[rt<<1|1];
	if(rsum[rt]==(m>>1))     rsum[rt] += rsum[rt<<1];
	msum[rt] = max(msum[rt], rsum[rt<<1]+lsum[rt<<1|1]);
}

void update(int L, int R, int p, int l, int r, int rt){
	if(L<=l && r<=R){
		cover[rt] = p;
		msum[rt] = lsum[rt] = rsum[rt] = p?0:(r-l+1);
		return ;
	}
	pushdown(rt, r-l+1);
	int m = (l + r) >> 1;
	if(L<=m)   update(L, R, p, lson);
	if(m<R)   update(L, R, p, rson);
	pushup(rt, r-l+1);
}

int query(int p, int l, int r, int rt){
	if(l==r)  return l;                    //  少了这句，runtime error左无数次
	pushdown(rt, r-l+1);
	int m = (l + r) >> 1;
	if(msum[rt<<1]>=p)
		return query(p, lson);
	else if(rsum[rt<<1]+lsum[rt<<1|1]>=p)
		return m - rsum[rt<<1] + 1;
	else 
		return query(p, rson);
}

int main(){
	freopen("in1.txt", "r", stdin);
	freopen("out1.txt", "w", stdout);
	int i;
	char op[10];
	int a, b;
	node no; 
	vector<node>::iterator it;

	while(~scanf("%d %d", &n, &m)){
		init();
		for(i=0; i<m; i++){
			scanf("\n%s", op);
			if(op[0]=='N'){
				scanf("%d", &a);
				if(msum[1]>=a){
					b = query(a, 1, n, 1);
					no.s = b;  no.e = a+b-1;
                    it=upper_bound(vec.begin(),vec.end(),no);
                    vec.insert(it,no);         // 插入某位置
					update(b, a+b-1, 1, 1, n, 1);
					printf("New at %d\n", b);
				}
				else 
					printf("Reject New\n");
			}
			else if(op[0]=='F'){
				scanf("%d", &a);
				no.s = a; no.e = a;
				int num = upper_bound(vec.begin(), vec.end(), no)-vec.begin()-1;
				if(num==-1 || vec[num].e<a)
					printf("Reject Free\n");
				else{
					update(vec[num].s, vec[num].e, 0, 1, n, 1);
					printf("Free from %d to %d\n", vec[num].s, vec[num].e);
					vec.erase(vec.begin()+num);
				}
			}
			else if(op[0]=='G'){
				scanf("%d", &a);
				if(vec.size()>=a){
					printf("Get at %d\n", vec[a-1].s);
				}
				else{
					printf("Reject Get\n");
				}
			}
			else {
				update(1, n, 0, 1, n, 1);
				vec.clear();
				printf("Reset Now\n");
			}
		}
		printf("\n");
	}

	return 0;
}
//*/