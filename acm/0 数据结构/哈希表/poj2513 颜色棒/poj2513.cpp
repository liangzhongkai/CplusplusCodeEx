/* 先用map将颜色名称转换为连续不同的数字
// Time Limit Exceeded
#include<iostream>
#include<map>
#include<string>
#include<cstring>
#include<cstdio>

using namespace std;

map<string, int> mp;

int color[2500000];

int main()
{
	//freopen("data.txt", "r", stdin);
	string str1, str2;
	char ch1[12], ch2[12];
	int i, cnt = 1;
	int key = 0;

	memset(color, 0, sizeof(color));

	while(scanf("%s %s", ch1, ch2)!=EOF){
		 str1 = ch1;
		 str2 = ch2;
		 if(mp.find(str1)==mp.end())   mp[str1] = cnt++;
		 if(mp.find(str2)==mp.end())   mp[str2] = cnt++;
		 color[mp[str1]]++;   color[mp[str2]]++;
	}

	for(i=1; i<cnt; i++){
		if(color[i]&1)
			key++;
	}

	if(key==0 || key==2)   printf("Possible\n");
	else   printf("Impossible\n");

	return 0;
}
//*/




/*    RuntimeError
#include <stdio.h>
#define N 250001
int color[N],father[N];

int hash(char *s){
    int key=1;
    while(*s)   key=(key*29+(*s++)-'a')%9991;
    return key;
}

int find(int x){   // 开始的时候是返回自己
    int tmp=0;
    int root=x;
    while(father[root]>=0)   root=father[root];
    while(x!=root){   //将沿着根路径的顶点指向root
        tmp=father[x];
        father[x]=root;
        x=tmp;
    }
    return root;
}

void Union(int root1,int root2){
	printf("%d %d\n", root1, root2);
	printf("%d %d\n", father[root1], father[root2]);
    int sum=father[root1]+father[root2];
    if(father[root1]>father[root2]){
        father[root1]=root2;
        father[root2]=sum;
		//printf("***%d %d %d\n", father[root1], father[root2], sum);
    }
    else{
        father[root2]=root1;
        father[root1]=sum;
    }
	
}

int main(void)
{
	//freopen("data.txt", "r", stdin);
    register int i;
    int a,b,root1,root2,num=0;
    char s1[11],s2[11];
    for(i=0;i<N;++i){
        father[i]=-1;
        color[i]=0;
    }
    while(scanf("%s%s",s1,s2)!=EOF){
        a=hash(s1);
        b=hash(s2);
        color[a]++;
        color[b]++;
        root1=find(a);     //father[root1] = -4 表示有4个以root1为根连通了。
        root2=find(b);
        if(root1!=root2)    Union(root1,root2);
		//printf("%d %d\n", father[root1], father[root2]);
		//printf("*********\n");
    }
    int root = find(a);
	//printf("%d\n", root);
    for(i=0;i<N;++i){            //遍历hash表找出度大于0的顶点
        if(color[i]>0){
            if(color[i]%2){      //奇数顶点个数
                num++;
                if(num>2){
                    puts("*Impossible");
                    return 0;
                }
            }
            if(root!=find(i)){   //判断是否连通图
                 puts("**Impossible");
                 return 0;
            }
        }
    }
    puts("Possible");
    return 0;
}
//*/



/*      2116K	532MS	C++	1751B
#include <stdio.h>
#define N 250001
int color[N],father[N];

int hash(char *s)   //这个哈希函数居然能唯一识别各种“颜色”
{
    int key=1;
    while(*s)   key=(key*29+(*s++)-'a')%9991;
    return key;
}

int find(int x)   // 开始的时候是返回自己
{
    int tmp=0;
    int root=x;
    while(father[root]>=0)   root=father[root];
    while(x!=root){
        tmp=father[x];
        father[x]=root;
        x=tmp;
    }
    return root;
}

void Union(int root1,int root2)
{
	//printf("%d %d\n", father[root1], father[root2]);
    int sum=father[root1]+father[root2];
    if(father[root1]>father[root2]){
        father[root1]=root2;
        father[root2]=sum;
    }
    else{
        father[root2]=root1;
        father[root1]=sum;
    }
	//printf("%d %d\n", father[root1], father[root2]);
}

int main(void)
{
	freopen("data.txt", "r", stdin);
    register int i;
    int a,b,root1,root2,num=0;
    char s1[11],s2[11];
    for(i=0;i<N;++i){
        father[i]=-1;
        color[i]=0;
    }
    while(scanf("%s%s",s1,s2)!=EOF){
        a=hash(s1);
        b=hash(s2);
        color[a]++;
        color[b]++;
        root1=find(a);
        root2=find(b);
        if(root1!=root2)    Union(root1,root2);
		//printf("%d %d\n", root1, root2);
		//printf("%d %d\n", father[root1], father[root2]);
		//printf("*********\n");
    }
    int root=1;
    for(i=0;i<N;++i){
        if(color[i]>0){
            if(color[i]%2){
                num++;
                if(num>2){
                    puts("Impossible");
                    return 0;
                }
            }
            if(root==1) root=find(i);
            else if(root!=find(i)){
                    puts("Impossible");
                    return 0;
                }
        }
    }
    puts("Possible");
    return 0;
}
//*/

 
//*     73400K	1907MS	C++	1431B
//      75328K	1875MS	C++	1555B
#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>

using namespace std;

int ii;
struct trie{
	int id;
	struct trie *next[26];
	trie(){
		id = 0;
		for(ii=0; ii<26; ii++)
			next[ii] = 0;
	}
};

trie* t = new trie();
int cnt = 1;

const int N = 500010;
int father[N], c[N], size[N];

