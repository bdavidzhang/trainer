#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){string s;cin>>s;ll n=s.size();ll tot=n*(n+1)/2;ll sum=0;
 for(int v=1;v<=9;v++){ // substrings with max>=v = tot - substrings all <v
  ll bad=0,run=0;for(char c:s){if(c-'0'<v){run++;bad+=run;}else run=0;}
  sum+=tot-bad;}
 ll w=sum/tot,r=sum%tot;
 if(r==0)printf("%lld\n",w);
 else{ll g=std::gcd(r,tot);if(w)printf("%lld %lld/%lld\n",w,r/g,tot/g);else printf("%lld/%lld\n",r/g,tot/g);}
}
