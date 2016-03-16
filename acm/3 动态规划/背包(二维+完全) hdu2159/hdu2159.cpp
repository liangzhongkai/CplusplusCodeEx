//     15MS	296K	685 B	C++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;
int dp[N][N];
int n, m, k, s;

void completepack(int v, int c){
    for(int i=c; i<=m; i++){
        for(int j=s; j>0; j--){    //  0->s 可以，s->0 也可以！
            dp[i][j] = max( dp[i][j],  dp[i-c][j-1]+v);
        }
    }
}

int main()
{
    int i, a, b;
    while(scanf("%d %d %d %d", &n, &m, &k, &s)!=EOF){
        memset(dp, 0, sizeof(dp));
        for(i=0; i<k; i++){
            scanf("%d %d", &a, &b);
            completepack(a, b);
        }
        int flag = 0;
        for(i=0; i<=m; i++){
            if(dp[i][s]>=n){
                printf("%d\n", m-i);
                flag = 1;
                break;
            }
        }
        if(flag==0) 
            printf("-1\n");
    }
	
    return 0;
}



/*    0MS	288K	841 B	C++
#include <stdio.h>
#include <string.h>
int Max(int a,int b){
return a>b?a:b;
}
int main(){
int n,m,t,s,i,j,k,sum;
int f[105][105],weight[105],value[105];
while(scanf("%d%d%d%d",&n,&m,&t,&s)!=EOF){
sum = -1;
for( i = 1 ; i <= t ; i++){
scanf("%d%d",&value[i],&weight[i]);
}
memset(f,0,sizeof(f));
for( i = 1 ; i <= m ; i++){
for( j = 1 ; j <= t ; j++){
for( k = 1 ; k <= s ; k++){
if( i >= weight[j] ){
f[i][k] = Max(f[i][k] , f[i-weight[j]][k-1] + value[j]);
}
}
}
if( f[i][s] >= n ){
sum = m - i ;
break;
}
}
printf("%d\n",sum);
}
return 0;
}
//*/
