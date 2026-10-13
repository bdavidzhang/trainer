#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
typedef long long ll;
const u64 MD=(1ULL<<61)-1;
static inline u64 mulm(u64 a,u64 b){__uint128_t t=(__uint128_t)a*b;u64 r=(u64)(t&MD)+(u64)(t>>61);if(r>=MD)r-=MD;return r;}
struct HT{vector<u64> k;vector<int> v;vector<char> used;u64 mask;
 void init(int lg){k.assign(1<<lg,0);v.assign(1<<lg,0);used.assign(1<<lg,0);mask=(1ULL<<lg)-1;}
 static inline u64 mix(u64 x){x^=x>>31;x*=0x9E3779B97F4A7C15ULL;x^=x>>29;return x;}
 void add(u64 key){u64 p=mix(key)&mask;while(used[p]&&k[p]!=key)p=(p+1)&mask;used[p]=1;k[p]=key;v[p]++;}
 inline int get(u64 key)const{u64 p=mix(key)&mask;while(used[p]){if(k[p]==key)return v[p];p=(p+1)&mask;}return 0;}
};
u64 pw[128];
struct H{vector<u64> f,r;int L; // f: prefix hashes of s, r: prefix hashes of reverse(s)
 void build(const string&s){L=s.size();f.assign(L+1,0);r.assign(L+1,0);
  for(int i=0;i<L;i++){f[i+1]=mulm(f[i],pw[1])+(unsigned char)s[i]+1;if(f[i+1]>=MD)f[i+1]-=MD;}
  for(int i=0;i<L;i++){r[i+1]=mulm(r[i],pw[1])+(unsigned char)s[L-1-i]+1;if(r[i+1]>=MD)r[i+1]-=MD;}}
 inline u64 sub(const vector<u64>&h,int a,int b)const{u64 x=h[b]+MD-mulm(h[a],pw[b-a]);if(x>=MD)x-=MD;return x;}
 inline u64 fw(int a,int b)const{return sub(f,a,b);}
 inline u64 rv(int a,int b)const{return sub(r,L-b,L-a);} // hash of reverse(s[a:b))
 inline bool pal(int a,int b)const{return fw(a,b)==rv(a,b);}
};
const ll MOD=1000000007;
// counts triples (A,B,C) with |A|>|C| (or >= if incEq) and A+B+C palindrome
ll solve(const vector<string>&v,bool incEq){
 int n=v.size();vector<H> hs(n);size_t tot=0;for(int i=0;i<n;i++){hs[i].build(v[i]);tot+=v[i].size();}
 HT T1,T2;int lg1=1;while((1u<<lg1)<2*(size_t)n+16)lg1++;int lg2=1;while((1u<<lg2)<2*tot+16)lg2++;
 T1.init(lg1);T2.init(lg2);
 for(int i=0;i<n;i++){const H&h=hs[i];int L=h.L;T1.add(h.r[L]);
  // B = P + Y, P nonempty palindrome prefix of length L-l, Y length l; key = hash(rev(Y)) = prefix of rev(B) of length l
  for(int l=0;l<L;l++)if(h.pal(0,L-l))T2.add(h.r[l]);}
 ll ans=0;vector<int> ends;
 for(int i=0;i<n;i++){const H&h=hs[i];int L=h.L;ends.clear();
  for(int e=1;e<=L;e++)if(e==L||h.pal(e,L))ends.push_back(e);
  int top=incEq?L:L-1;
  for(int pos=1;pos<=top;pos++){ll w=T1.get(h.f[pos]);if(!w)continue;
   ll g=T2.get(h.fw(pos,L));
   for(int e:ends)if(e>pos)g+=T1.get(h.fw(pos,e));
   ans=(ans+(w%MOD)*(g%MOD))%MOD;}}
 return ans;}
int main(){mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
 u64 base=rng()%(MD-1000)+500;pw[0]=1;for(int i=1;i<128;i++)pw[i]=mulm(pw[i-1],base);
 int n;if(!(cin>>n))return 0;vector<string> v(n);for(auto&s:v)cin>>s;
 ll a=solve(v,true);for(auto&s:v)reverse(s.begin(),s.end());a=(a+solve(v,false))%MOD;
 printf("%lld\n",a);}
