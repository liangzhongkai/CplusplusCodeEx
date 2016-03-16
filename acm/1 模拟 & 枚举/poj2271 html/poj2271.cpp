//  164K	0MS	C++	812B
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>

using namespace std;

int main()
{
	//freopen("data.txt", "r", stdin);
	int sum = 0, len;
	char str[85];
	char b[5] = {'<','b','r','>','\0'};
	char h[5] = {'<','h','r','>','\0'};

	while(scanf("%s", str)!=EOF){
		if(strcmp(str, b)==0){
			printf("\n");
			sum = 0;
		}
		else if(strcmp(str, h)==0){
			if(sum!=0)
				printf("\n");
			printf("--------------------------------------------------------------------------------\n");
			sum = 0;
		}
		else{
			len = strlen(str);
			if(sum==0){
				printf("%s", str);
				sum = len;
			}
			else if(sum<80-len){
				printf(" %s", str);
				sum += len + 1;
			}
			else{
				printf("\n");
				printf("%s", str);
				sum = len;
			}
		}
	}

	return 0;
}


