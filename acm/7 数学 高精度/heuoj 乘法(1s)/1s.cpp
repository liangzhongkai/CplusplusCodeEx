//   477MS 	720K 	1361B 	KCT     when MAX is equal to 1000
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

#define MAX 1000
#define mod 10000
#define baselen 4
#define in(a) scanf("%d", &a)
#define out1(a) printf("%d", a)
#define out2(a) printf("%04d", a)
typedef int type;

struct bint{
	type dig[MAX], len;
	bint(){
		len = 0, dig[0] = 0;
	}
};

void by(bint a, bint b, bint &c){
	type i, j, carry;
	for(i=a.len+b.len+1; i>=0; i--)   c.dig[i] = 0;
	for(i=0; i<=a.len; i++){
		carry = 0;
		for(j=0; j<=b.len||carry; j++){
			carry += c.dig[i+j];
			if(j<=b.len) carry += a.dig[i] * b.dig[j];
			c.dig[i+j] = carry % mod;
			carry /= mod;
		}
	}
	i = a.len + b.len + 1;
	while(i && c.dig[i]==0)   i--;
	c.len = i;
}

bool input(bint &a){
	type i, j, w, k, p;
	char data[MAX*baselen+1];
	if(scanf("%s", data)==EOF)   return false;
	w = strlen(data) - 1, a.len = 0;
	for(p=0; p<=w&&data[p]=='0'; p++);
	while(1){
		i = j = 0, k = 1;
		while(i<baselen && w>=p){
			j = j + (data[w--] - '0') * k;
			k *= 10, i++;
		}
		a.dig[a.len++] = j;
		if(w<p)   break;
	}
	a.len--;
	return true;
}

void output(bint &a){
	type i;
	i = a.len - 1;
	out1(a.dig[a.len]);
	while(i>=0)   out2(a.dig[i--]);
}

int main()
{
	bint a, b, ans;

	while(input(a)){
		input(b);
		by(a, b, ans);
		output(ans);
		printf("\n");
	}
	return 0;
}












/*      520MS 	720K 	2109B 	
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int base = 10000; // (base^2) fit into int
const int width = 4; // width = log base
const int N = 1000; // n * width: 可表示的最大位数

struct bint{
	int ln, v[N];
	bint (int r = 0) { // r应该是字符串！
		for (ln = 0; r > 0; r /= base) v[ln++] = r % base;
	}
	bint& operator = (const bint& r) {
		memcpy(this, &r, (r.ln + 1) * sizeof(int)); // !
		return *this;
	}
} ;

bool operator < (const bint& a, const bint& b){
	int i;
	if (a.ln != b.ln) return a.ln < b.ln;
	for (i = a.ln - 1; i >= 0 && a.v[i] == b.v[i]; i--);
	return i < 0 ? 0 : a.v[i] < b.v[i];
}

bool operator <= (const bint& a, const bint& b){
	return !(b < a);
}

bint operator * (const bint& a, const bint& b){
	bint res; res.ln = 0;
	if (0 == b.ln) { res.v[0] = 0; return res; }
	int i, j, cy;
	for (i = 0; i < a.ln; i++) {
		for (j=cy=0; j < b.ln || cy > 0; j++, cy/= base) {
			if (j < b.ln) 
				cy += a.v[i] * b.v[j];
			if (i + j < res.ln) 
				cy += res.v[i + j];
			if (i + j >= res.ln) 
				res.v[res.ln++] = cy % base;
			else 
				res.v[i + j] = cy % base;
		}
	}
	return res;
}

int digits(bint& a) // 返回位数
{
	if (a.ln == 0) return 0;
	int l = ( a.ln - 1 ) * 4;
	for (int t = a.v[a.ln - 1]; t; ++l, t/=10) ;
	return l;
}

bool read(bint& b, char buf[]) // 读取失败返回0
{
	if (1 != scanf("%s", buf)) return 0;
	int w, u, ln = strlen(buf);
	memset(&b, 0, sizeof(bint));
	if ('0' == buf[0] && 0 == buf[1]) return 1;
	for (w = 1, u = 0; ln; ) {
		u += (buf[--ln] - '0') * w;
		if (w * 10 == base) {
			b.v[b.ln++] = u; u = 0; w = 1;
		}
		else w *= 10;
	}
	if (w != 1) b.v[b.ln++] = u;
	return 1;
}

void write(const bint& v){
	int i;
	printf("%d", v.ln == 0 ? 0 : v.v[v.ln - 1]);
	for (i = v.ln - 2; i >= 0; i--)
		printf("%04d", v.v[i]); // ! 4 == width
	printf("\n");
}

const int maxn = 1000;

int main()
{
	char str1[maxn],str2[maxn];
	bint a,b,c;
	while(read(a,str1))
	{
		read(b,str2);
		//getchar();
		c=operator * (a, b);
		write(c);
	}
	return 0;
}
//*/
/*
2
3
3
4
*/



