/*  从最大可能的串开始遍历。
#include<iostream>

using namespace std;

int main()
{
	

	return 0;
}

//*/


//*        1108K	47MS	C++	3342B
#include <stdio.h>
#include <algorithm>
#include <string>
using namespace std;
const int N = 20005;

struct node{
	int f, s;
	int pos;
	node(int f = 0, int s = 0, int pos = 0){
	   this->set(f, s, pos);
	}
	void set(int f, int s, int pos){
	   this->f = f;
	   this->s = s;
	   this->pos = pos;
	}
	bool operator==(node n){
	   return this->f == n.f && this->s == n.s;
	}
	bool operator!=(node n){
	   return !((*this) == n);
	}
}nodes[N];

struct e{
	node y;
	int next;
}edges[N];

int str[N];
int n;
int rank[N], sa[N], first[N], h[N];

bool cmp1(node n1, node n2){
	return n1.f < n2.f;
}

bool compu_rank(){
	int p = 1, i;
	bool flag = false;
	rank[nodes[0].pos] = 1;
	for(i = 1; i < n; i++){
	   if(nodes[i] != nodes[i - 1]) p++;
	   else flag = true; //表示还有rank相同的串
	   rank[nodes[i].pos] = p;
	}
	return flag;
}

void radix_sort(){
	//对第一个关键字排序
	int i, e, tot, cur;
	e = 0;
	for(i = 0; i <= n; i++) first[i] = -1;
	for(i = 0; i < n; i++){
	   edges[e].y = nodes[i];
	   edges[e].next = first[nodes[i].s];
	   first[nodes[i].s] = e;
	   e++;
	}
	tot = 0;
	for(i = 0; i < n; i++){
	   cur = first[i];
	   while(cur != -1){
		nodes[tot++] = edges[cur].y;
		cur = edges[cur].next;
	   }
	}
	e = 0;
	for(i = 0; i <= n; i++) first[i] = -1;
	for(i = n - 1; i >= 0; i--){ //这里要从大到小循环
	   edges[e].y = nodes[i];
	   edges[e].next = first[nodes[i].f];
	   first[nodes[i].f] = e;
	   e++;
	}
	tot = 0;
	for(i = 0; i < n; i++){
	   cur = first[i];
	   while(cur != -1){
		nodes[tot++] = edges[cur].y;
		cur = edges[cur].next;
	   }
	}
}

void compu_sa(){
	int i, j = 1;
	bool flag;
	for(i = 0; i < n; i++) nodes[i].set(str[i], 0, i);
	sort(nodes, nodes + n, cmp1);
	flag = compu_rank();

	
	//for(i = 0; i < n; i++) printf("(%d, %d)\n", nodes[i].f, nodes[i].s);
	//printf("\n\n");
	

	while(flag && j < n){
	   for(i = 0; i < n; i++){
		nodes[i].set(rank[i], 0, i);
		if(i + j < n) nodes[i].s = rank[i + j];
	   }
	   radix_sort();
	   flag = compu_rank();
	   j *= 2;
	   
	   //for(i = 0; i < n; i++) printf("(%d, %d)\n", nodes[i].f, nodes[i].s);
	   //printf("\n\n");
	   
	}

	for(i = 0; i < n; i++) rank[i]--;
	for(i = 0; i < n; i++) sa[i] = nodes[i].pos;
	
	//for(i = 0; i < n; i++){
	//   printf(" sa[%d] = %d\n", i, sa[i]);
	//   for(int j = sa[i]; j < n; j++) printf("%d", str[j]);
	//   printf("\n");
	//}
}

void compu_h(){
	h[0] = 0;
	int i, k = 0, s;
	for(i = 0; i < n; i++){
	   if(rank[i] == 0){
			h[0] = k = 0;
	   }
	   else{
			if(k > 0) k--;
			s = sa[rank[i] - 1];
			while(i + k < n && s + k < n && str[i + k] == str[s + k]) k++;
			h[rank[i]] = k;
	   }
	}
	//for(i = 0; i < n; i++) printf("h[%d] = %d\n", i, h[i]);
}

bool check(int len, int k){ //如何对后缀分组呢？？？
	int i, g = 1;
	for(i = 0; i < n; i++){ //这里利用了前缀相同的，是连在一起的这一样直观特性
	   if(h[i] >= len){
			g++;
			if(g >= k) return true;
	   }
	   else{
			g = 1;
	   }
	}
	return false;
}


