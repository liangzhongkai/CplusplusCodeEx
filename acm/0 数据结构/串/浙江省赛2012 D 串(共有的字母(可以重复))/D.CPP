//  C++ 	30s 	188kb
#include<iostream>
#include<string>
#include<cstring>

using namespace std;

int last[30], cnt[30];

int main()
{
	int tc ;
	int n;
	int i, j;
	int len;
	string str;

	cin >> tc;

	while(tc--){
		cin >> n;
		memset(last, 0, sizeof(last));

		cin >> str;
		len = str.length();
		for(j=0; j<len; j++){
			last[str[j]-'A']++;
		}

		for(i=0; i<n-1; i++){
			cin >> str;
			memset(cnt, 0, sizeof(cnt));
			len = str.length();
			for(j=0; j<len; j++){
				cnt[str[j]-'A']++;
			}
			for(j=0; j<30; j++){
				last[j] = last[j]<cnt[j]?last[j]:cnt[j];
			}
		}

		for(i=0; i<30; i++){
			for(j=0; j<last[i]; j++)
				cout << char(i+'A');
		}
		cout << endl;
	}

	return 0;
}






//    0s 	180
#include<stdio.h>
int main()
{
    int T,i,j,n,k;
    char str[30][100];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for (i=0;i<n;i++)
            scanf("%s",str[i]);
        for (i=1;i<n;i++)
            for (j=0;j<12;j++)
            {
                for (k=0;k<12;k++)
                  if(str[0][j]==str[i][k]) break;
                                if(k==12)
                     str[0][j]='#';//ÌÞ³ý
                    else str[i][k]='#';
            }
        for (i=65;i<=90;i++)//°´×ÖÄ¸Ë³ÐòÊä³ö
           for (j=0;j<12;j++)
          if(str[0][j]==i)
        printf("%c",i);
        printf("\n");
    }
    return 0;
}