/*   翅膀哥的模板
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define N 200005
#define pi acos(-1.0) // PI值
using namespace std;
struct complex
{
    double r,i;
    complex(double real=0.0,double image=0.0){
        r=real; i=image;
    }
    // 以下为三种虚数运算的定义
    complex operator + (const complex o){
        return complex(r+o.r,i+o.i);
    }
    complex operator - (const complex o){
        return complex(r-o.r,i-o.i);
    }
    complex operator * (const complex o){
        return complex(r*o.r-i*o.i,r*o.i+i*o.r);
    }
}x1[N],x2[N];
char a[N/2],b[N/2];
int sum[N]; // 结果存在sum里
void brc(complex *y,int l) // 二进制平摊反转置换 O(logn)
{
    register int i,j,k;
    for(i=1,j=l/2;i<l-1;i++)
    {
        if(i<j)  swap(y[i],y[j]); // 交换互为下标反转的元素
                                // i<j保证只交换一次
        k=l/2;
        while(j>=k) // 由最高位检索，遇1变0，遇0变1，跳出
        {
            j-=k;
            k/=2;
        }
        if(j<k)  j+=k;
    }
}
void fft(complex *y,int l,double on) // FFT O(nlogn)
                            // 其中on==1时为DFT，on==-1为IDFT
{
    register int h,i,j,k;
    complex u,t;
    brc(y,l); // 调用反转置换
    for(h=2;h<=l;h<<=1) // 控制层数
    {
        // 初始化单位复根
        complex wn(cos(on*2*pi/h),sin(on*2*pi/h));
        for(j=0;j<l;j+=h) // 控制起始下标
        {
            complex w(1,0); // 初始化螺旋因子
            for(k=j;k<j+h/2;k++) // 配对
            {
                u=y[k];
                t=w*y[k+h/2];
                y[k]=u+t;
                y[k+h/2]=u-t;
                w=w*wn; // 更新螺旋因子
            } // 据说上面的操作叫蝴蝶操作…
        }
    }
    if(on==-1)  for(i=0;i<l;i++) y[i].r/=l; // IDFT
}
int main(void)
{
    int l1,l2,l;
    register int i;
    while(scanf("%s%s",a,b)!=EOF)
    {
        l1=strlen(a);
        l2=strlen(b);
        l=1;
        while(l<l1*2 || l<l2*2)   l<<=1; // 将次数界变成2^n
                                        // 配合二分与反转置换
        for(i=0;i<l1;i++) // 倒置存入
        {
            x1[i].r=a[l1-i-1]-'0';
            x1[i].i=0.0;
        }
        for(;i<l;i++)    x1[i].r=x1[i].i=0.0;
        // 将多余次数界初始化为0
        for(i=0;i<l2;i++)
        {
            x2[i].r=b[l2-i-1]-'0';
            x2[i].i=0.0;
        }
        for(;i<l;i++)    x2[i].r=x2[i].i=0.0;
        fft(x1,l,1); // DFT(a)
        fft(x2,l,1); // DFT(b)
        for(i=0;i<l;i++) x1[i]=x1[i]*x2[i]; // 点乘结果存入a
        fft(x1,l,-1); // IDFT(a*b)
        for(i=0;i<l;i++) sum[i]=x1[i].r+0.5; // 四舍五入
        for(i=0;i<l;i++) // 进位
        {
            sum[i+1]+=sum[i]/10;
            sum[i]%=10;
        }
        l=l1+l2-1;
        while(sum[l]<=0 && l>0)   l--; // 检索最高位
        for(i=l;i>=0;i--)    putchar(sum[i]+'0'); // 倒序输出
        putchar('\n');
    }
    return 0;
}

  //*/













