#include <bits/stdc++.h>
using namespace std;
typedef long long ll;typedef __int128 LL;
struct Ln{ll m,b;ll at(ll x)const{return m*x+b;}};
struct Hull{vector<Ln>v;size_t p=0;
 // slopes strictly decreasing, queries increasing, min
 static bool bad(const Ln&a,const Ln&b,const Ln&c){return (LL)(c.b-a.b)*(a.m-b.m)<=(LL)(b.b-a.b)*(a.m-c.m);}
 void add(Ln l){while(v.size()>=p+2&&bad(v[v.size()-2],v.back(),l))v.pop_back();v.push_back(l);}
 bool empty(){return v.empty();}
 ll q(ll x){if(p>=v.size())p=v.size()-1;while(p+1<v.size()&&v[p+1].at(x)<=v[p].at(x))p++;return v[p].at(x);}
};
int main(){int n,m;scanf("%d %d",&n,&m);vector<int>a(m),b(m);vector<ll>s(m),e(m);
vector<array<ll,3>>ev;for(int i=0;i<m;i++){scanf("%d %d %lld %lld",&a[i],&b[i],&s[i],&e[i]);ev.push_back({s[i],0,i});ev.push_back({e[i],1,i});}
sort(ev.begin(),ev.end());vector<Hull>H(n+1);H[1].add({0,0});
const ll INF=LLONG_MAX;vector<ll>dp(m,INF);ll ans=(n==1)?0:INF;
for(auto&x:ev){int i=x[2];if(x[1]==0){if(!H[a[i]].empty())dp[i]=H[a[i]].q(s[i])+s[i]*s[i];}
 else{if(dp[i]==INF)continue;if(b[i]==n)ans=min(ans,dp[i]);H[b[i]].add({-2*e[i],dp[i]+e[i]*e[i]});}}
printf("%lld\n",ans);}
