#include<iostream>
#include<algorithm>

using namespace std;

#define min(a,b) a<b?a:b

int main()
{
    int ugly[1501];
    ugly[1] = 1;
    int x2 = 1, x3 = 1, x5 = 1, num, n;
    for(int i = 2; i < 1501; ++i){
        num = min(min(ugly[x2] * 2, ugly[x3] * 3), ugly[x5] * 5);
        if(num == ugly[x2] * 2)
            ++x2;
        if(num == ugly[x3] * 3)
            ++x3;
        if(num == ugly[x5] * 5)
            ++x5;
        ugly[i] = num;
    }
    while(cin >> n){
        cout << "The " << n << "th ugly number is " << ugly[n] << "." << endl;
    }
    return 0;
}