/*
#include<cmath>
#include<string>
#include<iostream>
using namespace std;
#define pi acos(-1.0) 

struct complex
{
    double r,i;
    complex (){r=i=0.0;}
    complex (double real,double image)
 {
  r=real;
  i=image;
 }
    complex operator + (complex o) 
 {
  return complex(r+o.r,i+o.i);
 }
    complex operator - (complex o)
 {
  return complex(r-o.r,i-o.i);
 }
    complex operator * (complex o)
 {
  return complex(r*o.r-i*o.i,r*o.i+i*o.r);
 }
}op1[200001],op2[200001];   

char a[100001],b[100001];              
int sum[200001];                     //保存结果sum

void brc(complex *y,int l)        //二进制平摊反转置换O（logn）
{
    int i,j,k;
    j=l/2;
    for (i=1;i<l-1;i++)
    {
        if (i<j) swap(y[i],y[j]);      //交换互为下标反转ge两个元素，（i<j）保证只交换一次
        k=l/2;
        while (j>=k)                    //由最高位检索,遇1变0（姐系加n/2）遇到0就变1，跳出，
        {
            j-=k;
            k/=2;
        }
        if (j<k) j+=k;                
    }
}

void fft(complex *y,int l,double on)  //FFT O(nlogn)   其中on=1时为DFT，on=-1时为IDFT
{
    int i,j,k,m;
    complex u,t;
    brc(y,l);                                         //调用反转置换
    for (m=2;m<=l;m*=2)                 //控制层数
    {
        complex wn(cos(on*2*pi/m),sin(on*2*pi/m));  //初始化单位复根,每层n吾同，所以要更新咯
        for (j=0;j<l;j+=m)                     //控制起始下表
        {
            complex w(1,0);                //初始化螺旋因子
            for (k=j;k<j+m/2;k++)        //配对过程
            {
                u=y[k];                            //u=y1(w^k) 结合上面我讲ge
                t=w*y[k+m/2];                //t=w^k*y2(w^k)
                y[k]=u+t;                        //y(w^k)=u+t
                y[k+m/2]=u-t;                //y(w^(k+n/2))=u-t
                w=w*wn;                       //更新螺旋因子
            }                                         //上面操作又叫做蝴蝶操作
        }
    }
    if (on==-1) for (i=0;i<l;i++) y[i].r/=l;      //IDFT时公式ge 1/n
}

int main()
{
    int l1,l2,i,l;
    while (scanf("%s %s",a,b)!=EOF)
    {
        l1=strlen(a);
        l2=strlen(b);
        l=1;
        while (l<l1*2 || l<l2*2) l*=2;            //将次数界变成2^n,配合二分法同反转置换
        for (i=0;i<l1;i++)                             //倒置存入，配合我后面ge进位
        {
            op1[i].r=a[l1-i-1]-'0';
            op1[i].i=0.0;
        }
        for (;i<l;i++) op1[i].r=op1[i].i=0.0;//将多余次数界初始化为0
        for (i=0;i<l2;i++)
        {
            op2[i].r=b[l2-i-1]-'0';
            op2[i].i=0.0;
        }
        for (;i<l;i++) op2[i].r=op2[i].i=0.0;
        fft(op1,l,1);                                     //DFT(a)
        fft(op2,l,1);                                     //DFT(b)
        for (i=0;i<l;i++) op1[i]=op1[i]*op2[i];  //点乘并将结果存入a
        fft(op1,l,-1);                                    //IDFT(a*b)
        for (i=0;i<l;i++) sum[i]=op1[i].r+0.5;   //由于FFT有精度问题，所以呢度要四舍五入
        for (i=0;i<l;i++)                               //对sum做进位操作
        {
            sum[i+1]+=sum[i]/10;
            sum[i]%=10;
        }
        l=l1+l2-1;         
        while (sum[l]<=0 && l>0) l--;       //检索最高非零位
        for (i=l;i>=0;i--) printf("%d",sum[i]);    //倒序输出
        printf("\n");
    }
    return 0;
}

//*/













