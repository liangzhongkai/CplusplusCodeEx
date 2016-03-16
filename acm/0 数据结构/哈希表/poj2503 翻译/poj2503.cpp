/*
将字典和查询合并之后qsort一次，O((m+n)*log(m+n))
3679201 scat 2503 Accepted 6108K 891MS C++ 994B 2008-07-19 19:09:29 

将字典qsort，每次查询时bsearch，O((m+n)logm)
2878665 scat 2503 Accepted 2356K 343MS GCC 220B 2007-11-07 12:54:56 

TRIE，O(m*len+n*len)
2798315 scat 2503 Accepted 13512K 125MS C 973B 2007-10-18 02:10:12 

hash
2799032 scat 2503 Accepted 3600K 156MS C 1323B 2007-10-18 12:13:08 

map
3635793 scat 2503 Accepted 15428K 1860MS G++ 259B 2008-07-14 22:00:57 
*/
/*
#include<iostream>
#include<string>
#include<map>
#include<cstdio>
#include<cstring>

using namespace std;

map<string, int> mp;
char str2[100010][12];

int main()
{
	int i, key, j;
	string str1 = "" ;
	char ch[30];
	int cnt = 1;

	//scanf("%s", ch);
	//str1 = ch;
	//printf(str1.c_str());

	while(gets(ch) && ch[0]!='\0'){
		key = 0;
		str1 = "";
		j = 0;
		for(i=0; i<strlen(ch); i++){
			if(ch[i]==' ')   key = 1, i++;
			if(key)   str1 += ch[i];
			else if(key==0)   str2[cnt][j++] = ch[i];
		}
		str2[cnt][j] = '\0';
		mp[str1] = cnt++;
	}

	while(scanf("%s", ch)){
		str1 = ch;
		int kk = mp[str1];
		if(kk>0){
			printf("%s\n", str2[kk]);
		}
		else
			printf("eh\n");
	}

	return 0;
}
///*/





/*   9088K	938MS	C++	768B
#include <iostream>
#include <string>
#include <map>

using namespace std;

string s;
map<string,int> in;

int main()
{
	in.clear();
	int i=0,num=0;

	char out[100010][12];
	char a[12],b[12],c[12];
	char ch=getchar();

	while(ch!='\n')
	{
		int j=0;
		while(ch>='a' && ch<='z')
		{
			a[j++]=ch;
			ch=getchar();
		}
		a[j]='\0';

		while(ch>'z' || ch<'a')
			ch=getchar();

		j=0;
		while(ch>='a' && ch<='z')
		{
			b[j++]=ch;
			ch=getchar();
		}
		b[j]='\0';//每个数组的结束符

		num++;
		s=b;
		in[s]=num;
		strcpy(out[num],a);
		//while(ch!='\n') ch=getchar();
		ch=getchar();
		i++;
	}

	while(scanf("%s",c)!=EOF)
	{
		s=c;
		i=in[s];
		if(i>0)
		printf("%s\n",out[i]);
		else
		printf("eh\n");
	}

	return 0;
}
*/


/*         3876K	172MS	C++	1013B
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct aa
{
	char word[13];
	char foreign[13];
}dic[100010];
int hash[300000];
int main()
{
	int i,j,n;
	int getf;
	int rt;
	char line[30];
	gets(line);
	n=0;
	for(i=0;i<300000;i++)
		hash[i]=-1;
	while(line[0]!='\0')
	{
		for(i=0;line[i]!=' ';i++)
			dic[n].word[i]=line[i];
		dic[n].word[i++]='\0';
		for(i,j=0;line[i]!='\0';i++,j++)
			dic[n].foreign[j]=line[i];
		dic[n].foreign[j]='\0';
		getf=0;
		i=0;
		while(dic[n].foreign[i]!='\0')
		{
			getf=getf*26+dic[n].foreign[i++];
			getf%=300000;
		}
		while(hash[getf]!=-1)
			getf=(getf+1)%300000;
		hash[getf]=n;
		n++;
		gets(line);
	}
	while(gets(line))
	{
		getf=0;i=0;
		while(line[i]!='\0')
		{
			getf=getf*26+line[i++];
			getf%=300000;
		}
		while(hash[getf]!=-1 && strcmp(dic[hash[getf]].foreign,line)!=0)
			getf=(getf+1)%300000;
		if(hash[getf]!=-1)
			printf("%s\n",dic[hash[getf]].word);
		else
			printf("eh\n");
	}
	return 0;
}
	
*/


