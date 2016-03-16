//  11MS 	716K 	1074B 	
#include<iostream>
#include<string>

using namespace std;

string str;

void print(int a, int b)
{
	if(a!=b)
	{
		for(int i=a; i<b; i++)
			cout<< str[i];
	}
}


int main()
{
	int e;
	int cnt = 1;

	while(cin >> str)
	{
		cout << "Case " << cnt << ":" << endl;
		e = str.find("acm");
		while(!str.empty() && e!=-1)
		{
			while(e>9 && str.length()>=10)
			{
				print(0, 10);
				cout <<endl;
				str = str.replace(0, 10, "");
				e = str.find("acm");
			}
			
			print(0, e);
			if(e!=0)
				cout << endl;
			str = str.replace(0, e+3, "");
			cout << "acm" ;
				
			e = str.find("acm");
			if(e>7 || (e==-1 && str.length()>7))
			{
				print(0,7);
				cout << endl;
				str = str.replace(0,7, "");
				e = str.find("acm");
			}
			
		}
		while(str.length()>10)
		{
			print(0, 10);
			cout << endl;
			str = str.replace(0, 10, "");
		}
		
		
		cout << str << endl;
		cnt++;
	}
		
	return 0;
}