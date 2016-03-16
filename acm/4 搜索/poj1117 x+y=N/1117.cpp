/*
题目：给定一个 N (10 <= N <= 10^9), 求满足以下条件的所有数对 (x,y):
y 为 x 去掉某个 10 进制位后形成的新数，比如可以从 1234 中去掉 3 得到 124；
y 总是比 x 少一位并可以以 0 开头， 如去掉 1002 的千位后得到 002。
x+y = N。

如果直接搜的话，根据题意，设 N 的十进制表示是 n 位数. 则 x 要么也为 n 位数，要么为 n-1 位数。这样搜索的复杂度就约为 O(N/10), 在题中 N 最大可能为 10^9, 所以搜索空间是 10^8 级别。如果只是一个空循环什么也不做的话，完成整个搜索的时间也需要上百 ms。这显然是不可行的，需要考虑怎么来减少搜索次数。
考虑一个 n 位数 x , 去掉第 i 位数(0<=x<="" p="">

y = x - ( int(x/10^i) - int(x/10^(i+1) ) * 10^i
其中 int() 为下取整，^为乘方。

则有 x+y = 2*x - ( int(x/10^i) - int(x/10^(i+1) )* 10^i = N。
设 ( int(x/10^i) - int(x/10^(i+1) ) = T, 得到

2*x - T*10^i = N. 即是
T= (2*x - N)/10^i；
显然，其中 T, N, x 均为整数。即 (2*x - N) % 10 ^i = 0。

于是可以得出算法1:

1、 T 显然大于 0, 于是首先令 T=1, 算出 x = (10 ^i + N)/2. 如果 x 不为整，可直接退出。
2、 检验 T == ( int(x/10^i) - int(x/10^(i+1) ) ? 如果是，将 x 和 N-x 即为一组解.
3、 T = T + 1，这将使得 x += (10^i)/2， 重复步骤 2, 如果 x > N, 则退出。
从这个算法可以看出, x 每次递增 (10^i)/2, 当 i 为高位时，即 10^i 比较大的时候，搜索空间是很小的。但是 i 比较小的时候就不适用了。 这时可以将上面的方程进行改造。

将 T 用求模来表示，即有 T= (x - x%10^i)/10^i - (x - x%10^(i+1))/10^(i+1), 于是有以下方程：

2*x - [ (x - x%10^i)/10^i - (x - x%10^(i+1))/10^(i+1)] * 10^i = K

化简后得 11*x + 10*x%(10^i) - x%10^(i+1) = N. 令 M = x%10^(i+1) - 10*x%(10^i), 得到:

11 * x - M = 10*N, 即是 x = (10*N+ M)/11. 同样也有 x, M,N 都是整数。 且易知 -10^(i+1) < M < 10^(i+1).

于是得到算法2:

1. 在 -10^(i+1) < M < 10^(i+1) 内寻找到第一个能使得 10*N+M 能被 11 整除的 M值 m.
2. 求出 x = (10*N+M)/11. 检验 M == x%10^(i+1) - 10*x%(10^i)? 如果相等 x,N-x 即为一组解.
3. m += 11.重复步骤2, 如果 m>= 10^(i+1), 则退出.
由算法 2 的搜索复杂度为 10^(i+1) /11 约为 10^i, 可见在较低位上，即 10^i 较小的时候比较适用。

于是得出解法：

遍历 i, (0<=i=n/2 时采用算法1, 否则采用算法2收搜索。 时间复杂度约为 O(sqrt(N)).
//*/

/*
#include<iostream>

using namespace std;

int n,len=0,num[30];

int getbase(int base)
{
     int key=base/11,  k=base%11;
     if(k==10) return 0;
     return 10*key+k;   
}

int cmp( const void *a ,const void *b)
{
     return *(int *)a - *(int *)b;
}

void output()
{
     qsort(num,len,sizeof(num[0]),cmp);
     int i,j=0;
     for(i=1;i<len;i++) if(num[i]!=num[j]) num[++j]=num[i];
     printf("%d\n",j+1);
     for(i=0;i<=j;i++){
            int x=0,t=num[i];
            while(t){
                 x++;
                 t=t/10; 
            }        
            if(x==1) continue;
            x--;
            printf("%d + ",num[i]);
            cout.width(x);
            cout.fill('0');
            cout<<n-num[i];
            printf(" = %d\n",n);    
     }     
}

int main()
{
    while(true)
	{
		scanf("%d",&n);
		int base=1,x,y,key;
		while(base<=n)
		{
			  key=n/base;
			  y=n%base;
			  x=getbase(key)*base;

			  if(x!=0 && y%2==0) num[len++]=x+y/2;

			  if(base!=1)
			  {
				 key--;
				 y=base+y;
				 x=getbase(key)*base;
				 if(x!=0 && y%2==0) num[len++]=x+y/2;
			  }
			  base=base*10;
		}
		if(len>0) output();
		else printf("0\n");
		len=0;
   
	}

    return 0;
}
//*/





