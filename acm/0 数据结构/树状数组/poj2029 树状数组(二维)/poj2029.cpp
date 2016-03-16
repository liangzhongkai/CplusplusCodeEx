#include<iostream>

using namespace std;

#define max 105
int c[max][max];
int n,w,h,x,y,s,t;

int lowbit (int t)
{
 return t&(-t);
}

int sum(int endx,int endy)
{
 int sum=0;
 int temp=endy;
 while(endx>0)
 {
  endy=temp;
  while(endy>0)
  {
   sum+=c[endx][endy];
   endy-=lowbit(endy);
  }
  endx-=lowbit(endx);
 }
 return sum;
}

void add(int addx,int addy,int num)
{
 int temp=addy;
 while(addx<=w)
 {
  addy=temp;
  while(addy<=h)
  {
   c[addx][addy]+=num;
   addy+=lowbit(addy);
  }
  addx+=lowbit(addx);
 }
}

int getsum(int l,int b,int r,int t)
{
    return sum(r,t)-sum(r,b-1)-sum(l-1,t)+sum(l-1,b-1);
}

int main()
{
 
 while(cin>>n,n)
 {
  memset(c,0,sizeof(c));
  cin>>w>>h;
  while(n--)
  {
   scanf("%d%d",&x,&y);
   add(x,y,1);
  }
  cin>>s>>t;
  int cou=0;
  for(int i=1;i<=w-s+1;i++)
  {
   for(int j=1;j<=h-t+1;j++)
   {
    int temp=getsum(i,j,i+s-1,j+t-1);
    if(temp>cou)
    cou=temp;
   }
  }
  cout<<cou<<endl;
 }
 return 0;
}