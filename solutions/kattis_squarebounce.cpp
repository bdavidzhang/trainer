#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// fold coordinate (num/den) + 1 offset already included: r = (C+1)*den, returns numerator of folded coord over den
static ll foldc(ll numPlus,ll den){ll r=numPlus%(4*den);if(r<=2*den)return r-den;return 3*den-r;}
static void outp(ll p,ll q){if(p==0){printf("0 1");return;}ll g=std::gcd(llabs(p),q);printf("%lld %lld",p/g,q/g);}
int main(){ll a,b,n;cin>>a>>b>>n;
 // unfolded: u=x+1, y=a*u/b. vertical walls at u=2k (k>=1), horizontal at y=2m+1 (m>=0) i.e. u=(2m+1)b/a
 ll k=1,m=0;bool vert=false;ll idx=0;
 for(ll e=0;e<=n;e++){ // compare 2k vs (2m+1)b/a
  if(2*k*a<(2*m+1)*b){vert=true;idx=k;k++;}else{vert=false;idx=m;m++;}
 }
 if(vert){ll x=(idx&1)?1:-1; // Y=2*idx*a/b ; Y+1=(2*idx*a+b)/b
  ll y=foldc(2*idx*a+b,b);outp(x,1);printf(" ");outp(y,b);puts("");}
 else{ll y=(idx&1)?-1:1; // X+1=(2idx+1)b/a
  ll x=foldc((2*idx+1)*b,a);outp(x,a);printf(" ");outp(y,1);puts("");}
}
