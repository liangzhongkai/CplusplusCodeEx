/*
142857
0588235294117647
052631578947368421
0434782608695652173913
0344827586206896551724137931
0212765957446808510638297872340425531914893617
0169491525423728813559322033898305084745762711864406779661
016393442622950819672131147540983606557377049180327868852459
01
758241
0588235294117646
152631578947368421
04347826086956521739130
034482758620689655172413793
0212765957446808501638297872340425531914893617
0169491525423728813559322033898305084745762711864406779666
485767305968737584736478947631110239847564719283674623819109
999999999999999999999999999999999999999999999999999999999999


> 142857 is cyclic
> 0588235294117647 is cyclic
> 052631578947368421 is cyclic
> 0434782608695652173913 is cyclic
> 0344827586206896551724137931 is cyclic
> 0212765957446808510638297872340425531914893617 is cyclic
> 0169491525423728813559322033898305084745762711864406779661 is cyclic
> 016393442622950819672131147540983606557377049180327868852459 is cyclic
> 01 is not cyclic
> 758241 is not cyclic
> 0588235294117646 is not cyclic
> 152631578947368421 is not cyclic
> 04347826086956521739130 is not cyclic
> 034482758620689655172413793 is not cyclic
> 0212765957446808501638297872340425531914893617 is not cyclic
> 0169491525423728813559322033898305084745762711864406779666 is not cyclic
> 485767305968737584736478947631110239847564719283674623819109 is not cyclic
> 999999999999999999999999999999999999999999999999999999999999 is not cyclic
//*/

//*                 204K	0MS	C++	1521B  
#include<iostream>
#include<cstring>

using namespace std;


int Judge(char ch[])
{//判断字符串ch是否全为0，若全为0，返回0，否则返回1
	int i,k;
	k=strlen(ch);
	for(i=0;i<k;i++)
		if(ch[i]!='0')
			return 0;
	return 1;
}


char* BigNumMultiSmall(char a1[],int b1, char c[])   // 保留前置0，若结果为0，只有单个0
{
	int i,j,t;
	int a[2000]={0};
	//将字符串转化为整型数组，并逆置
	t=strlen(a1);
	for(i=0;i<t;i++)
		a[i]=a1[t-1-i]-'0';
	//整型数组的每个元素乘以b1，然后对其进行求余，整除，使其只有一位数
	a[0]=a[0]*b1;
	for(i=1;i<t;i++)
	{
		a[i]*=b1;
		a[i]+=a[i-1]/10;
		a[i-1]=a[i-1]%10;
	}
	while(a[i-1]>9)
	{//若最后一个元素大于9
		a[i]=a[i-1]/10;
		a[i-1]=a[i-1]%10;
		i++;
	}
	//将得到的整型数组逆置赋给字符串
	for(j=0;j<i;j++)
		c[j]=a[i-j-1]+'0';
	c[i] = '\0';
	if(Judge(c))//若积全为0，则只输出一个0
		strcpy(c,"0\0");

	return c;
}


int main()
{
	char b1[65];
	char c[65];
	int i, j, k;
	int length = 0, key;

	while( cin >> b1 )
	{
		length = strlen(b1);

		for(i=1; i<=length; i++)
		{
			BigNumMultiSmall(b1, i, c);

			key = 0;
			if(length==strlen(c))
			{
				for(j=0; j<length; j++)
				{
					if(b1[0]==c[j])
					{
						int count = 0;
						for(k=j; k<j+length; k++)
						{
							if(b1[k-j]==c[k%length])
							{
								count++;
							}
						}
						if(count==length)  //相等就跳出
							break;
					}
				}
				if(j==length)
				{
					key = 1;
					break;
				}
			}
			else
				key = 1;
		}

		if(key==1)
			cout << b1 << " is not cyclic" << endl;
		else
			cout << b1 << " is cyclic" << endl;
	}

	return 0;
}
//*/


