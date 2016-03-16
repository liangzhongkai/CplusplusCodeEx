//*      248K	32MS
#include<iostream>

using namespace std;

int p, q, a, n;
int ans;

int comp(int restp, int restq, int p, int q)
{
	return (restp * q) - (restq * p);
}

void sub( int &nextp, int &nextq, int q )
{
	nextp = nextp * q - nextq;
	nextq = nextq * q;
}

void dfs( int lastq, int restp, int restq, int restmul, int d )
{
	if( d>n+1 )
		return;
	if( d<=n+1 && restp==0 )
	{
		ans++;
		return;
	}

    int nextp, nextq;
	for(int i=lastq; i<=restmul; i++ )
	{
		if(comp(restp, restq, 1, i)<0)
			continue;

		nextp = restp;
		nextq = restq;
		sub( nextp, nextq, i );

		if( comp(nextp, nextq, n-d, i)>0 )
			break;

		dfs( i, nextp, nextq, restmul/i, d+1 );
	}

}

int main()
{
	while( cin >> p >> q >> a >> n && p && q && a && n )
	{
		ans = 0;
		dfs( 1, p, q, a, 1 );
		cout << ans << endl;
	}

	return 0;
}
//*/




/*                      164K	47MS    
#include<iostream>

#include<cstdio>
#include<cmath>

using namespace std;

int p, q, a, n, tot;    //如题目定义，tot为答案

//p1/q1 和 p2/q2 比较大小
int inline frac_cmp(int p1, int q1, int p2,  int q2)
{
    return p1 * q2 - p2 * q1;
}

//int inline gcd(int a, int b){
//    if(b == 0) return a;
//    return gcd(b, a % b);
//}

// p/q - 1/d  答案保存在 p/q中
void inline frac_sub(int &p, int &q, int d){
    p = p * d - q;
    q = q * d;

    //可以不约分，节省时间（600ms -> 63ms）
//    if(p != 0){
//        int g = gcd(p, q);
//        p = p / g; q = q / g;
//    }
}

//last_d上一层的分母。。left_p剩下的分数的分子。。left_q剩下的分数的分母。。num层数。。left_a剩下的分母的最大乘积
void dfs(int last_d, int left_p, int left_q, int num, int left_a)
{
    int next_p, next_q;

    if(num > n+1 )
		return;    //if(num == n+1 && left_p!=0 ) return;
    if(num <= n+1 && left_p == 0)
	{
        tot++; return;
    }

//    if(frac_cmp(left_p, left_q, n-num+1, last_d) > 0) return;    //剩下的分数太大(后面会判断，可略)

    for(int d=last_d; d<=left_a; d++)
	{
        if(frac_cmp(left_p, left_q, 1, d) < 0)
			continue;    // 1/d太大

		next_p = left_p;
		next_q = left_q;
        frac_sub(next_p, next_q, d);        //求得next_p, next_q
		

        if(frac_cmp(next_p, next_q, n-num, d) > 0)
			break;    //剩给下一层的分数太大

        dfs(d, next_p, next_q, num+1, left_a / d);
    }

}


int main()
{
    while(scanf("%d %d %d %d", &p, &q, &a, &n))
	{
        if(p==0) return 0;

        tot = 0;
        dfs(1, p, q, 1, a);
        printf("%d\n", tot);

    }

    return 0;
}

  */