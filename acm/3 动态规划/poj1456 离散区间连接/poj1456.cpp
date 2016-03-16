

//*  284K	782MS	C++	816B      排序 + DP
#include <cstdio>
#include <algorithm>
#include <memory.h>

using namespace std;

#define max(a, b) ((a)>(b)?(a):(b))

struct node{
    int d,p;
} all[10010];

int value[10010];

bool g(node a,node b){
    return a.d<b.d;
}

int main(void)
{
    int n,i,j;
    while (scanf("%d",&n)!=EOF){
        for ( i=0; i<n; i++)
            scanf("%d%d",&all[i].p,&all[i].d);
		
		memset(value,0,sizeof(value)); 
		sort(all,all+n,g);                // 截止时间从小到大
		int upper=all[n-1].d;

        for ( i=0; i<n; i++){
            for ( j=all[i].d; j>0; j--)
                if (value[j]<value[j-1]+all[i].p)
                    value[j] = value[j-1] + all[i].p;

            for ( j=all[i].d+1; j<=upper; j++)
                value[j] = max(value[j], value[j-1]);
        }

        printf("%d\n",value[upper]);
    }
    return 0;
}
//*/
