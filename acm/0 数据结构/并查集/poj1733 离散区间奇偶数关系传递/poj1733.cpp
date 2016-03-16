/*
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 5005;
int a[N], b[N];
char ch[N][5];
int mp[N*2];
int father[N*2], val[N*2];
int tmp;

int bs(int a){
	int s, e, mid;
	s = 0;   e = tmp;
	mid = s + (e-s)/2;
	while(s<=e){
		if(mp[mid]==a)
			return mid;
		else if(mp[mid]>a)
			e = mid - 1;
		else 
			s = mid + 1;
		mid = s + (e-s)/2;
	}
	return -1;
}

int Find(int a, int &b){
	int c = 0;
	if(father[a]==a)
		return a;
	c = Find(father[a], b);
	b = b ^ val[a];
	return c;
}

void Union(int a, int b){
	father[b] = a;
}

int main()
{
	int len, n;
	int fx, fy;
	int bx, by;
	int key;
	int i;
	int tmp1, tmp2;

	scanf("%d", &len);
	scanf("%d", &n);

		for(i=0; i<n; i++){
			scanf("%d %d %s", a+i, b+i, ch+i);
			mp[i*2] = a[i];
			mp[i*2+1] = b[i];
		}

		sort(mp, mp+2*n);
		tmp = 0;
		for(i=1; i<2*n; i++){
			if(mp[i]!=mp[tmp]){
				mp[++tmp] = mp[i];
			}
		}

		for(i=0; i<=tmp; i++){
			father[i] = i;
			val[i] = 0;
		}
		for(i=0; i<n; i++){
			if(a[i]==1)  a[i] = 2;
			bx = bs(a[i]-1);      // 找到序号
			by = bs(b[i]);
			tmp1 = 0;   tmp2 = 0;
			fx = Find(bx, tmp1);
			fy = Find(by, tmp2);

			if(strcmp(ch[i], "even")==0)
				key = 0;
			else
				key = 1;

			if(fx==fy){   // 关系可以确定
				if(tmp1^key==tmp2)
					continue;
				else{
					printf("%d\n", i);
					key = 3;
					break;
				} 
			}
			else{
				tmp1 = 0;
				while( father[by]<bx ){
					tmp1 = tmp1 ^ val[by];
					tmp2 = by;
					by = father[by];
					if(tmp2==by)  break;
				}
				if(father[by]==bx){
					if(tmp1==key)
						continue;
					else{
						printf("%d\n", i);
						key = 3;
						break;
					}
				}
				else if(father[by]>bx){
					tmp2 = tmp1;
					tmp1 = tmp1 ^ val[by];
					val[bx] = tmp2 ^ key;
					father[bx] = father[by];
					father[by] = bx;
					val[by] = tmp1 ^ key;
				}
				else{
					father[by] = bx;
					val[by] = tmp1 ^ key;
				}
				//Union(fx, fy);             // 合并根
				//val[by] = val[bx] ^ key;   // 输入相邻节点的关系    ???
			}
		}
		if(key!=3)
			printf("%d\n", n);


	return 0;
}
//*/



//*    8092K	63MS	C++	1409B   hash

#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

#define maxn 1000010
#define P 999997
int r[maxn],set[maxn];      //0表示偶数1表示奇数
int n,m,cnt,tp;
int head[maxn];

struct node{
    int num,next,value;
}a[maxn];

int get_hash(int x){         // 按照出场顺序，给点标号
    int H=x%P;
    for(int i=head[H];i!=0;i=a[i].next){
        if(x==a[i].value)
			return a[i].num;
    }
    a[cnt].next=head[H];
    a[cnt].value=x;
    a[cnt].num=++tp;
    head[H]=cnt++;
    return tp;
}

int find_set(int x){
    if(x!=set[x]){
        int tmp=find_set(set[x]);
        r[x]=r[x]^r[set[x]];      // 调整子孙与根之间的关系
        set[x]=tmp;
    }
    return set[x];
}

void union_set(int x,int y,int v){
    int X=find_set(x);
    int Y=find_set(y);
	// 调整Y的father和相对奇偶值
    set[Y]=X;
    r[Y]=(v^r[x])^r[y];
}

int main()
{
    int i,x,y,v;
    char s[10];
    scanf("%d",&n);
    for(i=0;i<=maxn;i++)set[i]=i;
    cnt=1;tp=0;
    scanf("%d",&m);
	bool flag=false;

		for(i=1;i<=m;i++){
			scanf("%d%d%s",&x,&y,s);
			if(x>y){                 //互换，不换也能AC，因为题目要求x<=y
				x=x^y;
				y=x^y;
				x=y^x;
			}

			if(flag)	continue;

			if(s[0]=='o')v=1;
			else v=0;

			x=get_hash(x-1);
			y=get_hash(y);
			int X=find_set(x);
			int Y=find_set(y);

			if(X!=Y){
				union_set(x,y,v);continue;
			}

			if((r[y]^r[x])!=v){
				printf("%d\n",i-1);flag=true;
			}
		}

	    if(!flag)printf("%d\n",m);
	
	return 0;
}
//*/



/*    556K	63MS	C++	1310B

#include <iostream>
using namespace std;
#define MOD 9941
#define MAX 10005

struct node
{
    node():next(0){}
    int val, index;
    node* next;
}HashMap[MOD];

int root[MAX],num[MAX],u=0;
char c[MAX];
int find(int x)
{
    int y = x%MOD;
    node *p,*q;
    p = &HashMap[y], q = HashMap[y].next;
    while (q)
        if(q->val == x)return q->index;
        else p=q,q=q->next;
    node *temp=new node(); temp->val=x,temp->index=++u,p->next=temp,num[u]=x;
    return u;
}
int findroot(int x)
{
    int t;
    if(root[x]!=x){
		t = root[x];
		root[x]=findroot(root[x]);
		c[x] = c[t]^c[x];
	}
    return root[x];
}
int main()
{
    int i,l,n,s,t,r1,r2,v,ans;
    bool IsError = false;
    char ch[5];
    for(i=0;i<MAX;i++)
		root[i]=i, c[i]=0;
    scanf("%d\n%d", &l, &n);

    for (i=1; i<=n;i++)
    {
        scanf("%d %d %s", &s, &t, ch);

        if(IsError)continue;

        v = (ch[0] == 'e')?0:1;

        s=find(s-1),t=find(t);
        r1=findroot(s), r2=findroot(t);

        if(r1==r2 && (c[s]^c[t]^v)){
			IsError=true;ans=i-1;
		}
        else if(r1 != r2)
        {
            if(num[r1]<num[r2])
				root[r2]=r1,   c[r2]=c[s]^c[t]^v;
            else
				root[r1]=r2, c[r1]=c[s]^c[t]^v;
        }
    }
    IsError ? printf("%d\n",ans) : printf("%d\n", n);
    return 0;
}
//*/