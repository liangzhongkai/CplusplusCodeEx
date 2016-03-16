//*    120K	0MS	C++	1036B
#include<iostream>
#include<cstring>
#include<string>

using namespace std;

int readLine(char *s){
	int L;
	for(L=0; (s[L]=getchar())!='\n' && s[L]!=EOF; L++)
		;
	s[L] = 0;
	return L;
}

int main()
{
	int i, j;
	char buf[128];
	int N, M;
	int door[20];

	while(readLine(buf)){
		if(buf[0]=='S'){
			sscanf(buf, "%*s %d %d", &M, &N);

			memset(door, 0, sizeof(door));

			int doors = 0;

			for(i=0; i<N; i++){
				readLine(buf);
				int k = 0;

				while(sscanf(buf+k, "%d", &j)==1){
					//cout << buf[k] << endl;
					doors++;
					door[i]++,   door[j]++;
					while(buf[k] && buf[k]==' ')   k++;
					while(buf[k] && buf[k]!=' ')   k++;
				}
			}

			readLine(buf);
			int odd = 0, even = 0;
			for(i=0; i<N; i++){
				if(door[i]&1)   odd++;
				else even++;
			}
			if(odd == 0 && M == 0)   printf("YES %d\n", doors);
			else if(odd==2 && door[M]%2==1 && door[0]%2==1 && M!=0)
				printf("YES %d\n", doors);
			else   printf("NO\n");
		}
		else if(!strcmp(buf, "ENDOFINPUT"))
			break;
	}

	return 0;
}