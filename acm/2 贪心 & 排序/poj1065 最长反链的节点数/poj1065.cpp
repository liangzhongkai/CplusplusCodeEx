/*   296K	32MS	C++	724B
#include<iostream>
#include<algorithm>

using namespace std;

struct point{
	int x, y;
}mp[5005];

bool vis[5005];

bool cmp(const point &a, const point &b){
	if(a.x==b.x)
		return a.y<b.y;
	return a.x<b.x;
}

int main()
{
	int tc;
	int n;
	int i, j;

	cin >> tc;

	while(tc--){
		cin >> n;
		for(i=0; i<n; i++){
			cin >> mp[i].x >> mp[i].y ;
		}

		sort(mp, mp+n, cmp);

		memset(vis, false, sizeof(vis));
		int ans = 0;
		int k = 0;
		for(i=0; i<n; i++){
			if(!vis[i]){
				ans++;
				k = i;
				// 最长非递减子序列
				for(j=i+1; j<n; j++){
					if(!vis[j] && mp[j].y>=mp[k].y){
						vis[j] = true;
						k = j;
					}
				}
			}
		}
		cout << ans << endl;
	}

	return 0;
}
//*/

//    求最长的那条链的节点个数
//    212K	0MS	C++	1041B
#include <stdio.h>
#include <algorithm>
using namespace std;

int a,b,len,k[5000];

struct node
{
    int l,w;
}m[5000];

bool cmp(node a,node b)
{
    if(a.l==b.l) return a.w<b.w;//@
    else return a.l<b.l;
}

int search(int key)   //  二分法求出递减序列中的第一个<=目标的下标
{
    int p=0,q=len,t;
    while(p<q)
    {
        t=(q+p)>>1;
        if(k[t]==key) return t;
        else if(k[t]<key) q=t;    // 这里有些特别：如果是q = t - 1 Wrong Answer
        else p=t+1;
    }
    return p;
}

int f()    // 求最长反链的长度，即最长递减子序列
{
    k[0]=m[0].w;
    len=0;
    for(int i=1,t;i<b;++i)
    {
        t=search(m[i].w);      // 一是找到与m[i].w相等的k[]的下标，一是刚好比它小的下标   k数组为降序
        if(k[t]>m[i].w)
            k[++len]=m[i].w;   // 后续插入  因为m[i].w比k数组里任一个都要小
        else
            k[t]=m[i].w;       // 更新中间的节点   取代<=m[i].w的第一个！
    }
    return len+1;
}

int main()
{
    scanf("%d",&a);
    for(int i=0;i<a;++i)
    {
        scanf("%d",&b);
        for(int j=0;j<b;++j)
            scanf("%d %d",&m[j].l,&m[j].w);
        sort(m,m+b,cmp);
        printf("%d\n",f());
    }
    return 0;
}