/*
1
5
1 4
2 6
8 10
3 4
7 10

4
*/
//  1088K	79MS	C++	1890B
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
 
const int maxn = 11111;
bool hash[maxn];
int li[maxn] , ri[maxn];
int X[maxn*3];     // ��ɢ����ĵ��� 2*maxn + ��
int col[maxn<<4];  // �ײ�������˫���ĵ��� �� ����������2*maxn+��<<2
int cnt;
 
void PushDown(int rt) {
	if (col[rt] != -1) {
		col[rt<<1] = col[rt<<1|1] = col[rt];
		col[rt] = -1;
	}
}

void update(int L,int R,int c,int l,int r,int rt) {
	if (L <= l && r <= R) {
		col[rt] = c;
		return ;
	}
	PushDown(rt);                  // ��ǰ��
	int m = (l + r) >> 1;
	if (L <= m) update(L , R , c , lson);
	if (m < R) update(L , R , c , rson);
}

// �����ѯû�и���col[]����ΪֻҪ�����ж�����col[i]ֵ�������ٸ�����������
void query(int l,int r,int rt){
	if (col[rt] != -1) {           // ��l-r�����ڵ�col[]ֵ��ͬʱ��col[rt] == -1
		if (!hash[ col[rt] ]) cnt ++;
		hash[ col[rt] ] = true;
		return ;
	}
	if (l == r) return ;
	int m = (l + r) >> 1;
	query(lson);
	query(rson);
}

int Bin(int key,int n,int X[]){
	int l = 0 , r = n - 1;
	while (l <= r) {
		int m = (l + r) >> 1;
		if (X[m] == key) return m;
		if (X[m] < key) l = m + 1;
		else r = m - 1;
	}
	return -1;
}

int main() 
{
	int T , n, i;
	scanf("%d",&T);
	while (T --) {
		scanf("%d",&n);
		int nn = 0;
		for (i = 0 ; i < n ; i ++) {
			scanf("%d%d",&li[i] , &ri[i]);
			X[nn++] = li[i];
			X[nn++] = ri[i];
		}

		////////////////////////////////////// ��ɢ�� : ��Ϊ�˽�Լ�ռ�////////////////////////////////////////
		sort(X , X + nn);
		int m = 1;
		for (i = 1 ; i < nn; i ++) {
			if (X[i] != X[i-1]) X[m ++] = X[i];
		}
		// ��Ϊ��ɢ�������е����Ŷ��������ģ������Ḳ�ǵײ�ĺ�������ʹʵ����û����ȫ����
		// ���磺1-10 1-4 6-10�� ��Ӧ����ɢ�����£�
		//       1-4  1-2 3-4 �� ��������������ȫ�����ˣ�����ʵ����û�и����ꡣ
		for (i = m - 1 ; i > 0 ; i --) {
			if (X[i] != X[i-1] + 1) X[m ++] = X[i-1] + 1;
		}
		sort(X , X + m);
		//////////////////////////////////////////////////////////////////////////////////////////////////////

		memset(col , -1 , sizeof(col));
		for (i = 0 ; i < n ; i ++) {
			int l = Bin(li[i] , m , X);   // ��li[i]��ri[i]����Ŵ���
			int r = Bin(ri[i] , m , X);   // �������к������width=1  ����  ��ɢ��������
			update(l , r , i , 0 , m , 1);
		}
		cnt = 0;
		memset(hash , false , sizeof(hash));
		query(0 , m , 1);
		printf("%d\n",cnt);
	}
	return 0;
}