//    3484K	532MS	C++	1577B    BKDRHash()
//    3448K	547MS	C++	1577B    ELFhash()
//    3516K	610MS	C++	1496B    Hash()
#include<iostream>
#include<vector>
#include<cstdio>

using namespace std;

const int N = 9997;

char str1[100001][12], str2[100001][12];
/*
int ELFhash(char * key)
{
    unsigned int h = 0;
    while (*key){
        h = (h << 4) + *key++;
        unsigned int g = h & 0xf0000000L;
        if (g) h ^= g >> 24;
        h &= ~g;
    }
    return h % N;
}
*/

int Hash(char *s){
    int key=1;
    while(*s)   key=(key*29+(*s++)-'a')%N;
    return key;
}



vector<int> vec[N+1];

int main()
{
	char str[12];
	char ch;
	int ct = 0; 
	int cnt = 0, i;
	ch=getchar();

	while(ch!='\n'){
		cnt = 0;
		for(i=0; i<15; i++){     // 开头10次害我wa了不少次！！！！！！！！！！！
			if(ch<'a' || ch>'z')   break;
			str1[ct][cnt++] = ch;
			ch = getchar();
		}
		str1[ct][cnt] = '\0';
		//printf("%s\n", str1[ct]);

		cnt = 0;
		for(i=0; i<15; i++){
			ch = getchar();
			if(ch<'a' || ch>'z')   break;
			str2[ct][cnt++] = ch;
		}
		str2[ct][cnt] = '\0';
		//printf("%s\n", str2[ct]);

		cnt = Hash(str2[ct]);
		
		//printf("%d\n", cnt);
		vec[cnt].push_back(ct++);

		ch=getchar();
	}

	cnt = 0;
	int key, k=0;
	while(scanf("%s", str)!=EOF){
		key = 0;
		cnt = Hash(str);
		//printf("%s", str);
		//printf("%d\n", cnt);
		for(i=0; i<vec[cnt].size(); i++){
			k = vec[cnt][i];
			//printf("%d\n", k);
			if(strcmp(str, str2[k])==0){
				printf("%s\n", str1[k]);  key = 1;
				break;
			}
		}
		if(key==0)
			printf("eh\n");
	}

	return 0;
}


