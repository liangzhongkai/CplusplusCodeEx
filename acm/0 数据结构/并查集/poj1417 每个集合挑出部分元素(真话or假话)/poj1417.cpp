/*  3052K	32MS	C++	2543B
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int MAXN = 605;
int father[MAXN];
int val[MAXN];
int dif[MAXN], com[MAXN];
int A, B;
int mp[MAXN][3];
int len;
int dp[MAXN][MAXN];
int flag[MAXN][MAXN];
int ans[MAXN];
int size;

void init()
{
	int i;
	for(i=0; i<MAXN; i++){
		father[i] = i;
		val[i] = 0;
		dif[i] = 0;
		com[i] = 1;
	}
	memset(dp, 0, sizeof(dp));
	memset(flag, 0, sizeof(flag));
	memset(ans, 0, sizeof(ans));
	size = 0;
	len = 0;
}

int Find(int a){
	if(father[a]==a)
		return a;
	int na = father[a];
	father[a] = Find(father[a]);
	val[a] = val[a] ^ val[na];
	return father[a];
}

void Union(int a, int b, int c){
	father[A] = B;
	val[A] = val[a] ^ val[b] ^ c;
	if(val[A]==0){      // 同类
		dif[B] += dif[A];
		com[B] += com[A];
	}
	else{
		dif[B] += com[A];
		com[B] += dif[A];
	}
}

int main()
{
	int n, p, q;
	int i, j, a, b;
	char ch[5];

	while(scanf("%d%d%d", &n, &p, &q)){
		if(n==0 && q==0 && p==0)
			break;
		//////////////////边界情况////////////////////////
		if(n==0 && q==0 && p==1){
			printf("1\nend\n");
			continue;
		}
		if(n==0 && q==1 && p==0){
			printf("end\n");
			continue;
		}
		//////////////////////////////////////////////////

		init();
		for(i=0; i<n; i++){
			scanf("%d %d %s", &a, &b, ch);
			A = Find(a);
			B = Find(b);
			if(A==B)   continue;
			if(strcmp(ch, "no")==0){
				Union(a, b, 1);
			}
			else if(a==b){
				continue;
			}
			else{
				Union(a, b, 0);
			}
		}

		for(i=1; i<=p+q; i++){
			if(father[i]==i){
				//cout << "*" << com[i] << " " << dif[i] << endl;
				mp[len][0] = i,   mp[len][1] = com[i],   mp[len++][2] = dif[i];
			}
		}

		dp[0][mp[0][1]] = 1;   dp[0][mp[0][2]] = 1;
		flag[0][mp[0][1]] = 1;   flag[0][mp[0][2]] = 0;
		for(i=1; i<len; i++){
			for(j=0; j<MAXN; j++){
				if(dp[i-1][j]!=0){
					dp[i][j+mp[i][1]] += dp[i-1][j];
					flag[i][j+mp[i][1]] = 1;
					dp[i][j+mp[i][2]] += dp[i-1][j];
					flag[i][j+mp[i][2]] = 0;
				}
			}
		}

		int t = p;
		if(dp[len-1][p]==1 && dp[len-1][q]==1 && q!=p){
			for(i=len-1; i>=0; i--){
				if(flag[i][t]==0){
					for(j=1; j<=p+q; j++){
						if(Find(j)==mp[i][0] && val[j]==1)
							ans[size++] = j;
					}
					t -= mp[i][2];
				}
				else{
					for(j=1; j<=p+q; j++){
						if(Find(j)==mp[i][0] && val[j]==0)
							ans[size++] = j;
					}
					t -= mp[i][1];
				}
			}
			sort(ans, ans+size);
			for(i=0; i<size; i++){
				printf("%d\n", ans[i]);
			}
			printf("end\n");
		}
		else{
			printf("no\n");
		}
	}

	return 0;
}
//*/