int main(){
	int i, k, mid, l, r;
	while(scanf("%d%d", &n, &k)){
	   for(i = 0; i < n; i++) scanf("%d", &str[i]);
	   compu_sa();   // 计算后缀数组
	   compu_h();    // 计算
	   l = 1, r = n;
	   while(l <= r){
			mid = (l + r) >> 1;
			if(check(mid, k)) l = mid + 1;
			else r = mid - 1;
	   }
	   printf("%d\n", l - 1);
	   break;
	}
	return 0;
}

//*/




//*     4600K	141MS	C++	2357B
#include <iostream>
#include <stdio.h>
using namespace std;

const int N=1000005;
int m[N],sa[N],rank[N],height[N],wa[N],wb[N],cnt[1000010];
int k;

int cmp(int *x,int a,int b,int l)
{
    return ((x[a]==x[b]) && (x[a+l]==x[b+l]));
}

void suffix(int *s,int len)   // 串s， 总长度len(包括新加的1)
{
    int *x=wa,*y=wb,*t;
    int i,j,p,n,k;
    n=len;
    for(i=0;i<n;i++)
    {
        rank[i]=0;
        height[i]=0;
        sa[i]=0;
    }
    int mm=1000003;
    for(i=0;i<mm;i++)
        cnt[i]=0;            
    for(i=0;i<n;i++)
        cnt[x[i]=s[i]]++;     // 计算每一种字符出现的次数。(包括那个1)
    for(i=1;i<mm;i++)
        cnt[i]=cnt[i]+cnt[i-1];  // 本来这里有点浪费 有许多地方都为0，相加之后就不一样了。
    for(i=n-1;i>=0;i--)
        sa[--cnt[x[i]]]=i;       // 单个字符的后缀第一次排序(下标为次序)。         如果 这里是sa[--cnt[x[i]]]=x[i];的话，就是基数排序了。
	
	//for(i=0; i<9; i++)
	//	cout << sa[i] << " "; 
	//cout << endl;
   
    for(j=1,p=1;  p<n;  mm=p,j*=2)
    {
        for(p=0,i=n-j;i<n;i++)
            y[p++]=i;
        for(i=0;i<n;i++)
            if(sa[i]>=j)  y[p++]=sa[i]-j;

		//for(i=0; i<p; i++)
		//	cout << y[i] << " ";
		//cout << endl;

		// 下面有来一次基数排序//////    x[]始终都是原来的字符串。
        for(i=0;i<mm;i++)
            cnt[i]=0;
        for(i=0;i<n;i++)
            cnt[x[y[i]]]++;
        for(i=1;i<mm;i++)
            cnt[i]=cnt[i]+cnt[i-1];
        for(i=n-1;i>=0;i--)
            sa[--cnt[x[y[i]]]]=y[i];
		/////////////////////////////
		
		// 交换 x 与 y 数组
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i],sa[i-1],j)?p-1:p++;
    }

	// 下面是 rank[] 数组
    for(i=0;i<n;i++)
        rank[sa[i]]=i;

	// 下面是 height[] 数组
    k=0;
    for(i=0;i<n;i++)
    {
        if(0==rank[i])
            height[rank[i]]=k=0;
        else
        {
            if(k>0)
                k--;               // height[j] >= height[i] - 1;
            j=sa[rank[i]-1];
            while(s[i+k]==s[j+k])  // i是后一名，j是前一名
                k++;
            height[rank[i]]=k;
        }
    }
//     for(i=0;i<n;i++)
//         cout<<height[i]<<" ";
//     cout<<endl;
}
bool isExsit(int n,int len)
{
    int cnt=0;
    for(int i=1;i<n;i++)
    {
        if(height[i]>=len)
        {
            cnt++;
            if(cnt>=k-1)
                return true;
        }
        else
        {
            cnt=0;
        }
    }
    return false;
}
int main()
{
    int i,j,n,mid;
    scanf("%d%d",&n,&k);
    for(i=0;i<n;i++)
    {
        scanf("%d",&m[i]);
        m[i]=m[i]+2;
    }
    m[i]=1;
    n++;   //忘了++了
    suffix(m,n);

	for(i=0; i<n; i++)
		cout << height[i] << " ";
	cout << endl;

    i=0;
    j=n;
    while(i<=j)
    {
        mid=(i+j)/2;
        if(isExsit(n,mid))
        {
            i=mid+1;
        }
        else
            j=mid-1;
    }
    printf("%d\n",j);
    return 0;
}

//*/




