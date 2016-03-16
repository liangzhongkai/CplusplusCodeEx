/*
Sample Input

1 
ABCD EFGH even 
ABCI EFJK up 
ABIJ EFGH even 

12 
ABCD EFGH even 
ABCI EFJK up 
ABIJ EFGH even 
AGHL BDEC even 
JKI ADE up 
J K even 
ABCDEF GHIJKL up 
ABC DEF even 
I J down 
ABCDEF GHIJKL up 
ABHLEF GDIJKC down 
CD HA even 
A B up 
B A down 
A C even 
A B up 
B C even 
DEFG HIJL even 
ABC DEJ down 
ACH IEF down 
AHK IDJ down 
ABCD EFGH even 
AB IJ even 
A L down 
EFA BGH down 
EFC GHD even 
BA EF down 
A B up 
A C up 
L K even 
ACEGIK BDFHJL up 
ACEGIL BDFHJK down 
ACEGLK BDFHJI down 
ACEGIK BDFHJL up 
ACEGIL BDFHJK down 
ACEGLK BDFHJI up 


Sample Output

K is the counterfeit coin and it is light. 

  sample output 
K is the counterfeit coin and it is light. 
I is the counterfeit coin and it is heavy. 
I is the counterfeit coin and it is light. 
L is the counterfeit coin and it is light. 
B is the counterfeit coin and it is light. 
A is the counterfeit coin and it is heavy. 
A is the counterfeit coin and it is light. 
L is the counterfeit coin and it is heavy. 
A is the counterfeit coin and it is light. 
A is the counterfeit coin and it is heavy. 
L is the counterfeit coin and it is light. 
K is the counterfeit coin and it is heavy.

*/


//                           236K	0MS	C++	1258B
#include<iostream>
#include<string>

using namespace std;

int main()
{
	int tc, i, j;
	string left, right, result;
	int k ;
	string reslt;

	cin >> tc;

	while( tc-- )
	{
		int ans[13] = {0};
		int equal[13] = {0};
		int count = 0;

		for(i=0; i<3; i++)
		{
			cin  >> left >> right >> result;
			if(result=="even")
			{
				for(j=0; j<left.size(); j++)
				{
					equal[left[j]-65] = 1;
				}
				for(j=0; j<right.size(); j++)
				{
					equal[right[j]-65] = 1;
				}
			}
			else if(result=="up")
			{
				count++;
				for(j=0; j<left.size(); j++)
				{
					ans[left[j]-65]--;
				}
				for(j=0; j<right.size(); j++)
				{
					ans[right[j]-65]++;
				}
			}
			else if(result=="down")
			{
				count++;
				for(j=0; j<left.size(); j++)
				{
					ans[left[j]-65]++;
				}
				for(j=0; j<right.size(); j++)
				{
					ans[right[j]-65]--;
				}
			}
		}

		k = -1;
		reslt = "";
		for(i=0; i<12; i++)
		{
			if(equal[i]==1)
				continue;
			if(ans[i]==count)
			{
				k = i;
				reslt = "light";
			}
			if(ans[i]==-count)
			{
				k = i;
				reslt = "heavy";
			}
		}

		cout << char(k+65) << " is the counterfeit coin and it is " << reslt << "." << endl;
	}

	return 0;
}