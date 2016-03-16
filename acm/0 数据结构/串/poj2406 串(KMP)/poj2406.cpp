//    Output  Limit   Exceeded
//    Time    Limit   Exceeded
/*
#include<iostream>
#include<cstring>

using namespace std;

const int N=1000005;
int r[N],sa[N],rank[N],height[N],wa[N],wb[N],cnt[N];
char ch[N];

int cmp(int *x, int a, int b, int l){
	return (x[a]==x[b]) && (x[a+l]==x[b+l]);
}
void suffix(int *s, int n){
	// sa数组
	int *x = wa, *y = wb, *t;
	int i, j, p, k;
	memset(rank, 0, sizeof(rank));
	memset(height, 0, sizeof(height));
	memset(sa, 0, sizeof(sa));
	memset(cnt, 0, sizeof(cnt));

	int mm = 30;       //  总共28种 = 27个字母 + 0
	for(i=0; i<n; i++)   cnt[x[i]=s[i]]++;
	for(i=1; i<mm; i++)   cnt[i] += cnt[i-1];
	for(i=n-1; i>=0; i--)  sa[--cnt[x[i]]] = i;

	for(j=1, p=1; p<n; mm=p, j*=2){
		for(p=0, i=n-j; i<n; i++)   y[p++] = i;
		for(i=0; i<n; i++)
			if(sa[i]>=j)   y[p++] = sa[i] - j;
		for(i=0; i<mm; i++)   cnt[i] = 0;
		for(i=0; i<n; i++)   cnt[x[y[i]]]++;
		for(i=1; i<mm; i++)   cnt[i] += cnt[i-1];
		for(i=n-1; i>=0; i--)   sa[--cnt[x[y[i]]]] = y[i];

		for(t=x, x=y, y=t, p=1, x[sa[0]]=0, i=1; i<n; i++)
			x[sa[i]] = cmp(y, sa[i], sa[i-1], j)?p-1:p++;
	}
	// rank数组
	for(i=0; i<n; i++){
		rank[sa[i]] = i;
	}
	// height数组
	for(k=0, i=0; i<n; height[rank[i++]]=k)
		for(k?k--:0, j=sa[rank[i]-1]; s[i+k]==s[j+k]; k++);
}

int main()
{
	int i;
	int len;
	int cnt, max;
	while(scanf("%s", ch)!=EOF && ch[0]!='.'){
		len = strlen(ch);
		//printf("%s\n", ch);
		for(i=0; i<len; i++){
			r[i] = ch[i] - 95;
		}
		r[len++] = 0;
		//for(i=0; i<len; i++){
		//	printf("%d ", r[i]);
		//}
		//printf("\n");
		suffix(r, len);
		max = 0;
		cnt = 0;
		//for(i=0; i<len; i++){
		//	printf("%d ", height[i]);
		//}
		//printf("\n");
		for(i=0; i<len; i++){
			if(height[i]>0){
				cnt++;
			}
			else{
				max = max>cnt?max:cnt;
				cnt = 0;
			}
		}
		max = max>cnt?max:cnt;
		max++;
		printf("%d\n", max);
	}

	return 0;
}
//*/




/*  5080K	1969MS	C++	543B

#include<iostream>
#include<stdio.h>

using namespace std;

char a[1100000];
int p[1100000];

int main()
{
	 int t,i,j;
	 bool d;
	 char x;
	 d=true;
	 while(1)
	 {
		  t=0;
		  while(1)
		  {
			   scanf("%c",&x);
			   if (x==10) break;
			   if (x=='.') {d=false;break;}
			   a[++t]=x;
		  }
		  if (d==false) break;
		  p[1]=0;
		  j=0;
		  for(i=2;i<=t;i++)
		  {
			   while(j>0 && a[j+1]!=a[i]) j=p[j];
			   if (a[j+1]==a[i]) j++;
			   p[i]=j;
		  }
		  for(i=1; i<=t; i++){
		       printf("%d ", p[i]);
		  }
		  printf("\n");
		  if (t%(t-p[t])==0)
			  printf("%d\n",t/(t-p[t]));
		  else
		      printf("1\n");
	 }
	 //cin>>x;
	 return 0;
}
//*/



//*   5068K	125MS	C++	 427B
#include<iostream>
#include<stdio.h>
using namespace std;
char a[1100000];
int p[1100000];
int main(){
	 int t,i,j;
	 while(scanf("%s", a+1)!=EOF && a[1]!='.'){
		  p[1]=0;
		  j=0;
		  t = strlen(a+1);
		  for(i=2;i<=t;i++){
			   while(j>0 && a[j+1]!=a[i]) j=p[j];
			   if (a[j+1]==a[i]) j++;
			   p[i]=j;
		  }
		  for(i=1;i<=t;i++)
			  printf("%d ", p[i]);
		  printf("\n");
		  if (t%(t-p[t])==0) printf("%d\n",t/(t-p[t]));
		  else printf("1\n");
	 }
	 return 0;
}
//*/
