/*
#include<iostream>

using namespace std;


int main()
{


	return 0;
}
//*/



/*      172K	0MS	C++	1605B
#include<iostream>
#include<stdio.h>

using namespace std;

char a[1000],b[20][100],rest[1000];
int f[1000];

void pig(int x,int y)
{
	 int pp,i;
	 pp=0;
	 for(i=1;i<=y;i++)
		 if (rest[i]<a[i+x-1])
		 {
			 pp=1;break;
		 }
		 else if (rest[i]>a[i+x-1])
		 {
			 pp=2;break;
		 }
	if (pp==2)
	{
		for(i=1;i<=y;i++)
			rest[i]=a[i+x-1];
	}
}

bool dog(int x,int y,int z,int w)
{
	 int i;
	 for(i=1;i<=y;i++)
		if (a[x+i-1]!=b[z][w+i-1])
			return false;
	 return true;
}


int main()
{
	 int i,j,k,g,h,t,n,t1,tt;
	 char x;
	 bool d,d1,dd;
	 scanf("%d",&tt);

	 for(i=1;i<=tt;i++)
	 {
		  scanf("%d",&n);
		  t=0;
		  scanf("%c",&x); //吸收回车符

		  while(1)
		  {
			   scanf("%c",&x);
			   if (x==10) break;
			   else
				  a[++t]=x;
		  }

		  for(j=2;j<=n;j++)
		  {
			    t1=0;
				while(1)
				{
					   scanf("%c",&x);
					   if (x==10) break;
					   else
					      b[j][++t1]=x;
				}
				f[j]=t1;
		  }

		  dd=false;
		  for(j=1; j<=t; j++)
			rest[j]='T';

		  for(j=t; j>=3; j--)
		  {
			   if (dd==true) break;
			   for(k=1; k<=t-j+1; k++)
			   {
					d1=true;
					for(g=2; g<=n; g++)
					{
						 d=false;
						 for(h=1; h<=f[g]-j+1; h++)
							 if (dog(k,j,g,h)==true)
							 {
								 d=true;break;
							 }
						 if (d==false)
						 {
							 d1=false;break;
						 }
					}
					if (d1==true)
					{
						 dd=true;
						 pig(k,j);
					}
			   }
			   if (dd==true) break;
		  }
		  if (dd==true)
		  {
			   for(g=1;g<=j;g++)
					printf("%c",rest[g]);
			   printf("\n");
		  }
		  else
			   printf("no significant commonalities\n");
	 }
	 return 0;
}
//*/


/*     240K	32MS	C++	787B                         str.substr(begin, end)暴力子串

#include<iostream>
#include<string>

using namespace std;

int main()
{
	int t,i,n,k,j;
	string s[15], longest;
	cin>>t;
	while(t--)
	{
		longest="";
		cin>>n;

		for(i=1;i<=n;i++)
		{
			cin>>s[i];
		}

		for(i=3;i<=60;i++)
		{
			for(j=0;j<=60-i;j++)
			{
					string str=s[1].substr(j,i);
					int flag=1;

					for(k=2;k<=n;k++)
					{
						if(s[k].find(str)==string::npos)  // 找不到子串
						{
							flag=0;
							break;
						}
					}

					if(flag)
					{
						if(longest.length()<str.length())
							longest=str;
						else if(longest.length()==str.length() && str<longest)
								longest=str;
					}

			}
		}

		if(longest=="")
			cout<<"no significant commonalities"<<endl;
		else
			cout<<longest<<endl;
	}
	return 0;
}
//*/




/*          180K	16MS	C++	1002B 

#include <iostream>
#include <algorithm>
using namespace std;

char str[15][100];
char dest[100];
int start,n;

struct P
{
	char res[100];
}ans[100];

bool cmp(P a,P b)
{
    return strcmp(a.res,b.res)<0;//小于0时,a比b的大
}

void solve()
{
	 int i;
	 for(i=0;i<n;i++)
	 {
		  if(strstr(str[i],dest)==NULL)
		  {
			   start=1;
			   return ;
		  }
	 }
	 return ;
}

int main()
{
	 int ncase;
	 scanf("%d",&ncase);

	 while(ncase--)
	 {
		  scanf("%d",&n);
		  int i,j;
		  for(i=0;i<n;i++)
			  scanf("%s",str[i]);
		  int s=0;

		  for(i=60; i>=3; i--)
		  {
			   j=0;
			   while(j+i<=60)
			   {
					start=0;
					memset(dest,0,sizeof(dest));
					strncpy(dest,&str[0][j],i);

					solve();

					if(!start)
						 strcpy(ans[s++].res,dest);
					j++;
			   }
			   if(s)
				   break;
		  }
		  if(s)
		  {
				sort(ans,ans+s,cmp);
				printf("%s\n",ans[0].res);
		  }
	      else
				printf("no significant commonalities\n");
	 }

	 return 0;
}
//*/