int Find(int a){
	if(father[a]==a)
		return a;
	while(father[a]!=a){
		a = father[a];
	}
	return a;
}

void Union(int a, int b){
	if(size[a] > size[b]){
		father[a] = b;
		size[b]++;
	}
	else{
		father[b] = a;
		size[a]++;
	}
}

int InsertTree(char *s){
	int i;
	int len = strlen(s), k;
	trie* p=t;           // 不可以写成 trie* p = new trie(); p只作指针用
	for(i=0; i<len; i++){
		k = s[i]-'a';
		if(p->next[k]==0)
			p->next[k] = new trie();
		//if(i!=len-1)                  //  这里让我wa了无数次
		p = p->next[k];
	}
	if(p->id==0)
		p->id = cnt++;   // 编号
	return p->id;
}

int main()
{
	freopen("data.txt", "r", stdin);
	int i, ans;
	int a, b, fa, fb;
	char st1[12], st2[12];

	for(i=0; i<N; i++){
		father[i] = i;
	}
	memset(c, 0, sizeof(c));
	memset(size, 0, sizeof(size));

	while(scanf("%s %s", st1, st2)!=EOF){
		a = InsertTree(st1);
		b = InsertTree(st2);
		c[a]++; c[b]++;
		fa = Find(a);   fb = Find(b);
		if(fa!=fb)  Union(fa, fb);
	}

	ans = 0;
	int key = Find(1);       // 之前写了father[1],wa了好多次
	for(i=1; i<cnt; i++){
		if(c[i]&1)   ans++;   // 为了计算度数为奇数的点数
		if(Find(i)!=key){       // 必须是连通的 
			printf("Impossible\n");
			return 0;
		}
	}

	if(ans>2)
		printf("Impossible\n");
	else 
		printf("Possible\n");
	
	return 0;
}
//*/





/*        75328K	1360MS	C++	1443B
#include<iostream>
using namespace std;
#define N 500010

struct Node
{
   int id;
   Node *p[26];
   Node(){
      int i;
      id=-1;
      for (i=0;i<26;i++)
        p[i]=NULL;
   }
}root;

int d[N],parent[N],rank[N],cnt;

int GetNum(char *s){
   int i;
   Node *r=&root;
   for (i=0;s[i];i++){
      if (r->p[s[i]-'a']==NULL)
        r->p[s[i]-'a']=new Node();
      r=r->p[s[i]-'a'];
   }
   if (r->id==-1)
      r->id=cnt++;
   return r->id;
}

int FindSet(int i){
   if (parent[i]!=i)
      parent[i]=FindSet(parent[i]);
   return parent[i];
}

int UnionSet(int i,int j){
   i=FindSet(i);
   j=FindSet(j);
   if (i!=j)
      if (rank[i]>rank[j])
        parent[j]=i;
      else{
        parent[i]=j;
        if (rank[i]==rank[j])
           ++rank[j];
      }
   return i!=j;
}

int main()
{
	freopen("data.txt", "r", stdin);
   int i,j,k;
   char s1[12],s2[12];
   for (i=0;i<N;i++)
      parent[i]=i;
   cnt=0;
   memset(rank,0,sizeof(rank));
   memset(d,0,sizeof(d));
   while (scanf("%s%s",s1,s2)!=EOF)
   {
      j=GetNum(s1);
      k=GetNum(s2);
      d[j]++;
      d[k]++;
      UnionSet(j,k);
   }
   for (k=i=0;i<cnt;i++)
      if (d[i]%2)
        k++;
   j=FindSet(0);
   for (i=1;i<cnt;i++)
      if (FindSet(i)!=j)
      {
        printf("Impossible\n");
        return 0;
      }
   if (k<3)
      printf("Possible\n");
   else
      printf("Impossible\n");
   return 0;
}
//*/









/*   4752K	1032MS	C++	1456B
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define SET(p,v) memset(p,v,sizeof p)

const int SIZE=500001,ALSIZE=26;

struct E{
	unsigned short u,v;
}edge[SIZE];

int N,M,count,trieN;
unsigned short deg[SIZE],p[SIZE];

struct node{
	unsigned short id;
	unsigned short branch[ALSIZE];
}trie[70000];

unsigned short search(char *word){
	char now;
	int cur=1;

	for(;*word;++word){
		now=*word-'a';

		if(!trie[cur].branch[now]) trie[cur].branch[now]=++trieN;

		cur=trie[cur].branch[now];
	}

	if(!trie[cur].id) trie[cur].id=++N;

	return trie[cur].id;
}

unsigned short Find(unsigned short x){
	return p[x]?p[x]=Find(p[x]):x;
}

void Union(unsigned short x,unsigned short y){
	unsigned short px=Find(x),py=Find(y);
	int vexNum=p[px]+p[py];

	if(px!=py){ ++count; p[px]=py; }
}

bool isConnect(){
	count=0;
	for(int i=1;i<M;++i) Union(edge[i].u,edge[i].v);

	return M==1 || count+1==N;
}
int main(){
	int i;
	char a[11],b[11];

	int u,v; M=1; N=0; trieN=1;
	while(1){
		for(i=0;~(a[i]=getchar()) && a[i]!=' ';++i); 
		if(a[i]==-1) break;

		a[i]=0; 
		
		for(i=0;(b[i]=getchar())!='\n';++i); b[i]=0;
		
		u=search(a); v=search(b);
		
		++deg[u]; ++deg[v];
		edge[M].u=u; edge[M++].v=v;
	}

	int odd=0;
	for(i=1;i<=N;++i)
		if(deg[i]&1)
			++odd;

	if((!odd || odd==2) && isConnect()) puts("Possible");
	else puts("Impossible");

	return 0;
}
//*/