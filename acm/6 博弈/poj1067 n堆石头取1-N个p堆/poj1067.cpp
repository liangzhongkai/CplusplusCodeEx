//172K	0MS	C++	323B
#include<iostream>
#include<cmath>
using namespace std;

int main()
{
    double arph=(sqrt(5.0)+1.0)/2.0;
    int a,b;
    while (cin>>a>>b)
    {
        if (b<a) swap(a,b);
        int n=b-a;
        int c=floor(n*arph);
        if (c==a) cout<<0<<endl;
        else cout<<1<<endl;
    }
    return 0;
}
