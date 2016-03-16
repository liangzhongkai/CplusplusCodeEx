// 250MS	4548K	4427 B	C++
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