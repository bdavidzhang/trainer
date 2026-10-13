#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n;scanf("%d",&n);vector<ll>x(n),y(n),k(n);
 for(int i=0;i<n;i++){scanf("%lld %lld",&x[i],&y[i]);k[i]=(x[i]<<32)|y[i];}
 sort(k.begin(),k.end());
 vector<pair<ll,ll>>off;const ll R=2018;
 for(ll dx=-R;dx<=R;dx++){ll r=R*R-dx*dx;ll dy=(ll)llround(sqrt((double)r));if(dy*dy!=r)continue;off.push_back({dx,dy});if(dy)off.push_back({dx,-dy});}
 ll cnt=0;const ll LIM=1LL<<31;
 for(int i=0;i<n;i++)for(auto [dx,dy]:off){ll a=x[i]+dx,b=y[i]+dy;if(a<0||b<0||a>=LIM||b>=LIM)continue;
  if(binary_search(k.begin(),k.end(),(a<<32)|b))cnt++;}
 printf("%lld\n",cnt/2);}
