/*
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int MAXN = 510;
int father[MAXN], val[MAXN];
int A, B;
int cnt;
int mp[MAXN];

void init(){
	for(int i=0; i<MAXN; i++){
		father[i] = i;
		val[i] = 0;
	}
	cnt = 0;
	memset(mp, 0, sizeof(mp));
}

int Find(int a){
	if(father[a]!=a){
		int na = father[a];
		father[a] = Find(father[a]);
		val[a] = (val[a] + val[na]) % 3;
	}
	return father[a];
}

void Union(int a, int b, int c){
	father[A] = B;
	val[A] = (val[b] + c - val[a] + 6) % 3;
}

int main()
{
	int n, m;
	int i;
	int a, b, t;
	char ch;
	int vis[MAXN];

	while(scanf("%d%d", &n, &m)!=EOF){
		if(n==1 && m==0){
			printf("Player 0 can be determined to be the judge after 0 lines\n");
			continue;
		}

		init();
		memset(vis, 0, sizeof(vis));
		int count = 0;
		int key = 0;
		int flag = -1;

		for(i=0; i<m;  i++){
			scanf("%d%c%d", &a, &ch, &b);
			A = Find(a);
			B = Find(b);

			if(ch=='=')   t = 0;
			else if(ch=='<')   t = 1;
			else   t = 2;

			if(A==B){
				if(t==0 && val[a]==val[b])   continue;
				else if(t==1 && (val[a]==1&&val[b]==0 || val[a]==0&&val[b]==2 || val[a]==2&&val[b]==1))   continue;
				else if(t==2 && (val[b]==1&&val[a]==0 || val[b]==0&&val[a]==2 || val[b]==2&&val[a]==1))   continue;
				else{
					count++;
					if(count>2){
						if(a!=flag && b!=flag){
							key = 1;
							count--;
							continue;
						}
					}
					if(count==2){
						if(vis[a]==1)   flag = a;
						if(vis[b]==1)   flag = b;
						//cout << flag << endl;
					}
					mp[count] = i+1;
					vis[a]++;   vis[b]++;
				}
			}
			else{
				Union(a, b, t);
			}
		}

		int k = 0;
		if(count==0)   printf("Can not determine\n");
		else if(count==1)   printf("Impossible\n");
		else{
			for(i=0; i<n; i++){
				if(vis[i]==count){
					if(k==0){   k = 1; key = i; }
					else if(k==1){   k = 2;}
				}
			}
			if(k==1){
				printf("Player %d can be determined to be the judge after %d lines\n", key, mp[2]);
			}
			else{
				printf("Impossible\n");
			}
		}
	}

	return 0;
}
//*/




/*   188K	657MS	C++	1683B

#include <iostream>
#include<cstring>
#include<cstdio>

using namespace std;
 
 #define MAXN 501
 #define MAXM 2001
 int root[MAXN],relation[MAXN],x[MAXM],y[MAXM],sa[MAXN];
 char cmp[MAXM];

 int findroot(int x)
 {
     int t;
     if(root[x]!=x)
     {
         t=root[x];root[x]=findroot(root[x]);
         relation[x]=(relation[x]+relation[t])%3;
     }
     return root[x];
 }
 
 bool IsTrue(int x, int y, int d)
 {
     int a, b;
     a = findroot(x);
     b = findroot(y);
     if(a==b)
         return (3+relation[x]-relation[y])%3==d ? true : false;
     else
         root[b] = a,   relation[b] = (6 - d + relation[x] - relation[y]) % 3;
     return true;
 }
 
 int main()
 {
     int i,N,M,judge,r,t,ansP,ansS;
     while (scanf("%d %d",&N, &M)==2)
     {
         memset(sa,0,sizeof(sa));
         for(i=0;i<M;i++)
			 scanf("%d %c %d",&x[i],&cmp[i],&y[i]);

         for(judge=0;judge<N;judge++){
             for(i=0;i<N;i++){
				 root[i]=i,   relation[i]=0;
			 }
             for(i=0;i<M;i++){
                 if(x[i]==judge||y[i]==judge)continue;    // 如果你把judge有关的边都考虑，可能会影响以后那些非judge的边的关系

                 if(cmp[i]=='=')r=0;
                 else if(cmp[i]=='>')r=1;
                 else r=2;

                 if(!IsTrue(x[i],y[i],r)){ sa[judge]=i+1; break; }   // 除这个judge之外，其他都不能出现错误关系，否则judge就不唯一
             }
         }

         for(ansS=i=t=0;i<N;i++){
             if(sa[i]==0)t++,ansP=i;
             if(sa[i]>ansS)ansS=sa[i];     // 能确认judge的时候
         }

         if(t==0)printf("Impossible\n");
         else if(t>1)printf("Can not determine\n");
         else printf("Player %d can be determined to be the judge after %d lines\n",ansP,ansS);
     }
     return 0;
 }
 //*/