//  	0.015	112 KB
#include <stdio.h>

int f(int n,int k)
{
	int ans=1;
	int ed;
	int i;
	if (n%k)
	   ed=n%k;
	else
	   ed=k;
	for (i=0;true;i++)
	{
		int tmp= (n-i*k);
		ans*=tmp;
		if (tmp==ed)
		 break;
	}
	return ans;
}

int main()
{
	char buff[100];
	int n;
	scanf("%d%s",&n,buff);
	int cnt=0;
	int i;

	for (i=0;buff[i];i++)
	   if (buff[i]=='!')
		cnt++;

	int ans = f(n,cnt);

	printf("%d\n",ans);

	return 0;
}
