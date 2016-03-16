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
				// ��ǵݼ�������
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

//    ������������Ľڵ����
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

int search(int key)   //  ���ַ�����ݼ������еĵ�һ��<=Ŀ����±�
{
    int p=0,q=len,t;
    while(p<q)
    {
        t=(q+p)>>1;
        if(k[t]==key) return t;
        else if(k[t]<key) q=t;    // ������Щ�ر������q = t - 1 Wrong Answer
        else p=t+1;
    }
    return p;
}

int f()    // ��������ĳ��ȣ�����ݼ�������
{
    k[0]=m[0].w;
    len=0;
    for(int i=1,t;i<b;++i)
    {
        t=search(m[i].w);      // һ���ҵ���m[i].w��ȵ�k[]���±꣬һ�Ǹպñ���С���±�   k����Ϊ����
        if(k[t]>m[i].w)
            k[++len]=m[i].w;   // ��������  ��Ϊm[i].w��k��������һ����ҪС
        else
            k[t]=m[i].w;       // �����м�Ľڵ�   ȡ��<=m[i].w�ĵ�һ����
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