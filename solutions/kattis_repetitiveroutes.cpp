#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int m;vector<int> bit;
void upd(int i,int v){for(;i<=m;i+=i&-i)bit[i]+=v;}
int qry(int i){int s=0;for(;i>0;i-=i&-i)s+=bit[i];return s;}
int main(){int n;scanf("%d",&n);m=2*n;bit.assign(m+1,0);
 vector<int> st(n+1,0),last(m+1,0);ll ans=0;
 for(int k=1;k<=m;k++){int c,l;scanf("%d %d",&c,&l);
  if(last[l])upd(last[l],-1);upd(k,1);last[l]=k;
  if(!st[c])st[c]=k;else{int a=st[c];int distinct=qry(k)-qry(a-1);ans+=(k-a+1)-distinct;}
 }
 printf("%lld\n",ans);}
