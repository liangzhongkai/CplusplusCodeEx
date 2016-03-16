#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAX = 2005;

/******
 * flag:1�����ҵ���ͻ;0����δ�ҵ�
 * n:bugs������
 * m:iteractions������
 ******/
int flag, n, m;

/******
 * �ڽӱ�
 ******/
vector<int> v[MAX];

/******
 * sex��ʾbugs���Ա�,Ĭ��Ϊ-1
 * mark��ʾ�õ��Ƿ�������
 ******/
int sex[MAX];
int mark[MAX];

void dfs(int x)
{
    int i, len = v[x].size();

    for (i = 0; i < len; ++i)
    {
        if (sex[v[x][i]] == -1)
        {
            sex[v[x][i]] = (sex[x] + 1) % 2;
        }
        else if (sex[v[x][i]] == sex[x])
        {
            flag = 1;
            return;
        }
        
        if (mark[v[x][i]] == 0)
        {
            mark[v[x][i]] = 1;
            dfs(v[x][i]);
        }
    }
}

int main()
{
    int i, j, a, b;
    int cases, scenarios;
    scanf("%d", &scenarios);

    for (cases = 1; cases <= scenarios; ++cases)
    {
        scanf("%d%d", &n, &m);

        /*
         * �Ը���������ʼ��
         */

        for (i = 0; i <= n; ++i)
        {
            v[i].clear();
            sex[i] = -1;
            mark[i] = 0;
        }

        flag = 0;

        for (i = 0; i < m; ++i)
        {
            scanf("%d%d", &a, &b);
            v[a].push_back(b);
            v[b].push_back(a);
        }

        for (i = 1; i <= n; ++i)
        {
            if (flag == 1)
            {
                break;
            }

            if (sex[i] == -1)
            {
                sex[i] = 0;
            }

            if (mark[i] == 0)
            {
                mark[i] = 1;
                dfs(i);
            }
        }

        if (flag == 1)
        {
            printf("Scenario #%d:\nSuspicious bugs found!\n\n", cases);
        }
        else
        {
            printf("Scenario #%d:\nNo suspicious bugs found!\n\n", cases);
        }
    }

    return 0;
}