/*    1516K	63MS	C++	2668B
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#define MAX 10005
using namespace std;
 
struct node{
    int a,b,color,flag;
}s[8*MAX];
 
struct st{
    int x,y;
}t[2*MAX];
 
int N[2*MAX],vs[2*MAX],sim[4*MAX],times,ans;
 
int cmp(int a,int b){
    return a<b;
}
 
int getidex(int y){
    int i=1,j=times+1,mid;
    while(i<=j){
        mid=(i+j)/2;
        if(N[mid]==y)   return mid;
        if(N[mid]>y) j=mid;
        else i=mid+1;
    }
    return 0;
}
 
int Build(int x,int y,int num){
    s[num].color=0;
    s[num].flag=0;
    s[num].a=x; 
    s[num].b=y;
    if(x==y)
        return 0;
    int mid=(x+y)/2;
        Build(x,mid,num+num);
        Build(mid+1,y,num+num+1);
}
 
int modify(int x,int y,int num,int color){
    if(s[num].color>0) //˵�������ᱻ���ǣ������������ˣ�
        return 0;
    if(x==s[num].a&&y==s[num].b){//�ҵ���ѯ����
        if(s[num].flag==0){//�ж��Ƿ���ȫ����
            s[num].color=color;
            s[num].flag=1;//Ⱦɫ
            if(!vs[color]){//��������ɫû�г��ֹ���������
                               //��ǰ���������ǿ����ˣ���ʵ���Ҳ������β�ѯ��һ��������
                              //�����Ƕ�����һ�����������Ⱦɫ����������Ȼ��������������϶�ҲȾɫ��
                              //���Ǽ���ֻ��Ҫһ�Σ���
                ans++;
                vs[color]=1;
            }
        }
        return 0;
    }
    int mid=(s[num].a+s[num].b)/2;
    if(y<=mid)
        modify(x,y,num+num,color);
    else if(x>mid)
        modify(x,y,num+num+1,color);
    else{
        modify(x,mid,num+num,color);
        modify(mid+1,y,num+num+1,color);
    }
        //�ص�ע��һ��������������������Ⱦɫ��
        //����ȻҪ���ϸ��¸��׽ڵ��Ⱦɫ״̬��flag!
    if(s[num+num].flag&&s[num+num+1].flag)
        s[num].flag=1;
}
 
int main(){
    int cas,n,i,j;
    scanf("%d",&cas);
    while(cas--){
        memset(vs,0,sizeof(vs));
        ans=0;
        scanf("%d",&n);
        for(i=1;i<=n;i++)
            scanf("%d%d",&t[i].x,&t[i].y);
                //�����ұ߽�Ĵ����sim[]����һ�ߣ��Ա��������ɢ������
        for(i=1;i<=n;i++){
            sim[i]=t[i].x;
        }
        for(i=n+1,j=1;j<=n;j++,i++){
            sim[i]=t[j].y;
        }
        sort(sim+1,sim+1+2*n,cmp);//��������
                //ȥ���ظ��ı߽�ֵ
        N[1]=sim[1];
        times=1;
        for(i=2;i<=2*n;i++){
            if(N[times]!=sim[i])
                N[++times]=sim[i];
        }
        Build(1,times,1);
        int color=0;
        for(i=n;i>=1;i--){
            int sx=getidex(t[i].x);
                 //�Ա߽�ֵ��sim[]�����λ�ã���Ϊ��ǰ�ı߽�ֵ���������ɢ�ĺ���˼�룡
            int sy=getidex(t[i].y);
            modify(sx,sy,1,++color);
        }
        printf("%d\n",ans);
    }
    return 0;
}
//*/


    #include<iostream>
  2 #include<cstdio>
  3 #include<algorithm>
  4 #include<string.h>
  5 #define MAX 20001
  6 
  7 using namespace std;
  8 
  9 int c,n,ls[MAX];

 10 struct node{
 11     int l,r;
 12     int c;
 13 }tree[MAX*4];

 14 struct ln{
 15     int li,num;//num��ʾ�ڼ��ź���
 16 }line[MAX];

 17 int set[MAX][2];
 18 bool visit[MAX];
 19 int ans;
 20 
 21 bool cmp(struct ln a,struct ln b){
 22     return a.li<b.li;
 23 }
 24 
 25 void Inittree(int pos,int ll,int rr){
 26     tree[pos].l = ll;
 27     tree[pos].r = rr;
 28     tree[pos].c = 0;
 29     if(ll!=rr){
 30         int mid = (ll+rr)>>1;
 31         Inittree(pos*2,ll,mid);
 32         Inittree(pos*2+1,mid+1,rr);
 33     }
 34 }
 35 
 36 void Insert(int pos,int ll,int rr,int color){
 37     if(tree[pos].l == ll && tree[pos].r == rr){
 38         tree[pos].c = color;
 39         return;
 40     }
 41     if(tree[pos].c > 0 && tree[pos].c != color){
 42         tree[pos*2].c = tree[pos].c;
 43         tree[pos*2+1].c = tree[pos].c;
 44         tree[pos].c = 0;
 45     }
 46     int mid = (tree[pos].l + tree[pos].r)>>1;
 47     if(rr<=mid){
 48         Insert(pos*2,ll,rr,color);
 49     }
 50     else if(ll>mid){
 51         Insert(pos*2+1,ll,rr,color);
 52     }
 53     else{
 54         Insert(pos*2,ll,mid,color);
 55         Insert(pos*2+1,mid+1,rr,color);
 56     }
 57 }
 58 
 59 void Search(int pos){
 60     if(tree[pos].c!=0){
 61         if(!visit[tree[pos].c]){//tree[pos].c
 62             visit[tree[pos].c] = true;
 63             ans++;
 64         }
 65         return ;
 66     }
 67     Search(2*pos);
 68     Search(2*pos+1);
 69 }
 70 
 71 int main()
 72 {
 73     int i;
 74     while(scanf("%d",&c)!=EOF){
 75         while(c--){
 76             scanf("%d",&n);
 77             for(i = 0;i < n;++i){//��ɢ��
 78                 scanf("%d%d",&set[i][0],&set[i][1]);
 79                 line[2*i].li = set[i][0];
 80                 line[2*i].num = -(i+1);//�ø�����ʾ �߶����
 81                 line[2*i+1].li = set[i][1];
 82                 line[2*i+1].num = i+1;
 83             }
 84             sort(line,line+2*n,cmp);
 85             int temp = line[0].li,tp = 1;
 86             for(i = 0;i < 2*n;++i){
 87                 if(line[i].li != temp){
 88                     tp++;
 89                     temp = line[i].li;
 90                 }
 91                 if(line[i].num < 0){
 92                     set[-line[i].num-1][0] = tp;
 93                 }
 94                 else{
 95                     set[line[i].num-1][1] = tp;
 96                 }
 97             }//��ɢ��
 98         
 99             Inittree(1,1,tp);
100             for(i = 0;i < n;++i){
101                 Insert(1,set[i][0],set[i][1],i+1);
102             }
103             memset(visit,0,sizeof(visit));
104             ans = 0;
105             Search(1);
106             printf("%d\n",ans);
107         }
108     }
109     return 0;
110 }