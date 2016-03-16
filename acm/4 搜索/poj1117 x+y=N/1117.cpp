/*
��Ŀ������һ�� N (10 <= N <= 10^9), ������������������������ (x,y):
y Ϊ x ȥ��ĳ�� 10 ����λ���γɵ�������������Դ� 1234 ��ȥ�� 3 �õ� 124��
y ���Ǳ� x ��һλ�������� 0 ��ͷ�� ��ȥ�� 1002 ��ǧλ��õ� 002��
x+y = N��

���ֱ���ѵĻ����������⣬�� N ��ʮ���Ʊ�ʾ�� n λ��. �� x ҪôҲΪ n λ����ҪôΪ n-1 λ�������������ĸ��ӶȾ�ԼΪ O(N/10), ������ N ������Ϊ 10^9, ���������ռ��� 10^8 �������ֻ��һ����ѭ��ʲôҲ�����Ļ����������������ʱ��Ҳ��Ҫ�ϰ� ms������Ȼ�ǲ����еģ���Ҫ������ô����������������
����һ�� n λ�� x , ȥ���� i λ��(0<=x<="" p="">

y = x - ( int(x/10^i) - int(x/10^(i+1) ) * 10^i
���� int() Ϊ��ȡ����^Ϊ�˷���

���� x+y = 2*x - ( int(x/10^i) - int(x/10^(i+1) )* 10^i = N��
�� ( int(x/10^i) - int(x/10^(i+1) ) = T, �õ�

2*x - T*10^i = N. ����
T= (2*x - N)/10^i��
��Ȼ������ T, N, x ��Ϊ�������� (2*x - N) % 10 ^i = 0��

���ǿ��Եó��㷨1:

1�� T ��Ȼ���� 0, ���������� T=1, ��� x = (10 ^i + N)/2. ��� x ��Ϊ������ֱ���˳���
2�� ���� T == ( int(x/10^i) - int(x/10^(i+1) ) ? ����ǣ��� x �� N-x ��Ϊһ���.
3�� T = T + 1���⽫ʹ�� x += (10^i)/2�� �ظ����� 2, ��� x > N, ���˳���
������㷨���Կ���, x ÿ�ε��� (10^i)/2, �� i Ϊ��λʱ���� 10^i �Ƚϴ��ʱ�������ռ��Ǻ�С�ġ����� i �Ƚ�С��ʱ��Ͳ������ˡ� ��ʱ���Խ�����ķ��̽��и��졣

�� T ����ģ����ʾ������ T= (x - x%10^i)/10^i - (x - x%10^(i+1))/10^(i+1), ���������·��̣�

2*x - [ (x - x%10^i)/10^i - (x - x%10^(i+1))/10^(i+1)] * 10^i = K

������ 11*x + 10*x%(10^i) - x%10^(i+1) = N. �� M = x%10^(i+1) - 10*x%(10^i), �õ�:

11 * x - M = 10*N, ���� x = (10*N+ M)/11. ͬ��Ҳ�� x, M,N ���������� ����֪ -10^(i+1) < M < 10^(i+1).

���ǵõ��㷨2:

1. �� -10^(i+1) < M < 10^(i+1) ��Ѱ�ҵ���һ����ʹ�� 10*N+M �ܱ� 11 ������ Mֵ m.
2. ��� x = (10*N+M)/11. ���� M == x%10^(i+1) - 10*x%(10^i)? ������ x,N-x ��Ϊһ���.
3. m += 11.�ظ�����2, ��� m>= 10^(i+1), ���˳�.
���㷨 2 ���������Ӷ�Ϊ 10^(i+1) /11 ԼΪ 10^i, �ɼ��ڽϵ�λ�ϣ��� 10^i ��С��ʱ��Ƚ����á�

���ǵó��ⷨ��

���� i, (0<=i=n/2 ʱ�����㷨1, ��������㷨2�������� ʱ�临�Ӷ�ԼΪ O(sqrt(N)).
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
///���������ѧ�������Ļ��϶�Ҫ��ʱ����Ϊ10^9������̫��  
///�������õĹ��취����Ҫ������нϴ��һ��Ϊm����m��λ����������ȡ���Ҫȥ�����ǵ�  
//kλ���֣�����������Ϊ0,1��������ͨ��kλ��m�ֳ������֣��ұ߲��ֿ϶��ͼ������ұ����  
//��Ҫ��������Ӧλ����֮�͵�ĩλ��n�Ķ�Ӧλ��ͬ������10=10+0��kλ��߲���Ӧ�������  
//һλ��ö��kͬʱ����k�ұߵĲ��֣��õ��ұ߲��֣���߲��ֿ��Ը��ݺ��������  
//ע�������ұ߲���ʱ��ע��ÿһλ�п������������������͵�ĳλΪ2���������Ӧλ����Ϊ1  
//Ҳ����Ϊ6 
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
		for(i=strlen(num)-1;i>=0;i--)  //��ÿһλ���д���
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

























