//*  712K	282MS	C++	2258B
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

const int N = 20005;
int ch[N], height[N], rank[N], sa[N], cnt[N], wa[N], wb[N];
int n;

int cmp(int *x, int a, int b, int l){
	return (x[a]==x[b]) && (x[a+l]==x[b+l]);
}

void suffix(int *s, int n){
	// sa数组
	int *x = wa, *y = wb, *t;
	int i, j, p, k;

	memset(rank, 0, sizeof(rank));
	memset(height, 0, sizeof(height));
	memset(sa, 0, sizeof(sa));

	int mm = N;
	memset(cnt, 0, sizeof(cnt));
	for(i=0; i<n; i++)   cnt[x[i]=s[i]]++;
	for(i=1; i<mm; i++)   cnt[i] += cnt[i-1];
	for(i=n-1; i>=0; i--)  sa[--cnt[x[i]]] = i;

	for(j=1, p=1; p<n; mm=p, j*=2){
		for(p=0, i=n-j; i<n; i++)   y[p++] = i;
		for(i=0; i<n; i++)
			if(sa[i]>=j)   y[p++] = sa[i] - j;
		for(i=0; i<mm; i++)   cnt[i] = 0;
		for(i=0; i<n; i++)   cnt[x[y[i]]]++;
		for(i=1; i<mm; i++)   cnt[i] += cnt[i-1];
		for(i=n-1; i>=0; i--)   sa[--cnt[x[y[i]]]] = y[i];

		for(t=x, x=y, y=t, p=1, x[sa[0]]=0, i=1; i<n; i++)
			x[sa[i]] = cmp(y, sa[i], sa[i-1], j)?p-1:p++;
	}

	// rank数组
	for(i=0; i<n; i++){
		rank[sa[i]] = i;
	}

	// height数组
	/*
	k = 0;
	for(i=0; i<n; i++){
		if(rank[i]==0)   height[rank[i]] = k = 0;
		else{
			if(k>0)   k--;
			j = sa[rank[i]-1];
			while(s[i+k]==s[j+k])
				k++;
			height[rank[i]] = k;
		}
	}
	*/
	// 另一种height数组
	k = 0;
	for(i=0; i<n; height[rank[i++]]=k)
		for(k?k--:0, j=sa[rank[i]-1]; s[i+k]==s[j+k]; k++);
}


bool check(int mid)  // 判断某长度下是否存在这样的不重复子串。
{  
    int ll,rr;  
    for (int i = 1; i < n; i++)   // 不包括自己附加的元素
    {  
        if (height[i] < mid) ll = 0x1fffffff, rr = -0x1fffffff;  // 只要一断开，就复位。因为那些相同字符已经不是那些了。
        ll = ll > sa[i] ? sa[i]:ll;
        rr = rr < sa[i] ? sa[i]:rr;
        if (rr- ll >= mid) return true;
    }  
    return false;  
}  


int main()
{
	freopen("in.txt", "r", stdin);
	int i;
	int l, r, mid;
	int ans = 0;

	while(scanf("%d", &n) && n!=0){
		for(i=0; i<n; i++){
			scanf("%d", &ch[i]);
			if(i){
				//cout << ch[i] - ch[i-1] << " ";
				ch[i-1] = ch[i] - ch[i-1] + 200;
			}
		}
		//cout << endl;
		ch[n-1] = 0;
		
		if(n<10)
			printf("0\n");
		else{
			suffix(ch, n);
			for(l=0, r=n; l<r; ){
				if(check(mid=(l+r+1 >>1)))   l = mid;
				else   r = mid - 1;
			}
			l++;
			printf("%d\n", l>=5?l:0);
		}
	}

	return 0;
}
//*/