/*                                       244K	16MS	C++	1919B            KMP+枚举
#include<iostream>        //KMP+枚举
#include<string>

using namespace std;

#define len 60
char str[10][100],base[100];    
int next[100];        

void get_next(char B[],int t)    //B[1]--B[t]
{
    next[1]=0;
    int j=0;
    for(int i=2;i<=t;++i)
    {
        while(j>0&&B[j+1]!=B[i])
            j=next[j];
        if(B[j+1]==B[i])
            j=j+1;
        next[i]=j;
    }
}
bool kmp(char A[],char B[],int t)    //A是主串,B是子串（从1开始）,查询B串在A串的哪些地方出现
{
    int j=0;
    for(int i=1;i<=len;++i)
    {
        while(j>0&&B[j+1]!=A[i])
            j=next[j];
        if(B[j+1]==A[i])
            j=j+1;
        if(j==t)
            return true;
    }
    return false;
}
int main()
{
    int cases,m, i, j, k;
    char res[100],tmp[100];
    cin>>cases;
    while(cases--)
    {
        cin>>m;
        for(i=0;i<m;++i)    
            scanf("%s",str[i]+1);        //下标从1开始
        int tag=1,flag=1,rear=0;
        strcpy(res,"");
        for(i=len;i>=3&&flag;--i)
        {
            for(j=1;j+i-1<=len;++j)
            {    
                for(k=j;k<j+i;++k)
                    base[k-j+1]=str[0][k];        //base[1]--base[i]

                get_next(base,i);
                tag=0;
                for(k=1;k<m;++k)
                    if(!kmp(str[k],base,i))
                    {
                        tag=1;break;
                    }

                if(tag==0)
                {
                    flag=0;
                    strncpy(tmp,base+1,i);    //把base[1..i]复制到tmp[0..i-1]
                    tmp[i]='\0';    //tmp[i]=0; 一样的  strcmp()函数需要它作为串结束的标志！
                    if(strlen(res)==0||strcmp(res,tmp)>0)    //字典排序的最小串
                        strcpy(res,tmp);                        
                }
            }
        }
        if(flag==1)
            printf("no significant commonalities\n");
        else
            printf("%s\n",res);
    }
    return 0;
}
//*/




/*                     164K	16MS	C++	2006B                      //sunday算法
#include "stdio.h"
#include "string.h"

char dna[11][100];
int n;

//sunday算法
bool sunday(char *patt)
{
    int temp[256];//存每个字母在匹配不成功时应后移几位
    int i, patt_size = strlen(patt);

    //初始化
    for(i = 0; i < 256; i++)
        temp[i] = patt_size + 1;
   
    //预处理匹配不成功时移动几位
    for(i=0; i < patt_size; i++ )
        temp[patt[i]] = patt_size - i;
   
    int limit = 60 - patt_size + 1;
   
    //匹配过程
    for(int k = 1; k < n; ++k){
        bool found = false;
        for(i = 0; i < limit; i += temp[dna[k][i+patt_size]]){
            if(dna[k][i] == patt[0]){
                char *match_text = dna[k] + i + 1;
                int match_size = 1;
                do{
                    if(match_size == patt_size){
                        found = true;
                        break;
                    }
                }while((*match_text++) == patt[match_size++] );
            }
            if(found) break;
        }
        if(!found) return false;
    }
   
    return true;
}

int main(void){
    int t, i;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        for(i = 0; i < n; ++i)
            scanf("%s", dna[i]);

        char *s0 = dna[0];
        char s[100], patt[100];
        bool found = false;
       
        //dna[0]分解出任意连续子串并匹配
        for(i = 60; i >= 3; --i)
		{
            for(int j=0; j <= 60-i; ++j)
			{
                memcpy(patt, s0 + j, i);
                patt[i] = 0;
               
                if(sunday(patt))
				{
                    if(!found)
					{
                        strcpy(s, patt);
                        found = true;
                    }
                    else if(strcmp(s, patt) > 0)
					{
                        strcpy(s, patt);
                    }
                }
            }
            if(found) break;
        }
       
        if(found) puts(s);
        else puts("no significant commonalities");
    }
   
    return 0;
}
//*/









