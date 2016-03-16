//*  C++ 	330s  5568kb
 #include<iostream> 
 #include<cstdio>
 #include<cstdlib>
 #include<map>
 #include<cstring>
 using namespace std;
 typedef long long LL;
 #define N 100010
 struct node{
     int l,r;
     friend bool operator<(const node &x,const node &y){
         if(y.l!=x.l) return y.l<x.l;
         return y.r<x.r;
     }
 }tree[2][N];
 int n,m,cs,num[2][N];
 map<node,int> state;
 int id(node x){
     if(state.find(x)==state.end())
         state[x]=++cs;
     return state[x];
 }
 int dfs(int u,int kind){
     if(u==-1) return 0;
     node temp;
     temp.l=dfs(tree[kind][u].l,kind);
     temp.r=dfs(tree[kind][u].r,kind);
     int ans=id(temp);
     num[kind][ans]++;
     return ans;
 }
 int main(){
     int T,a,b, i;
     scanf("%d",&T);
     while(T--){
         scanf("%d%d",&n,&m);
         for(i=1;i<=n;++i){
             scanf("%d%d",&a,&b);
             tree[0][i].l=a;
             tree[0][i].r=b;
         }
         for(i=1;i<=m;++i){
             scanf("%d%d",&a,&b);
             tree[1][i].l=a;
             tree[1][i].r=b;
         }
         state.clear();
         cs=0;
         memset(num,0,sizeof(num));
         dfs(1,0);
         dfs(1,1);
         LL ans=0;
         for(i=0;i<=cs;++i)
             ans+=LL(num[0][i])*LL(num[1][i]);
         printf("%lld\n",ans);
     }
     return 0;
 }
 //*/





/*      320s 	7520kb

#include<iostream>
 #include<cstdio>
 #include<cstdlib>
 #include<map>
 #include<cstring>

 using namespace std;

 typedef __int64 LL;
 #define N 100010

 struct node{
     int l,r;
     friend bool operator<(const node &x,const node &y){
         if(y.l!=x.l) return y.l<x.l;
         return y.r<x.r;
     }
 }tree[2][N];

 int n,m,cs,num[2][N<<1];
 map<node,int> state;

 int id(node x){
     if(state.find(x)==state.end())
         state[x]=++cs;
     return state[x];
 }

 struct stk{
     int u,op,st;
 }qu[N];

 void dfs(int u,int kind){
     int top=0;
     qu[top].u=u;
     qu[top++].op=0;

     while(top){
         stk now=qu[top-1];
         if(now.u==-1){
             qu[top-1].st=0;
             top--;
         }
         else if(!now.op){
             qu[top].u=tree[kind][now.u].l;
             qu[top].op=0;
             qu[top-1].op=1;
             top++;
         }
         else if(now.op==1){
             qu[top].u=tree[kind][now.u].r;
             qu[top].op=0;
             qu[top-1].op=2;
             qu[top-1].st=qu[top].st;
             top++;
         }
         else{
             node temp;
             temp.l=qu[top-1].st;
             temp.r=qu[top].st;
             int rig=id(temp);
             qu[top-1].st=rig;
             num[kind][rig]++;
             top--;
         }
     }
 }

 int main()
 {
     int T,a,b, i;
     scanf("%d",&T);
     while(T--){
         scanf("%d%d",&n,&m);
         for(i=1;i<=n;++i){
             scanf("%d%d",&a,&b);
             tree[0][i].l=a;
             tree[0][i].r=b;
         }
         for(i=1;i<=m;++i){
             scanf("%d%d",&a,&b);
             tree[1][i].l=a;
             tree[1][i].r=b;
         }

         state.clear();
         cs=0;
         memset(num,0,sizeof(num));
         dfs(1,0);
         dfs(1,1);
         LL ans=0;
         for(i=0;i<=cs;++i)
             ans+=LL(num[0][i])*LL(num[1][i]);
         printf("%I64d\n",ans);
     }
     return 0;
 }
//*/

 /*
2
5 4
2 3
4 5
-1 -1
-1 -1
-1 -1
2 3
-1 -1
4 -1
-1 -1
5 5
2 3
4 5
-1 -1
-1 -1
-1 -1
2 3
4 -1
-1 -1
5 -1
-1 -1
 */