/*

#include<complex>
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
const double pi=acos(-1);
const complex<double> I(0,1);
const double eps=1e-6;
void fft(int n,int sig,complex<double> a[]){
    for(int j=1;j<n-1;j++){
        int i=0;
        for(int k=1,tmp=j;k<n;i=(i<<1)|(tmp&1),k<<=1,tmp>>=1);
        if(j<i) swap(a[i],a[j]);
    }
    for(int m=2;m<=n;m<<=1){
        int mh =m>>1;
        for(int i=0;i<mh;i++){
            complex<double> w=exp(sig*i*pi/mh*I);
            for(int j=i;j<n;j+=m){
                int k=j+mh;
                complex<double> u=a[j];
                a[j]=u+a[k]*w;
                a[k]=u-a[k]*w;
            }
        }
    }
}
complex<double> a[200000],b[200000];
char a1[100010],a2[100010];
int ans[200010];
int main()
{
	int i;
    while(scanf("%s%s",a1,a2)!=EOF){
        int l1=strlen(a1);
        int l2=strlen(a2);
        int l=1;
        while(1){
            if(l>=l1&&l>=l2)
                break;
            l<<=1;
        }
        l<<=1;
        for(i=0;i<l1;++i)
            a[i]=complex<double>(a1[l1-1-i]-'0',0);
        for(i=0;i<l2;++i)
            b[i]=complex<double>(a2[l2-1-i]-'0',0);
        for(i=l1;i<l;++i)
            a[i]=complex<double>(0,0);
        for(i=l2;i<l;++i)
            b[i]=complex<double>(0,0);
        fft(l,1,a);
        fft(l,1,b);
        for(i=0;i<l;++i)
            a[i]*=b[i];
        fft(l,-1,a);
        int k=0,tmp=0;
        ans[0]=0;
        for(i=0;i<l;++i){
            tmp=(int)(a[i].real()/l+eps);
            ans[i]+=tmp;
            if(ans[i])
                k=i;
            ans[i+1]=ans[i]/10;
            ans[i]%=10;
        }
        for(i=k;i>=0;--i)
            printf("%d",ans[i]);
        printf("\n");
    }
    return 0;
}

//*/















