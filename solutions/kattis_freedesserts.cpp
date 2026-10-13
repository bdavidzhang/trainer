#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,p[20],pm;int pw3[11];
vector<ll> memo;
// state: position i (MSB first), c = carry this position must emit upward
ll f(int i,int c,int aS,int bS,int mA,int mB,int code){
 if(i==n)return (c==0&&aS&&bS)?1:0;
 size_t idx=((((size_t)i*2+c)*2+aS)*2+bS)*59049+code;
 if(memo[idx]>=0)return memo[idx];
 ll r=0;
 for(int da=0;da<10;da++){
  int naS=aS||da>0;
  if(naS&&((pm>>da&1)||(mB>>da&1)))continue;
  for(int cin=0;cin<2;cin++){
   int db=p[i]+10*c-cin-da;
   if(db<0||db>9)continue;
   int nbS=bS||db>0;
   if(nbS&&((pm>>db&1)||db==da&&naS||(mA>>db&1)))continue;
   if(naS&&nbS&&da==db)continue;
   int nmA=mA,nmB=mB,nc=code;
   if(naS&&!(nmA>>da&1)){nmA|=1<<da;nc+=pw3[da];}
   if(nbS&&!(nmB>>db&1)){nmB|=1<<db;nc+=2*pw3[db];}
   r+=f(i+1,cin,naS,nbS,nmA,nmB,nc);
  }
 }
 return memo[idx]=r;
}
struct St{int c,bS,mB,code;};
ll P;int lim;string out;
void dfs(int i,int aS,int mA,vector<St> sts,ll a){
 if(lim<=0)return;
 if(i==n){ out+=to_string(a)+" "+to_string(P-a)+"\n";lim--;return;}
 for(int da=0;da<10&&lim>0;da++){
  int naS=aS||da>0;
  if(naS&&(pm>>da&1))continue;
  vector<St> ns;ll tot=0;
  for(auto&s:sts){
   if(naS&&(s.mB>>da&1))continue;
   for(int cin=0;cin<2;cin++){
    int db=p[i]+10*s.c-cin-da;
    if(db<0||db>9)continue;
    int nbS=s.bS||db>0;
    if(nbS&&((pm>>db&1)||(mA>>db&1)))continue;
    if(naS&&nbS&&da==db)continue;
    int nmA=mA,nmB=s.mB,nc=s.code;
    // code must reflect a's mask too; recompute a part below
    if(naS&&!(nmA>>da&1)){nmA|=1<<da;nc+=pw3[da];}
    if(nbS&&!(nmB>>db&1)){nmB|=1<<db;nc+=2*pw3[db];}
    ll v=f(i+1,cin,naS,nbS,nmA,nmB,nc);
    if(v>0){tot+=v;ns.push_back({cin,nbS,nmB,nc});}
   }
  }
  if(tot>0){int nmA=mA;if(naS)nmA|=1<<da;dfs(i+1,naS,nmA,ns,a*10+da);}
 }
}
int main(){cin>>P;string s=to_string(P);n=s.size();pw3[0]=1;for(int i=1;i<11;i++)pw3[i]=pw3[i-1]*3;
 for(int i=0;i<n;i++){p[i]=s[i]-'0';pm|=1<<p[i];}
 memo.assign((size_t)(n+1)*8*59049,-1);
 ll tot=f(0,0,0,0,0,0,0)/2;
 printf("%lld\n",tot);
 lim=(int)min<ll>(tot,5000);
 dfs(0,0,0,{{0,0,0,0}},0);
 fputs(out.c_str(),stdout);
}