/*   4808K	63MS	C++	3531B
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

const int maxP=1011;
int n, p1, p2, totGroup;
int fa[maxP],rival[maxP],tot[maxP],a[maxP],b[maxP],f[maxP][maxP],w[maxP][maxP],aa[maxP],bb[maxP];
bool v[maxP];

int find( int x )
{
    if ( fa[x]==x ) return x;
    fa[x]=find(fa[x]);
    return fa[x];
}

int unionT( int x, int y )
{
     x=find(x);
     y=find(y);
     if ( x==y || y==0 ) return x;
     if ( x==0 ) return y;
     
     fa[x]=y;
     tot[y]+=tot[x];
     return y;
}

void getWay( int i, int j )
{
     if ( i==0 ) return;
     
     if ( w[i][j]==1 ) 
     {
         getWay( i-1, j-a[i] );
         v[aa[i]]=true;
     }
     else
     {
         getWay( i-1, j-b[i] );
         v[bb[i]]=true;
     }
}

int main()
{
    while ( cin >> n >> p1 >> p2 )
    {
          if ( n+p1+p2==0 ) break;
          
          for ( int i=1; i<=p1+p2; i++ )
          {
              fa[i]=i;
              rival[i]=0;
              tot[i]=1;
          }
          
          for ( int i=1; i<=n; i++ )
          {
              int x,y;
              string s;
              cin >> x >> y >> s;
              
              if ( s=="yes" )
              {
                   x=find(x);
                   y=find(y);
                   int tx=unionT( x, y ),
                       ty=unionT( rival[x], rival[y] );
                   rival[tx]=ty;
                   rival[ty]=tx;
              }
              else
              {
                  x=find(x);
                  y=find(y);
                  rival[x]=find( rival[x] );
                  rival[y]=find( rival[y] );
                  if ( rival[y]==0 ) rival[y]=x;
                  if ( rival[x]==0 ) rival[x]=y;
                  
                  int tx=unionT( x, rival[y] ),
                      ty=unionT( rival[x], y );
                  rival[tx]=ty;
                  rival[ty]=tx;
              }
          }
          
          memset( v, false, sizeof(v) );
          totGroup=0;
          for ( int i=1; i<=p1+p2; i++ )
          {
              int x=find( i );
              if ( !v[x] )
              {
                   rival[x]=find( rival[x] );
                   totGroup++;
                   a[totGroup]=tot[x];
                   b[totGroup]=tot[rival[x]];
                   aa[totGroup]=x;
                   bb[totGroup]=rival[x];
                   v[x]=true;
                   v[rival[x]]=true;
              }
          }
          
          memset( f, 0, sizeof(f) );
          f[0][0]=1;
          for ( int i=1; i<=totGroup; i++ )
          for ( int j=1; j<=p1; j++ )
          {
              if ( j-a[i]>=0 && f[i-1][j-a[i]]>0 )
              {
                   f[i][j]+=f[i-1][j-a[i]];
                   w[i][j]=1;
              }
              if ( j-b[i]>=0 && f[i-1][j-b[i]]>0 )
              {
                   f[i][j]+=f[i-1][j-b[i]];
                   w[i][j]=2;
              }
              if ( f[i][j]>=2 ) f[i][j]=2;
          }
          
          if ( f[totGroup][p1]==1 || p1==0 )
          {
               memset( v, false, sizeof(v) );
               getWay( totGroup, p1 );
               for ( int i=1; i<=p1+p2; i++ )
               if ( v[ find( i ) ] ) cout << i << endl;
               cout << "end" << endl;
          }
          else cout << "no" << endl;
    }
    
    return 0;
}
//*/

 
//*                 1592K	16MS	C++	2905B
#include<cstdio>
#include<cstring>
#include <iostream>

using namespace std;

#define min(a, b) ((a)>(b)?(b):(a))
#define max(a, b) ((a)>(b)?(a):(b))

#define MAX 601
int root[MAX],same[MAX],diff[MAX],_map[MAX];
int dp[MAX][MAX];
char relation[MAX];

struct{
    int  s, d, c;
}node[MAX];

int findRoot(int x)
{
    int t;
    if(x!=root[x]){
		t = root[x];
		root[x]=findRoot(root[x]);
		relation[x]^=relation[t];
	}
    return root[x];
}

