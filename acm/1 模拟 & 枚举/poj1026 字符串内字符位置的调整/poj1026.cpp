
/*  Time Limit Exceeded
#include<iostream>
#include<string>
#include<cstring>

using namespace std;

int a[205];
int n;
char st[205];

void change(char *s){
	memset(st,0x00,sizeof(st));
	int i;
	for(i=0; i<n; i++){
		st[a[i]-1] = s[i];
	}
	st[n] = '\0';
	strcpy(s, st);
}

int main()
{	
	int i;
	int num;
	int len;
	char str[205];

	while(cin >> n && n!=0){
		for(i=0; i<n; i++){
			cin >> a[i];
		}

		while(cin >> num && num!=0){
			getchar();
			gets(str);
			//printf("%s", str);

			len = strlen(str);
			if(len<n){
				for(i=len; i<n; i++)
					str[i] = ' ';
			}
			str[n] = '\0';
			//printf("%s", str);

			while(num--)
				change(str);
			printf("%s\n", str);
		}
		printf("\n");
		
	}


	return 0;
}

//*/

//  244K	110MS	C++	1918B
#include<iostream>
#include<string>
#include<cstring>

using namespace std;

int a[205];
int Time[205];
int n;
bool vis[205];

int change(int n, int T){
	if(vis[n]){
		return T;
	}
	else{
		vis[n] = true;
		int t;
		t = change(a[n], T+1);
		Time[n] = t;
		return t;
	}
}

int main()
{	
	int i;
	int num;
	int len;
	char str[205], st[205];

	while(cin >> n && n!=0){
		for(i=1; i<=n; i++){
			cin >> a[i];
		}
		memset(vis, false, sizeof(vis));
		memset(Time, 0, sizeof(Time));
		for(i=1; i<=n; i++){
			if(!vis[i]){
				change(i, 0);
			}
		}
		
		//for(i=1; i<=n; i++){
		//	cout << Time[i] << " ";
		//}
		//cout << endl;
		
		while(cin >> num && num!=0){
			getchar();
			gets(str);
			//printf("%s\n", str);

			len = strlen(str);
			if(len<n){
				for(i=len; i<n; i++)
					str[i] = ' ';
			}
			str[n] = '\0';
			//printf("%s\n", str);

			for(i=1; i<=n; i++){
				int l = num % Time[i];
				int aa = i;
				while(l--){
					aa = a[aa];
				}
				st[aa-1] = str[i-1];
			}
			st[n] = '\0';
			strcpy(str, st);
			printf("%s\n", str);
		}
		printf("\n");
		
	}


	return 0;
}