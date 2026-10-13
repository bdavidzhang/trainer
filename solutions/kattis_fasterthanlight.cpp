#include <bits/stdc++.h>
using namespace std;
typedef long long ll;typedef __int128 LL;typedef pair<ll,ll> P;
static LL cross(P o,P a,P b){return (LL)(a.first-o.first)*(b.second-o.second)-(LL)(a.second-o.second)*(b.first-o.first);}
// upper hull, strictly convex, x strictly increasing
static vector<P> upperHull(vector<P> v){sort(v.begin(),v.end());vector<P>t;
 for(size_t i=0;i<v.size();i++){if(i+1<v.size()&&v[i+1].first==v[i].first)continue; // keep max y per x
  t.push_back(v[i]);}
 vector<P>h;for(auto&p:t){while(h.size()>=2&&cross(h[h.size()-2],h.back(),p)>=0)h.pop_back();h.push_back(p);}return h;}
// max over hull of y*dx - dy*x (dx>0)
static LL best(const vector<P>&h,ll dx,ll dy){int lo=0,hi=(int)h.size()-1;auto f=[&](int i){return (LL)h[i].second*dx-(LL)dy*h[i].first;};
 while(lo<hi){int m=(lo+hi)/2;if(f(m+1)>f(m))lo=m+1;else hi=m;}return f(lo);}
// exists line with all of A weakly above and all of B weakly below
static bool sep(const vector<P>&A,const vector<P>&B){
 ll maxAx=LLONG_MIN,minAx=LLONG_MAX,maxBx=LLONG_MIN,minBx=LLONG_MAX;
 for(auto&p:A){maxAx=max(maxAx,p.first);minAx=min(minAx,p.first);}
 for(auto&p:B){maxBx=max(maxBx,p.first);minBx=min(minBx,p.first);}
 if(maxAx<=minBx||maxBx<=minAx)return true;
 vector<P>hb=upperHull(B);vector<P>An=A;for(auto&p:An)p.second=-p.second;vector<P>ha=upperHull(An); // lower hull of A, y negated
 // f(a)=max_B(y-ax)+max_A(-y+ax) ; for A-negated points (x,-y): max(-y + a x) = max over (x,y') of y' - (-a) x
 auto test=[&](ll dx,ll dy){LL v=best(hb,dx,dy)+best(ha,dx,-dy);return v<=0;};
 for(size_t i=0;i+1<hb.size();i++){if(test(hb[i+1].first-hb[i].first,hb[i+1].second-hb[i].second))return true;}
 for(size_t i=0;i+1<ha.size();i++){if(test(ha[i+1].first-ha[i].first,-(ha[i+1].second-ha[i].second)))return true;}
 return false;}
int main(){int n;scanf("%d",&n);vector<P>tl(n),br(n),tr(n),bl(n);
 for(int i=0;i<n;i++){ll a,b,c,d;scanf("%lld %lld %lld %lld",&a,&b,&c,&d);ll x1=min(a,c),x2=max(a,c),y1=min(b,d),y2=max(b,d);
  tl[i]={x1,y2};br[i]={x2,y1};tr[i]={-x2,y2};bl[i]={-x1,y1};}
 // mirrored in x: top-left becomes (-x2,y2), bottom-right becomes (-x1,y1)
 puts(sep(tl,br)||sep(tr,bl)?"possible":"impossible");}