int main()
{
    int i,j, n, p1, p2, a, b, v, r1, r2, s, a1, a2, t;
    char ch[4];
    bool flag, flag1, flag2;
    while(scanf("%d %d %d", &n, &p1, &p2) && (n+p1+p2))
    {
        flag = true;

        if(p1 == p2)   flag = false;

        for(i = 0; i < MAX; i++)
			root[i]=i,   same[i] = diff[i] = relation[i] = _map[i] = 0;

        memset(dp, 0, sizeof(dp));

        for (i = 0; i < n; i++){
            scanf("%d %d %s", &a, &b, ch);
            if(!flag)   continue;
            v = (ch[0]=='y') ? 0:1;
            r1 = findRoot(a), r2 = findRoot(b);
            if(r1!=r2){
                if(r1<r2){root[r2]=r1; relation[r2]=relation[a]^relation[b]^v;}
                else {root[r1]=r2; relation[r1]=relation[a]^relation[b]^v;}
            }
        }

        if(!flag){
			printf("no\n");
			continue;
		}

        for(i=1; i<=(p1+p2); i++){
            t = findRoot(i);  
			(relation[i]==0) ? (same[t]++) : (diff[t]++);
		}

        for (s=0,i=1;i<=(p1+p2);i++)
            if(same[i]>0){
				_map[i]=s;   node[s].s=same[i];   node[s++].d=diff[i];
			}

        a1 = min(node[0].d, node[0].s),   a2 = max(node[0].d, node[0].s);
        if(a1==a2){
			printf("no\n");
			continue;
		}

		// DP 开始！
        for(i=a1; i<a2; i++)   dp[0][i] = a1;
        for(i=a2; i<=p1; i++)   dp[0][i] = a2;
        for(i=1; i<s&&flag; i++){
            a1 = min(node[i].s, node[i].d),   a2 = max(node[i].s, node[i].d);
            if(a1==a2){
				flag=false;
				break;
			}
            for(j=a1;j<=p1;j++){
                dp[i][j] = dp[i-1][j-a1]?(dp[i-1][j-a1]+a1):0;
                if(j-a2>0 && dp[i-1][j-a2]){
                    t = dp[i-1][j-a2]+a2;
                    if(t>dp[i][j])dp[i][j]=t;
                }
            }
        }
        if (dp[s-1][p1]!=p1)flag = false;
        for(i=s-1,t=p1;i>0&&flag;i--){
            flag1 = flag2 = false;
            if(t > node[i].s && dp[i][t]-node[i].s == dp[i-1][t-node[i].s])
                flag1 = true;
            if(t > node[i].d && dp[i][t]-node[i].d == dp[i-1][t-node[i].d])
                flag2 = true;
            if(flag1&&flag2)flag=false;
            if(flag1){node[i].c = 0; t-= node[i].s;}   // 第i棵树选相同的
            else {node[i].c=1; t-= node[i].d;}
        }

        if(node[0].s == t)   node[0].c = 0;
        else node[0].c = 1;
        if(flag){
            for(i=1;i<=(p1+p2);i++)
                if(node[_map[root[i]]].c==relation[i])   printf("%d\n", i);
            printf("end\n");
        }
        else printf("no\n");
    }
    return 0;
}
//*/




