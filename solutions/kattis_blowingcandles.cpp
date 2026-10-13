#include <bits/stdc++.h>
using namespace std;
typedef long long ll;typedef pair<ll,ll> P;
ll cr(P o,P a,P b){return (a.first-o.first)*(b.second-o.second)-(a.second-o.second)*(b.first-o.first);}
int main(){int n;ll R;scanf("%d %lld",&n,&R);vector<P>p(n);for(auto&q:p)scanf("%lld %lld",&q.first,&q.second);
 sort(p.begin(),p.end());vector<P>h(2*n);int k=0;
 for(int i=0;i<n;i++){while(k>=2&&cr(h[k-2],h[k-1],p[i])<=0)k--;h[k++]=p[i];}
 for(int i=n-2,t=k+1;i>=0;i--){while(k>=t&&cr(h[k-2],h[k-1],p[i])<=0)k--;h[k++]=p[i];}
 h.resize(k-1);int m=h.size();
 if(m<3){printf("0.0000000000\n");return 0;}
 long double best=1e30L;int j=1;
 for(int i=0;i<m;i++){P a=h[i],b=h[(i+1)%m];
  while(cr(a,b,h[(j+1)%m])>cr(a,b,h[j]))j=(j+1)%m;
  long double dx=b.first-a.first,dy=b.second-a.second;
  long double w=(long double)cr(a,b,h[j])/sqrtl(dx*dx+dy*dy);if(w<best)best=w;}
 printf("%.10Lf\n",best);}
