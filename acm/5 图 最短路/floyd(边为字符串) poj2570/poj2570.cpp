//*  324K	141MS	C++	836B
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

#define MAXN 201

int main()
{
	int m[MAXN][MAXN];
	int n;
	int A, B;
	int i, j, k;
	char str[27];
	char ch;

	while(scanf("%d", &n) && n!=0){
		memset(m, 0, sizeof(m));

		while(scanf("%d %d", &A, &B)){
			if(A==0 && B==0)   break;
			scanf("%s", str);
			for(i=0; str[i]; i++){
				m[A][B] |= 1 << (str[i]-'a');
			}
		}

		for(k=1; k<=n; k++){
			for(i=1; i<=n; i++){
				for(j=1; j<=n; j++){
					m[i][j] |= m[i][k] & m[k][j];
				}
			}
		}

		while(scanf("%d %d", &A, &B)){
			if(A==0 && B==0	)   break;
			if(!m[A][B])   putchar('-');
			else{
				for(ch='a'; ch<='z'; ch++){
					if(m[A][B] & (1<<ch-'a')){
						putchar(ch);
					}
				}
			}
			putchar('\n');
		}
		putchar('\n');
	}

	return 0;
}
//*/