//*         192K	16MS	C++	3195B             //后缀数组Height
  

#include<iostream>
using namespace std;

#define MAX_LEN 1000

int wa[MAX_LEN], wb[MAX_LEN], wv[MAX_LEN], wd[MAX_LEN], Height[MAX_LEN], sa[MAX_LEN], rank[MAX_LEN];
int n;

inline bool IsEqual(int *r, int a, int b, int l)
{
    return (r[a] == r[b] && r[a + l] == r[b + l]);
}

void da(int *r, int m)
{
    int i, j, p, *x = wa, *y = wb, *t;
    memset(wd, 0, sizeof(wd));
    for (i = 0; i < n; i++) wd[x[i] = r[i]]++; x[n] = y[n] = 0;
    for (i = 1; i < m; i++) wd[i] += wd[i - 1];
    for (i = n - 1; i >= 0; i--) sa[--wd[x[i]]] = i;

    for (p = 1, j = 1; p <= n; m = p, j *= 2)
    {
        for(p = 0, i = n - j; i < n; i++) y[p++] = i;
        for(i = 0; i < n; i++)if(sa[i] >= j)y[p++] = sa[i] - j;
        for(i = 0; i < n; i++) wv[i] = x[y[i]];
        memset(wd, 0, sizeof(wd));
        for(i = 0; i < n; i++) wd[wv[i]]++;
        for(i = 1; i < m; i++) wd[i] += wd[i - 1];
        for(i = n - 1; i >= 0; i--) sa[--wd[wv[i]]] = y[i];
        for(t = x, x = y, y = t, i = 1, p = 2,x[sa[0]] = 1; i < n; i++)
            x[sa[i]] = IsEqual(y, sa[i-1], sa[i], j) ? p - 1 : p++;
    }
}

void CalHeight(int *r)
{
    int i, j, k;
    for (i = 0; i < n; i++)rank[sa[i]] = i;
    for (i = 0, Height[0] = k = 0; i < n; Height[rank[i++]] = k)
        for (k?k--:0, j=(rank[i]>0)?sa[rank[i]-1]:0; rank[i]>0&&r[i+k]==r[j+k]; k++);
}

int main()
{
    int m, t, r[700], i, j, sp, sb, se, mid, s, l, ans, c, w;
    char str[61];
    bool visit[10], isfind;
    scanf("%d", &w);
    while (w--)
    {
        scanf("%d", &m); sp = 5;
        for(j = n = 0; j < m; j++)
        {
            scanf("%s", str);
            for (i = 0; i < 60; i++)
            {
                if(str[i] == 'A')r[n++] = 1;
                else if(str[i] == 'T')r[n++] = 2;
                else if(str[i] == 'G')r[n++] = 3;
                else r[n++] = 4;
            }
            r[n++] = sp++;
        }
        da(r, sp), CalHeight(r);
        for(sb=3,se=60,mid=31,s=0,ans=-1; sb < se;)
        {
            isfind = false;
            for(int i = 0; (i < n) && !isfind ; i++)
            {
                if(Height[i] < mid)memset(visit, false, sizeof(visit)), t = 0;
                if(Height[i] >= mid)
                {
                    if(t == 0){
                        l = sa[i-1] / 61;
                        if(!visit[l])visit[l] = true, t++;
                    }
                    l=sa[i]/61;
                    if(!visit[l])visit[l] = true, t++;
                    if(t == m)isfind = true,ans = i;
                }
            }
            if(isfind && mid == se)break;
            if(isfind)(sb == mid && se > sb) ? (mid = se):(sb = mid);
            else se = mid - 1, mid = (se + sb) / 2;
        }
        if(ans != -1)
            for(int i = 0; i < mid; i++)
            {
                c = r[sa[ans] + i];
                if(c == 1)printf("A");
                else if(c == 2)printf("T");
                else if(c == 3)printf("G");
                else printf("C");
            }
        else printf("no significant commonalities");
        printf("\n");
    }
    return 0;
}
//*/
