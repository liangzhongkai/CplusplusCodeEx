/*     406MS	408K	1494 B	
//     328MS	368K	1212 B	C++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define max(a,b) a>b?a:b

const int INF = 0x7ffffff;
const int N = 120010;
int dp[N];
int sum;

void zeroonepack(int p, int w){
	for(int i=sum; i>=p; i--){
		dp[i] = max(dp[i], dp[i-p]+w);
	}
}

void completepack(int p, int w){
	for(int i=p; i<=sum; i++){
		dp[i] = max(dp[i], dp[i-p]+w);
	}
}

void multiplepack(int p, int w, int num){
	if(num*p>=sum){
		completepack(p, w);
	}
	else{
		int k = 1;
		while(k<num){               //改为<之后 0MS	248K	970 B	C++
			zeroonepack(p*k, w*k);
			num -= k;
			k = k<<1;
		}
		zeroonepack(p*num, w*num);
	}
}

int main()
{
	int a[6];
	int i;
	int cnt;
	int count = 0;

	while(1){
		count++;
		cnt = sum = 0;
		for(i=0; i<6; i++){
			scanf("%d", a+i);
			sum += a[i]*(i+1);
		}
		if(sum==0)   break;
		if(sum&1){
			printf("Collection #%d:\n", count);
			printf("Can't be divided.\n\n");
		}
		else{
			sum = sum>>1;
			for(i=1; i<=sum; i++){
				dp[i] = -INF;
			}
			dp[0] = 0;
			for(i=0; i<6; i++){
				multiplepack(i+1, i+1, a[i]);
			}
			if(dp[sum]==sum){
				printf("Collection #%d:\n", count);
				printf("Can be divided.\n\n");
			}
			else{
				printf("Collection #%d:\n", count);
				printf("Can't be divided.\n\n");
			}
		}
	}

	return 0;
}
//*/




//*           46MS	408K	904 B	C++
#include"stdio.h"
#include"string.h"

int dp[60011];

int main()
{
		int num[7];
		int i,l,k;
		int sum;
		int total;
		int Case=1;
		while(scanf("%d",&num[1])!=-1)
		{
			sum=num[1];
			for(i=2;i<=6;i++){
				scanf("%d",&num[i]);
				sum+=num[i]*i;
			}

			if(sum==0)	break;
			if(sum%2!=0)
			{
				printf("Collection #%d:\n",Case++);
				printf("Can't be divided.\n\n");
				continue;
			}
			
			  total=sum/2;

			  for(l=1;l<=total;l++)
				  dp[l]=0;
			  for(k=0;k<=num[1]&&k<=total;k++)
				  dp[k]=1;
			  for(i=2;i<=6;i++)            //  不是DP，而是记忆化搜索！
			  {
				  for(l=total;l>=0;l--)
				  {
					  if(dp[l]==0)	continue;
					  for(k=1; k<=num[i]&&k*i+l<=total; k++)	
					  {
						  if(dp[k*i+l])	break;
						  dp[k*i+l]=1;
					  }
				  }
			  }
		  
			
			  if(dp[total])
			  {
				  printf("Collection #%d:\n",Case++);
				  printf("Can be divided.\n\n");
			  }
			  else
			  {
				  printf("Collection #%d:\n",Case++);
				  printf("Can't be divided.\n\n");
			  }
		}
			  return 0;
}

//*/