/*
#include <cmath>  
 #include <complex>  
 #include <cstring>  
 using namespace std;  
   
 const double PI = acos(-1.0);
 typedef complex<double> cp;  
 typedef __int64 int64;  
   
#define max(a,b) a>b?a:b

 const int N = 1 << 16;  
 int64 a[N], b[N], c[N << 1];  
   
 void bit_reverse_copy(cp a[], int n, cp b[])  
 {  
     int i, j, k, u, m;  
     for (u = 1, m = 0; u < n; u <<= 1, ++m);  
     for (i = 0; i < n; ++i)  
     {  
         j = i; k = 0;  
         for (u = 0; u < m; ++u, j >>= 1)  
             k = (k << 1) | (j & 1);  
         b[k] = a[i];  
     }  
 }  
   
 void FFT(cp _x[], int n, bool flag)  
 {  
     static cp x[N << 1];  
     bit_reverse_copy(_x, n, x);  
     int i, j, k, kk, p, m;  
     for (i = 1, m = 0; i < n; i <<= 1, ++m);  
     double alpha = 2 * PI;  
     if (flag) alpha = -alpha;  
     for (i = 0, k = 2; i < m; ++i, k <<= 1)  
     {  
         cp wn = cp(cos(alpha / k), sin(alpha / k));  
         for (j = 0; j < n; j += k)  
         {  
             cp w = 1, u, t;  
             kk = k >> 1;  
             for (p = 0; p < kk; ++p)  
             {  
                 t = w * x[j + p + kk];  
                 u = x[j + p];  
                 x[j + p] = u + t;  
                 x[j + p + kk] = u - t;  
                 w *= wn;  
             }  
         }  
     }  
     memcpy(_x, x, sizeof(cp) * n);  
 }  
   
 void polynomial_multiply(int64 a[], int na, int64 b[], int nb, int64 c[], int &nc)  
 {  
     int i, n;  
     i = max(na, nb) << 1;  
     for (n = 1; n < i; n <<= 1);  
     static cp x[N << 1], y[N << 1];  
     for (i = 0; i < na; ++i) x[i] = a[i];  
     for (; i < n; ++i) x[i] = 0;  
     FFT(x, n, 0);  
     for (i = 0; i < nb; ++i) y[i] = b[i];  
     for (; i < n; ++i) y[i] = 0;  
     FFT(y, n, 0);  
     for (i = 0; i < n; ++i) x[i] *= y[i];  
     FFT(x, n, 1);  
     for (i = 0; i < n; ++i)   
     {  
         c[i] =(int64)(x[i].real() / n + 0.5);
     }  
     for (nc = na + nb - 1; nc > 1 && !c[nc - 1]; --nc);  
 }  
   
 const int LEN = 5, MOD = 100000;  
 void convert(char *s, int64 a[], int &n)  
 {  
     int len = strlen(s), i, j, k;  
     for (n = 0, i = len - LEN; i >= 0; i -= LEN)  
     {  
         for (j = k = 0; j < LEN; ++j)  
             k = k * 10 + (s[i + j] - '0');  
         a[n++] = k;  
     }  
     i += LEN;  
     if (i)  
     {  
         for (j = k = 0; j < i; ++j)  
             k = k * 10 + (s[j] - '0');  
         a[n++] = k;  
     }  
 }  
   
 void print(int64 a[], int n)  
 {  
     printf("%I64d", a[--n]);  
     while (n) printf("%05I64d", a[--n]);  
     puts("");  
 }  
   
 char buf[N + 10];  
   
 int main()  
 {  
     int na, nb, nc;  
       
     while (scanf("%s", buf) != EOF)  
     {  
         bool sign = false;  
         if (buf[0] == '-')  
         {  
             sign = !sign;   
             convert(buf + 1, a, na);  
         }  
         else convert(buf, a, na);  
         scanf("%s", buf);  
         if (buf[0] == '-')  
         {  
             sign = !sign;  
             convert(buf + 1, b, nb);  
         }  
         else convert(buf, b, nb);  
         polynomial_multiply(a, na, b, nb, c, nc);  
         int64 t1, t2;  
         t1 = 0;  
         for (int i = 0; i < nc; ++i)  
         {  
             t2 = t1 + c[i];  
             c[i] = t2 % MOD;  
             t1 = t2 / MOD;  
         }  
         for (; t1; t1 /= MOD) c[nc++] = t1 % MOD;  
         if (sign) putchar('-');  
         print(c, nc);  
     }  
     return 0;  
 }
 //*/














