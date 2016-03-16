//*    343MS	1812K	1971 B	C++
//     312MS	1812K	1877 B	C++
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define max(a, b) a>b?a:b

const int N = 51111;
int msum[N<<2], lsum[N<<2], rsum[N<<2];
int st[N];
int p = 0;

void pushup(int rt, int m){
	lsum[rt] = lsum[rt<<1]==m-(m>>1)?(lsum[rt<<1]+lsum[rt<<1|1]):lsum[rt<<1];
	rsum[rt] = rsum[rt<<1|1]==(m>>1)?(rsum[rt<<1|1]+rsum[rt<<1]):rsum[rt<<1|1];
	msum[rt] = max(msum[rt<<1], msum[rt<<1|1]);
	msum[rt] = max(msum[rt], rsum[rt<<1]+lsum[rt<<1|1] );
}

void build(int l, int r, int rt){
	msum[rt] = lsum[rt] = rsum[rt] = r - l + 1;
	if(l==r)   return ;
	int m = (l + r) >> 1 ;
	build(lson);
	build(rson);
}

void update(int a, int p, int l, int r, int rt){
	if(l==r){
		msum[rt] = lsum[rt] = rsum[rt] = p;
		return ;
	}
	int m = (l + r) >> 1;
	if(a<=m)   update(a, p, lson);
	else   update(a, p, rson);
	pushup(rt, r-l+1);
}

int query(int a, int l, int r, int rt){
	if(msum[rt]==r-l+1 || l==r || msum[rt]==0)
		return msum[rt];
	int m = (l + r) >> 1;
	int ans = 0;
	if(a<=m){
		ans = query(a, lson);
		if(a>m-rsum[rt<<1])
			ans += lsum[rt<<1|1]; 
	}
	else{
		ans = query(a, rson);
		if(a<=m+lsum[rt<<1|1])
			ans += rsum[rt<<1];     
	}
	return ans;
}

int main()
{
	int n, m;
	int i, t;
	char ch[5];
	
	while(scanf("%d %d", &n, &m)!=EOF){
		build(1, n, 1);
		p = 0;
		for(i=0; i<m; i++){
			scanf("\n%s", &ch);
			if(ch[0]=='D'){
				scanf("%d", &t);
				st[++p] = t;
				update(t, 0, 1, n, 1);
			}
			else if(ch[0]=='Q'){
				scanf("%d", &t);
				printf("%d\n", query(t, 1, n, 1));
			}
			else{
				update(st[p], 1, 1, n, 1);
				p--;
			}
		}
	}

	return 0;
}
//*/






/*    343MS	3016K	2597 B	C++

#include<stdio.h>
struct haha{
	 int left;
	 int right;
	 int l_1;//从左边开始的1的连续长度
	 int r_1;//从右边开始的1的连续长度
	 int max_1;//最大的连续1的长度
}node[50000*4];

int max(int x,int y){
	 if(x>y) return x;
	 else return y;
}
void build(int left,int right,int nd){
	 int mid;
	 node[nd].left=left;
	 node[nd].right=right;
	 node[nd].max_1=node[nd].l_1=node[nd].r_1=right-left+1;
	 if(left==right)
	   return;
	 mid=(left+right)/2;
	 build(left,mid,nd*2);
	 build(mid+1,right,nd*2+1);
}

void update(int pos,int flag,int nd){
	 int mid, l_len, r_len;
	 if(node[nd].left==pos&&node[nd].right==pos){
		  if(flag)
			  node[nd].l_1=node[nd].r_1=node[nd].max_1=1;
		  else 
			  node[nd].l_1=node[nd].r_1=node[nd].max_1=0;
			 return;
	 }
	 
	 mid=(node[nd].left+node[nd].right)/2;
	 if(pos<=mid) update(pos,flag,nd*2);
	 else if(pos>mid) update(pos,flag,nd*2+1);

     // pushup
	 l_len=node[nd*2].right-node[nd*2].left+1;
	 r_len=node[nd*2+1].right-node[nd*2+1].left+1;
	 node[nd].max_1=max((node[nd*2].r_1+node[nd*2+1].l_1),max(node[nd*2].max_1,node[nd*2+1].max_1));
	 node[nd].l_1=node[nd*2].l_1;
	 if(node[nd*2].l_1==l_len) node[nd].l_1+=node[nd*2+1].l_1;
	 node[nd].r_1=node[nd*2+1].r_1;
	 if(node[nd*2+1].r_1==r_len) node[nd].r_1+=node[nd*2].r_1;
}

int query(int pos,int nd){
	 int mid,len;
	 len  =  node[nd].right - node[nd].left + 1;
	 if(node[nd].left==node[nd].right || node[nd].max_1==0 || node[nd].max_1==len)     //node[nd].max_1==len 查找到某段都是连续的 就return
		return node[nd].max_1;

	 mid=(node[nd].left+node[nd].right)/2;
	 if(pos<=mid){
		  if(pos>mid-node[nd*2].r_1)
			  return query(pos, nd*2) + query(node[nd*2+1].left, nd*2+1);
		  else 
			  return query(pos, nd*2);
	 }
	 else if(pos>mid){
		  if(pos<node[nd*2+1].left+node[nd*2+1].l_1)
		   return query(pos,nd*2+1)+query(node[nd*2].right,nd*2);
		  else
			 return  query(pos,nd*2+1);
	 }
}
int main()
{
   int n,m,k,a[50000],pos,ans;
   char s[2];
   while(scanf("%d %d",&n,&m)!=EOF)
   {
		build(1,n,1);
		k=0;
		while(m--)
		{
			 scanf("%s",s);

			 if(s[0]=='D'){
				  scanf("%d",&pos);
				  a[k++]=pos;
				  update(pos,0,1);//如果是被破坏了 就修改值为0
			 }

			 else if(s[0]=='R'){
				 k--;
				 pos=a[k];
				 update(pos,1,1);//如果没有被破坏依然是1
			 }

			 else if(s[0]=='Q'){
				  scanf("%d",&pos);
				  ans = query(pos,1);
				  printf("%d\n",ans);
			  }
		}
   }
   return 0;
}
//*/