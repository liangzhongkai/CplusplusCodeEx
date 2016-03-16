/*  7752K	969MS	C++	1011B
#include<iostream>
#include<vector>
#include<cstdio>

using namespace std;

const int N = 100000000;
const int prime = 99991;

int n, nc;
char str[N];

vector<int> hash[prime];

//int Hash(int a, int b){            Time Limit Exceeded
//	int ans = 1;
//	while(b--){
//		ans = (str[a++]%prime + ans*10%prime) % prime;
///	}
//	return ans;
//}

int ELFhash(int a, int b)
{
    unsigned int h = 0;
    while(b--){
        h = (h << 4) + str[a++];
        unsigned int g = h & 0xf0000000L;
        if (g) h ^= g >> 24;
        h &= ~g;
    }
    return h % prime;
}


bool is_same(int a, int b){
	int i;
	for(i=0; i<n; i++){
		if(str[a+i]!=str[b+i])
			return false;
	}
	return true;
}

int main()
{
	int t=0, i, j;
	int tmp, l, key;
	char ch;
	int ans = 0;
	scanf("%d%d", &n, &nc);
	getchar();

	scanf("%s", str);
	t = strlen(str);
	t++;

	for(i=0; i<t-n; i++){
		key = 0;
		tmp = ELFhash(i, n);
		
		l = hash[tmp].size();
		for(j=0; j<l; j++){
			if(is_same(i, hash[tmp][j])){
				key = 1;
				break;
			}
		}

		if(key==0){
			ans++;
			hash[tmp].push_back(i);
		}
	}

	printf("%d\n", ans);
		 
	return 0;
}
//*/



//*   20428K	47MS	C++	1199B

#include<stdlib.h>
//���⽫�ַ���ת��Ϊһ��nc���Ƶ���,�ж����
//���Ƿ��ظ����ּ���
#include<memory.h>
#include<stdio.h>
#include<iostream>

using namespace std;

#define MAX 20000000
bool c[MAX];
char x[MAX];

//����ĸת��Ϊ��Ӧ������,��Ϊ��ĸ���ܲ���������
//��nc = 3ʱ���ܻ���aeccc�����ַ���
//�����a,c,e�ֱ����0,1,2
int ascii[256];

int main()
{
	int i, j;
    int n,nc;
    while(scanf("%d%d\n",&n,&nc)!=EOF)
    {
        memset(c,0,sizeof(c));
        memset(ascii,0,sizeof(ascii));
        int tmp,res(0);
        scanf("%s",x);

        int len = strlen(x);
        //�����ֹ�����ĸ�����Ϊ-1(true)
        for( i = 0; i < len; i++)
            ascii[x[i]] = -1;

        int zz = 0;
        //Ϊ���ֹ�����ĸ��������
        for( i = 0; i < 256; i++)
            if(ascii[i])
                ascii[i] = zz++;

        bool flag;
        len = len - n + 1;
        for(i = 0; i < len; i++){
            flag = true;
            tmp = 0;
            //�����ַ���ת��Ϊnc������  ȷ�������г�ͻ
            for( j = 0; j < n; j++)
                tmp = tmp*nc + ascii[x[i+j]];
            tmp = abs(tmp)%MAX;
            if(!c[tmp]){
                res++;
                c[tmp] = true;
            }
        }
        printf("%d\n",res);
    }
    return 0;
}
//*/