/*   1588K	16MS	C++	7931B
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;

#define MAXM 2*MAXS  // Max #[people].
#define MAXS 300  // Max #[people in a tribe].

int father[MAXM + 1], rank[MAXM + 1], opposite[MAXM + 1];
// sets[i] is the set with i being its root.
// sets[i][0] is the number of elems in this set.
// sets[i][1,...] are the elems in this set.
 
int sets[MAXM + 1][MAXM + 1];
// A group is defined to be a pair of sets that are opposite.
// root, size are information of one set.
// oproot, opsize are information of the opposite set.

struct Group
{
    int root;
    int size;
    int oproot;
    int opsize;
};
// groups[i] store the information about a group.

Group groups[MAXM + 1];
int numGroups;  // Total number of groups.
bool isCounted[MAXM + 1];  // Used to collect groups.


// The following is used by DP. 
int divines[MAXM];
int table[2][MAXM];
int trace[MAXM][MAXM];

// Disjoint set operations. 
void makeAllSets(int m)
{
    for(int i = 1; i <= m; ++i)
    {
	father[i] = i;
	rank[i] = 0;
	opposite[i] = -1;
    }
}

int findSet(int x)
{
    if(x != father[x])
    {
	father[x] = findSet(father[x]);
    }
    return father[x];
}

int unionSets(int sx, int sy)
{
    if(sx == sy)
	return sx;
    if(rank[sx] < rank[sy])
    {
	father[sx] = sy;
	return sy;
    }
    else
    {
	if(rank[sx] == rank[sy])
	{
	    rank[sx]++;
	}
	father[sy] = sx;
	return sx;
    }
}

void initilaize(int m)
{
    // sets[0] is a sentinel set standing for an empty set.  
    // All elems are >= 1. 
    for(int i = 0; i <= m; ++i)
    {
	sets[i][0] = 0;
	isCounted[i] = false;
    }
}

// Organize the disjoint forest to groups.
//First store all sets to set.  Then collect groups using sets.

bool collectGroups(int m)
{
    // Collect sets. 
    for(int i = 1; i <= m; ++i)
    {
	int si = findSet(i);
	sets[si][++sets[si][0]] = i;
    }
    // Get groups data. 
    numGroups = 0;
    for(int i = 1; i <= m; ++i)
    {
	if(sets[i][0] > 0 && !isCounted[i])
	{
	   //Get information of set i. 
	    groups[numGroups].root = i;
	    groups[numGroups].size = sets[i][0];
	    isCounted[i] = true;
	    // Get information of opposite set of i. 
	    int si = findSet(i);
	    if(opposite[si] == -1)
	    {  // When si has no opposite set, its opposite set size is 0.
	       // And we set its opposite set to 0, which is a sentinel 
	       // standing for empty set.
		groups[numGroups].oproot = 0;
		groups[numGroups].opsize = 0;
	    }
	    else
	    {
		int soi = findSet(opposite[si]);
		groups[numGroups].oproot = soi;
		groups[numGroups].opsize = sets[soi][0];
		isCounted[soi] = true;
	    }
	    // When two sets has the same size in a group, there cannot be
	    // a unique solution.  So we can stop and output the result to 
	    // save time.
	      
	    if(groups[numGroups].size == groups[numGroups].opsize)
	    {
		return true;
	    }

	    numGroups++;
	}
    }
    return false;
}


// Let f(i, j) be #[formulations] that form j using only groups[0,...,i-1].
// Then:
// f(0, j) = \{
// 		1  if j = 0,
// 		0  otherwise.
// f(i, j) = f(i-1, j-groups[i-1].size) * I_{j >= groups[i-1].size} + 
// 	     f(i-1, j-groups[i-1].opsize) * I_{j >= groups[i-1].opsize}
// 	  1 <= i <= numGroups, 0 <= j <= numDivines.
//
// Time complexity: O(numGroups * numDivines).
// Space complexity: \Theta(numGroups * numDivines).
 
int dpNumFormulations(int numDivines)
{
    table[0][0] = 1;
    for(int j = 1; j <= numDivines; ++j)
    {
	table[0][j] = 0;
    }
    int *row1, *row2;
    row1 = table[0]; row2 = table[1];
    for(int i = 1; i <= numGroups; ++i)
    {
	for(int j = 0; j <= numDivines; ++j)
	{
	    row2[j] = 0;
	    // trace[i][j] = 0 means neither sets are used.
	    //             = 1 means only set is used.
	    //             = 2 means only opposite set is used.
	    //             = 3 means both sets are used.
	     
	    trace[i][j] = 0;  // Initialize to 0.
	    if(j >= groups[i-1].size)
	    {
		row2[j] += row1[j - groups[i-1].size];
		if(row1[j - groups[i-1].size] > 0)
		{
		    trace[i][j] = 1;  // Set last bit to 1 if use set.
		}
	    }
	    if(j >= groups[i-1].opsize)
	    {
		row2[j] += row1[j - groups[i-1].opsize];
		if(row1[j - groups[i-1].opsize] > 0)
		{
		    trace[i][j] |= 2;  // Set second bit to 1 if use opposite set.
		}
	    }
	    row2[j] = min(row2[j], 2);  // Cap to 2.
	}
	swap(row1, row2);
    }

    return row1[numDivines];
}

void restoreSolution(int numDivines)
{
    int num = 0;
    int j = numDivines;
    for(int i = numGroups; i > 0; --i)
    {
	int s;
	if(trace[i][j] == 1)
	{  // Set groups[i-1].root is used
	    s = groups[i-1].root;
	}
	else
	{  // Set groups[i].oproot is used./
	    assert(trace[i][j] == 2);
	    s = groups[i-1].oproot;
	}
	// Puting used set to divines.  
	for(int k = 1; k <= sets[s][0]; ++k)
	{
	    divines[num++] = sets[s][k];
	}
	j -= sets[s][0];
    }
    assert(num == numDivines);
    // Print the solution. 
    sort(divines, divines + numDivines);
    for(int i = 0; i < numDivines; ++i)
    {
	printf("%d\n", divines[i]);
    }
    printf("end\n");
}


int main()
{
    int n, m, p1, p2, x, y;
    char ans[4];
    while(scanf("%d%d%d", &n, &p1, &p2) && !(n == 0 && p1 == 0 && p2 == 0))
    {
	m = p1 + p2;  // Total #[people].
	// Build opposite groups using disjoint forest. 
	 // O(n * \alpha(m)) time.
	 //
	 // When building sets, we maintain the following property:
	//For each root of a set, opposite[root] must point to one elem in
	 // its opposite set, if it has an opposite set.
	 
	makeAllSets(m);
	for(int i = 0; i < n; ++i)
	{
	    scanf("%d%d", &x, &y);
	    scanf("%s", ans);
	    int sx = findSet(x);
	    int sy = findSet(y);
	    if(strcmp(ans, "no") == 0)
	    {  // x and y are in different tribes.
		if(opposite[sx] != -1 && opposite[sy] == -1)
		{
		    int sox = findSet(opposite[sx]);
		    int su = unionSets(sy, sox);
		    opposite[su] = x;  // Need to set the opposite of union.
		}
		else if(opposite[sx] == -1 && opposite[sy] != -1)
		{
		    int soy = findSet(opposite[sy]);
		    int su = unionSets(sx, soy);
		    opposite[su] = y;  // Need to set the opposite of union.
		}
		else if(opposite[sx] != -1 && opposite[sy] != -1)
		{
		    int sox = findSet(opposite[sx]);
		    int soy = findSet(opposite[sy]);
		    unionSets(sx, soy);  // Not need to set opposite of union.
		    unionSets(sy, sox);
		}
		else  // opposite[sx] == -1 && opposite[sy] == -1
		{
		    opposite[sx] = y;
		    opposite[sy] = x;
		}
	    }
	    else
	    {  // x and y are in the same tribe.
		int su = unionSets(sx, sy);
		if(opposite[sx] == -1 && opposite[sy] != -1)
		{
		    int soy = findSet(opposite[sy]);
		    opposite[su] = soy;  // Need to set the opposite of union.
		}
		else if(opposite[sx] != -1 && opposite[sy] == -1)
		{
		    int sox = findSet(opposite[sx]);
		    opposite[su] = sox;  // Need to set the opposite of union.
		}
		else if(opposite[sx] != -1 && opposite[sy] != -1)
		{
		    int sox = findSet(opposite[sx]);
		    int soy = findSet(opposite[sy]);
		    unionSets(sox, soy);  // Not need to set opposite of union.
		}
	    }
	}

	initilaize(m);  // O(m) time.
	// Collect group data. O(m) time.  
	bool isCut = collectGroups(m);
	if(isCut)
	{
	    printf("no\n");  // Early stop to save time.
	    continue;
	}
	// Use DP to solve the problem. O(numGroups * p1) time. /
	int numFormulations = dpNumFormulations(p1);
	if(numFormulations != 1)
	{
	    printf("no\n");
	}
	else
	{
	    restoreSolution(p1);
	}
    }

    return 0;
}

//*/