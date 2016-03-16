//                    480K	657MS	C++	1532B
/*
Sample Input
i
is
has
have
be
my
more
contest
me
too
if
award
#
me
aware
m
contest
hav
oo
or
i
fi
mre
#

Sample Output

me is correct
aware: award
m: i my me
contest is correct
hav: has have
oo: too
or:
i is correct
fi: i
mre: more me

//*/



#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

string diction[10001];


int main()
{
	int i=0, j,k,l;
	string dict;

	while( cin >> diction[i++] && diction[i-1]!="#" )
	{}
	
	while( cin >> dict && dict!="#" )
	{
			int key = 0;
			for(j=0; j<i; j++)
			{
				if(diction[j].size()==dict.size())
				{
					if(diction[j]==dict)
					{
						cout << dict << " is correct" << endl;
						key = 1;
						break;
					}
				}
			}
			
			if(key==1) continue;

			string ans = dict;
			ans += ":";
			int s1 = dict.size();
			for(j=0; j<i-1; j++)
			{
					int s2 = diction[j].size();
					
					if(s1 == s2 + 1)  // ����һ�������ֵ��
					{
						for(k=0; k<s1; k++)
						{
							string temp = dict;
							string::iterator it = temp.begin();
							temp.erase(it+k);
							if(temp==diction[j])
							{
								ans += " " +diction[j];
								break;
							}
						}
					}
					else if(s1 == s2)  // �ĵ�һ�������ֵ��  
					{
						for(k=0; k<s1; k++)
						{
							if(dict[k]!=diction[j][k])
							{
								string temp = dict;
								temp[k] = diction[j][k];
								if(temp==diction[j])
								{
									ans += " " +diction[j];
								}
								break;
							}
						}
					}
					else if(s1 == s2 - 1)  // �Ӷ�һ�������ֵ��
					{
						for(k=0; k<s1; k++)
							if(dict[k]!=diction[j][k])
								break;
						 string temp = diction[j];
						 string::iterator it = temp.begin();
						 temp.erase(it+k);
						 if(temp==dict)
						 {
							 ans += " " +diction[j];
						 }
					}
			}
			cout << ans << endl;
	}
		
	return 0;
}


/*
//                          836K	344MS	C++	2435B
#include <iostream>
#include <string>
#include <vector>
 
using namespace std;
 
int ok;
int ldic, lstr;
string current;
vector<string> dic;
 
// �滻һ���ַ� 
void replace(string dic)
{
    int count = 0;
    // ֻ��һ���ַ���һ����OK  
    for (int i = 0; i < dic.length(); i++)
    {
        if (current[i] != dic[i]) count++;
        if (count > 1) return;
    }
    ok = 1;
    cout << " " + dic;
}
 
// ����һ���ַ�  
void insert(string dic)
{
    string tmp;
    for (int i = 0; i < current.length(); i++)
    {
        // �ڲ�ͬλ�������ַ�  
        if (current[i] != dic[i])
        {
            tmp = dic;
            tmp.insert(i, 1, current[i]);
            if (tmp == current)
            {
                ok = 1;
                cout << " " + dic;
            }
            return;
        }
    }
}
 
// ɾ��һ���ַ�  
void del(string dic)
{
    string tmp;
    for (int i = 0; i < dic.length(); i++)
    {
        // ɾ����ͬλ�õ��ַ�  
        if (current[i] != dic[i])
        {
            tmp = dic;
            tmp.erase(i, 1);
            if (tmp == current)
            {
                ok = 1;
                cout << " " + dic;
            }
            return;
        }
    }
}
 
int main()
{
    // ������  
    while(1)
    {
        cin >> current;
        if (current == "#") break;
        dic.push_back(current);
    }
 
    while(1)
    {
        cin >> current;
        if (current == "#") break;
 
        ok = -1;
        lstr = current.length();
 
        // �ж��Ƿ�correct  
        for (int i = 0; i < dic.size(); i++)
        {
            if (dic[i] == current)
            {
                cout << current + " is correct";
                ok = 0;
                break;
            }
        }
 
        // ����  
        if (ok < 0)
        {
            cout << current + ':';
            for (int i = 0; i < dic.size(); i++)
            {
                ldic = dic[i].length();
                if (lstr == ldic)
                {
                    replace(dic[i]);
                }
                else if (lstr == ldic + 1)
                {
                    insert(dic[i]);
                }
                else if (lstr == ldic - 1)
                {
                    del(dic[i]);
                }
            }
        }
 
        cout << endl;
    }
    //system("pause");
    return 0;
}
//*/