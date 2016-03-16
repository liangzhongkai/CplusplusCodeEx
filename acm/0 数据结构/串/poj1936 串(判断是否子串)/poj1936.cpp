//*  296K	16MS	C++	488B
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

char s[100001];
char t[100001];

int main()
{
	int i;
	 while( cin >> s >> t)
	 {
		 int sl = strlen(s);
		 int tl = strlen(t);
		 if(sl>tl)
			 printf("No\n");
		 else
		 {
			 int j=0;
			 for(i=0; i<tl; i++)
			 {
				 if(t[i]==s[j])
					 j++;
				 if(j==sl)
					 break;
			 }

		     if(j==sl)
				 printf("Yes\n");
			 else
				 printf("No\n");
		 }
	 }

	return 0;
}

//*/