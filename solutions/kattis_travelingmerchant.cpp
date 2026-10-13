#include <bits/stdc++.h>
using namespace std;
// 14 segment trees: for each start residue c (mod 7) and direction, the price each town
// would have on the day it is visited. Node = (min, max, best profit buy-left/sell-right
// for eastward trees, buy-right/sell-left for westward trees).
struct Nd{int mn,mx,b;};
static const int MUL[7]={0,1,2,3,2,1,0};
int n,sz;vector<Nd> tr[14];
static inline Nd comb(const Nd&l,const Nd&r,bool east){Nd o;o.mn=min(l.mn,r.mn);o.mx=max(l.mx,r.mx);
 o.b=max(l.b,r.b);o.b=max(o.b,east? r.mx-l.mn : l.mx-r.mn);return o;}
int main(){scanf("%d",&n);vector<long long>v(n),d(n);for(int i=0;i<n;i++)scanf("%lld %lld",&v[i],&d[i]);
 sz=1;while(sz<n)sz<<=1;
 for(int k=0;k<14;k++){int c=k%7;bool east=k<7;auto&t=tr[k];t.assign(2*sz,Nd{INT_MAX,INT_MIN,0});
  for(int i=0;i<n;i++){int day=east?(((i-c)%7)+7)%7:(((c-i)%7)+7)%7;int p=(int)(v[i]+MUL[day]*d[i]);t[sz+i]=Nd{p,p,0};}
  for(int i=sz-1;i>=1;i--){const Nd&l=t[2*i],&r=t[2*i+1];
   if(l.mn==INT_MAX)t[i]=r;else if(r.mn==INT_MAX)t[i]=l;else t[i]=comb(l,r,east);}}
 int q;scanf("%d",&q);while(q--){int s,t;scanf("%d %d",&s,&t);s--;t--;bool east=s<t;int k=(s%7)+(east?0:7);
  auto&T=tr[k];int l=min(s,t)+sz,r=max(s,t)+sz+1;Nd L{0,0,0},R{0,0,0};bool hl=false,hr=false;
  while(l<r){if(l&1){const Nd&x=T[l++];if(x.mn!=INT_MAX){L=hl?comb(L,x,east):x;hl=true;}}
   if(r&1){const Nd&x=T[--r];if(x.mn!=INT_MAX){R=hr?comb(x,R,east):x;hr=true;}}l>>=1;r>>=1;}
  Nd res=hl&&hr?comb(L,R,east):(hl?L:R);printf("%d\n",max(res.b,0));}}
