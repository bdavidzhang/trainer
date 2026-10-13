#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;vector<ll> f;
void add(int i,ll v){for(;i<=n;i+=i&-i)f[i]+=v;}
void radd(int l,int r,ll v){if(l>r)return;add(l,v);if(r+1<=n)add(r+1,-v);}
ll get(int i){ll s=0;for(;i>0;i-=i&-i)s+=f[i];return s;}
int main(){ll t;scanf("%d %lld",&n,&t);f.assign(n+2,0);for(int i=1;i<=n;i++){ll a;scanf("%lld",&a);radd(i,i,a);}
 int i=1;
 while(i<=n&&t>0){
  ll v=get(i);
  if(v>0){ // one irregular game simulated directly
   t--;int pos=i;ll w=v;ll hand=v+1;
   while(true){
    radd(pos,pos,-w);
    ll e=pos+hand;int r=(int)min<ll>(n,e);
    radd(pos+1,r,1);
    if(e>n)break;
    ll u=get((int)e)-1;
    if(u==0)break;
    pos=(int)e;w=u+1;hand=w;
   }
  }
  // hole i is now 0: games alternate "put 1" / "pick 2 -> +1 at i+1, game at i+2"
  ll pairs=t/2;
  if(t&1)radd(i,i,1);
  if(i+1<=n)radd(i+1,i+1,pairs);
  t=pairs;i+=2;
 }
 for(int j=1;j<=n;j++)printf("%lld%c",get(j),j<n?' ':'\n');}