/*
第一种解法，直接了当的C++ map 水过去

#include<cstdio>
#include<map>
#include<cstring>
using namespace std;
struct word
{
	char data[13];
	bool operator<(const word& other)const
	{
		return strcmp(data,other.data)==-1;
	}
};
map<word,word> dic;
map<word,word>::iterator it;
word english,foreign;

int main()
{
	while(true)
	{
		char ch=getchar();
		if(ch=='\n')
		break;
		int len=-1;
		while(ch!=' ')
		{
			english.data[++len]=ch;
			ch=getchar();
		}
		english.data[++len]=0;
		len=-1;
		ch=getchar();
		while(ch!='\n')
		{
			foreign.data[++len]=ch;
			ch=getchar();
		}             
		foreign.data[++len]=0;
		dic[foreign]=english;
		// printf("%s %s\n",foreign.data,english.data);
	}

	while(scanf("%s",foreign.data)!=EOF)
	{
		it=dic.find(foreign);
		if(it==dic.end())   printf("eh\n");
		else   printf("%s\n",it->second.data);
	}

	return 0;
}

第二种解法,半hash，主要是排序加二分查找

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct one
{
	int i;
	unsigned __int64 hash;
	bool operator<(const one &other)const
	{
		return hash<other.hash;
	}
};
one hash[100010];
char english[100010][12];
//char foreign[100010][12];

unsigned __int64 hashValue(char *str)
{
	int h=0;
	while(*str)   h=h*27+(*str++)-'a'+1;
	return h; 
}

bool myget(char *str)
{
	char ch=getchar();
	if(ch==' '||ch=='\n'||ch==EOF)
	return false;
	while(ch!=' '&&ch!='\n')
	{
		*str++=ch;
		ch=getchar();
	}
	*str=0;
	return true;
}

int main()
{
	int i=0;
	char foreign[12];
	while(myget(&english[i][0]))
	{
		myget(&foreign[0]);
		hash[i].hash=hashValue(foreign);
		hash[i].i=i;
		++i;
	}
	sort(hash,hash+i);
	char forei[13];
	while(myget(forei))
	{
		one h;
		h.hash=hashValue(forei);
		int pos=lower_bound(hash,hash+i,h)-hash;

		if(pos==i||hash[pos].hash!=h.hash)
			printf("eh\n");
		else
			printf("%s\n",english[hash[pos].i]);
	}
	return 0;
}

第三种解法， 纯hash

#include<cstdio>
#include<cstring>

int hash[1001][1001];
char english[100010][12];
char foreign[100010][12];

void setHash(int i)
{
     int h=0;
     for(int j=0;foreign[i][j]!=0;++j)
        h=(h*26+(foreign[i][j]-'a'))%1001;
     h=h%1001;
     int j=0;
     while(hash[h][j]!=0)
          ++j;
     hash[h][j]=i;
}

int myHash(char *str)
{
    char *buf=str;
    int h=0;
    for(int j=0;*str!=0;++str)
       h=(h*26+(*str-'a'))%1001;
    h=h%1001;
    int j=0;
    while(hash[h][j]!=0&&strcmp(buf,&foreign[(hash[h][j])][0])!=0)
       ++j;
    return hash[h][j];
}

bool myget(char *str)
{
     char ch=getchar();
     if(ch==' '||ch=='\n'||ch==EOF)
       return false;
     while(ch!=' '&&ch!='\n')
     {
           *str++=ch;
           ch=getchar();
     }
     *str=0;
     return true;
}

char forei[13];

int main()
{
    int i=1;
    while(myget(&english[i][0]))
    {
         myget(&foreign[i][0]);
         setHash(i);
         ++i;
    }
    while(myget(forei))
    {
         int h=myHash(forei);
         if(h==0)
           printf("eh\n");
         else
           printf("%s\n",english[h]);
    }
    return 0;
}

第四种解法 trie tree

#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int index[1000100][26];
int length=0;
int value[1000100];
char english[100020][12];

inline bool myget(char *str)
{
     char ch=getchar();
     if(ch==' '||ch=='\n'||ch==EOF)
       return false;
     while(ch!=' '&&ch!='\n')
     {
           *str++=ch;
           ch=getchar();
     }
     *str=0;
     return true;
}

int main()
{
    int i=1;
    char foreign[12];
    while(myget(&english[i][0]))
    {
         myget(&foreign[0]);
         
         int j=0,start=0;
         while(foreign[j]!=0)
         {
               int next=foreign[j]-'a';
               if(index[start][next]==0)
                  index[start][next]=++length;
               start=index[start][next];
               ++j;
         }
         value[start]=i;
         ++i;
    }

    char forei[12];
    while(myget(forei))
    {
         int j=0,start=0;
         while(forei[j]!=0)
         {
               int next=forei[j]-'a';
               start=index[start][next];
               ++j;
         }
         
         start=value[start]; 
         if(start==0)
           printf("eh\n");
         else
           printf("%s\n",english[start]);
    }
    return 0;
}
*/