/*
#include<iostream>
#include<cmath>
using namespace std;
typedef struct vir{
        double re,im;
        vir(){}
        vir(double a,double b){re=a;im=b;}
        vir operator +(const vir &b){ return vir(re+b.re,im+b.im);}
        vir operator -(const vir &b){ return vir(re-b.re,im-b.im);}
        vir operator *(const vir &b){ return vir(re*b.re-im*b.im,re*b.im+b.re*im);}
}vir;
vir x1[200005],x2[200005];
const double Pi = acos(-1.0);
void change(vir *x,int len,int loglen)
{
        int i,j,k,t;
        for(i=0;i<len;i++)
        {
                t = i;
                for(j=k=0;j<loglen;j++,t>>=1)
                        k = (k<<1)|(t&1);
                if(k<i)
                {
                        vir wt =  x[k];
                        x[k] = x[i];
                        x[i] = wt;
                }
        }
}
void fft(vir *x,int len,int loglen)
{
        int i,j,t,s,e;
        change(x,len,loglen);
        t = 1;
        for(i=0;i<loglen;i++,t<<=1)
        {
                s = 0;
                e = s + t;
                while(s<len)
                {
                        vir a,b,wo(cos(Pi/t),sin(Pi/t)),wn(1,0);
                        for(j=s;j<s+t;j++)
                        {
                                a = x[j];
                                b = x[j+t]*wn;
                                x[j] = a + b;
                                x[j+t] = a - b;
                                wn =wn*wo;
                        }
                        s = e+t;
                        e = s+t;
                }
        }
}

void dit_fft(vir *x,int len,int loglen)
{
        int i,j,s,e,t=1<<loglen;
        for(i=0;i<loglen;i++)
        {
                t>>=1;
                s=0;
                e=s+t;
                while(s<len)
                {
                        vir a,b,wn(1,0),wo(cos(Pi/t),-sin(Pi/t));
                        for(j=s;j<s+t;j++)
                        {
                                a = x[j]+x[j+t];
                                b = (x[j]-x[j+t])*wn;
                                x[j] = a;
                                x[j+t] = b;
                                wn = wn*wo;
                        }
                        s = e+t;
                        e = s+t;
                }
        }
        change(x,len,loglen);
        for(i=0;i<len;i++)
                x[i].re/=len;
}


int main()
{
        char a[100005],b[100005];
        int i,len1,len2,t,over,len,loglen;
        
        while(scanf("%s%s",a,b)!=EOF)
        {
                len1 = strlen(a)<<1;
                len2 = strlen(b)<<1;
                len = 1;
                loglen = 0;
                while(len<len1)
                {
                        len<<=1;
                        loglen++;
                }
                while(len<len2)
                {
                        len<<=1;
                        loglen++;
                }
                for(i=0;a[i]!='\0';i++)
                {
                        x1[i].re = a[i]-'0';
                        x1[i].im = 0;
                }
                for(;i<len;i++)
                        x1[i].re = x1[i].im = 0;
                for(i=0;b[i]!='\0';i++)
                {
                        x2[i].re = b[i]-'0';
                        x2[i].im = 0;
                }
                for(;i<len;i++)
                        x2[i].re = x2[i].im = 0;
                fft(x1,len,loglen);
                fft(x2,len,loglen);
                for(i=0;i<len;i++)
                        x1[i] = x1[i]*x2[i];
                dit_fft(x1,len,loglen);
                for(i=(len1+len2)/2-2,over=loglen=0;i>=0;i--)
                {
                        t = x1[i].re + over + 0.5;
                        a[loglen++] = t%10;
                        over =  t/10;
                }
                while(over)
                {
                        a[loglen++] = over%10;
                        over /= 10;
                }
                for(loglen--;loglen>=0&&!a[loglen];loglen--);
                if(loglen<0)
                        putchar('0');
                else
                        for(;loglen>=0;loglen--)
                                putchar(a[loglen]+'0');
                putchar('\n');
        }
        return 0;
}
//*/