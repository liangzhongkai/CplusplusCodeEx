//  36944K	625MS	C++	715B
#include<iostream>

using namespace std;

char mp[37500010];

int main()
{
	int a[5];
	int i, tmp = 0;
	int x1 , x2 , x3 , x4 , x5 ;
	int ans = 0;

	for(i=0; i<5; i++){
		cin >> a[i] ;
	}

	memset(mp, 0, sizeof(mp));
	for(x1=-50; x1<51; x1++){
		if(x1!=0)
			for(x2=-50; x2<51; x2++){
				if(x2!=0)
					for(x3=-50; x3<51; x3++){
						if(x3!=0){
							tmp = a[0]*x1*x1*x1 + a[1]*x2*x2*x2 + a[2]*x3*x3*x3;
							mp[tmp+18750001]++;
						}
					}
			}
	}

	for(x4=-50; x4<51; x4++){
		if(x4!=0){
			for(x5=-50; x5<51; x5++){
				if(x5!=0){
					tmp = a[3]*x4*x4*x4 + a[4]*x5*x5*x5;
					ans += mp[18750001-tmp];
				}
			}
		}
	}

	cout << ans << endl;

	return 0;
}