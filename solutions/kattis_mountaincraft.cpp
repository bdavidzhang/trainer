#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> xs;vector<int> cnt;vector<ll> len;
void upd(int o,int l,int r,int a,int b,int v){
    if(a>=r||b<=l)return;
    if(a<=l&&r<=b)cnt[o]+=v;
    else{int m=(l+r)/2;upd(2*o,l,m,a,b,v);upd(2*o+1,m,r,a,b,v);}
    if(cnt[o]>0)len[o]=xs[r]-xs[l];
    else if(r-l==1)len[o]=0;
    else len[o]=len[2*o]+len[2*o+1];
}
int main(){int q;ll w;scanf("%d %lld",&q,&w);vector<pair<ll,ll>> qs(q),pk(q);int qi=0;
 for(auto&[l,r]:qs){ll x,y;scanf("%lld %lld",&x,&y);pk[qi++]={x,y};l=max(0LL,x-y);r=min(w,x+y);xs.push_back(l);xs.push_back(r);}
 sort(xs.begin(),xs.end());xs.erase(unique(xs.begin(),xs.end()),xs.end());
 int n=xs.size();cnt.assign(4*n+4,0);len.assign(4*n+4,0);
 set<pair<ll,ll>> on;const double s2=sqrt(2.0);
 for(int i=0;i<q;i++){ll x=pk[i].first,y=pk[i].second;
  int a=lower_bound(xs.begin(),xs.end(),qs[i].first)-xs.begin(),b=lower_bound(xs.begin(),xs.end(),qs[i].second)-xs.begin();
  int v;if(on.count({x,y})){on.erase({x,y});v=-1;}else{on.insert({x,y});v=1;}
  if(n>1)upd(1,0,n-1,a,b,v);
  printf("%.6f\n",(n>1?len[1]:0)*s2);}
}