//*
///如果当做数学题来做的话肯定要超时，因为10^9数量级太大  
///这题我用的构造法，设要求的数中较大的一个为m，则m的位数最多与和相等。设要去掉的是第  
//k位数字（从左到右依次为0,1……），通过k位将m分成两部分，右边部分肯定和加数的右边相等  
//且要满足两对应位数字之和的末位与n的对应位相同，例如10=10+0；k位左边部分应与加数错开  
//一位；枚举k同时搜索k右边的部分，得到右边部分，左边部分可以根据和推算出来  
//注意搜索右边部分时，注意每一位有可能有两种情况，假设和的某位为2，则加数对应位可能为1  
//也可能为6 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char num[15],s1[1000][15],s2[1000][15];
long n,t;

int decide(char s[],int k,char t1[],char t2[])
{
	int len=strlen(num);
	int i,j,p;
	char temp[15];
	for(i=0;i<=9;i++)
	{
		strcpy(temp,s);
		t1[k]='0'+i;
		if(temp[k]<t1[k])
		{
			t2[k]=temp[k]+10-t1[k]+'0';
			p=k-1;
			if(p>=0)
			{
			while(temp[p]=='0')
			temp[p--]+=9;
			temp[p]-=1;
			}
		}
		else
		t2[k]=temp[k]-t1[k]+'0';
		for(j=k-1;j>=0;j--)
		{
			t1[j]=t2[j+1];
			if(temp[j]<t1[j])
			{
				t2[j]=temp[j]+10-t1[j]+'0';
				p=j-1;
				if(p>=0)
				{
				while(temp[p]=='0')
				temp[p--]+=9;
				temp[p]-=1;
				}
			}
			else
			t2[j]=temp[j]-t1[j]+'0';
		}
		if(t2[0]=='0')
		{
			t2[len]='\0';t1[len]='\0';
			if(strcmp(t1,t2)!=0)
			{
				for(j=0;j<t;j++)				
				{
					if(strcmp(s1[j],t1)==0)
					return 0;
				}
				strcpy(s1[t],t1);
			    strcpy(s2[t++],t2);
			}			
		}
	}
	return 0;
}
int init(char s[],int k,int p,char t1[],char t2[])
{
	if(p==k)
		decide(s,k,t1,t2);
	else
	{
		int j;
		if((s[p]-'0')%2)
			return 0;
		else
		{
			t1[p]=(s[p]-'0')/2+'0';
			t2[p]=t1[p];

			init(s,k,p-1,t1,t2);

			t1[p]=(s[p]-'0'+10)/2+'0';
			t2[p]=t1[p];
			j=p-1;

			while(j>0&&s[j]=='0')
				s[j--]+=9;

			s[j]-=1;

			init(s,k,p-1,t1,t2);
		}
	}
	return 0;
}
int search(int k)
{
	char s[15],t1[15],t2[15];
	strcpy(s,num);
	init(s,k,strlen(s)-1,t1,t2);
	return 0;
}
int cmp(const void* _ch1,const void* _ch2)
{
	char* ch1=(char *)_ch1;
	char* ch2=(char *)_ch2;
	return strcmp(ch1,ch2);
}
int cmp1(const void* _ch1,const void* _ch2)
{
	char* ch1=(char *)_ch1;
	char* ch2=(char *)_ch2;
	return 0-strcmp(ch1,ch2);
}
int main()
{
	//freopen("pairs13.txt","r",stdin);
	//freopen("out13.txt","w",stdout);
	while(scanf("%d",&n)==1)
	{
		sprintf(num,"%d",n);
		int i;
		t=0;
		for(i=strlen(num)-1;i>=0;i--)  //对每一位进行处理
			search(i);

		printf("%d\n",t);
		qsort(s2,t,sizeof(s2[0]),cmp1);
		qsort(s1,t,sizeof(s1[0]),cmp);
		for(i=0;i<t;i++)
		{
			if(s1[i][0]=='0')
			printf("%s + %s = %d\n",s1[i]+1,s2[i]+2,n);
			else
			printf("%s + %s = %d\n",s1[i],s2[i]+1,n);
		}
	}
	return 0;
}
//*/

























