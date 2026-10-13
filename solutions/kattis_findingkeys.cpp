#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
static const ull MOD=(1ULL<<61)-1;
static ull mulmod(ull a,ull b){ __uint128_t t=(__uint128_t)a*b; ull r=(ull)(t&MOD)+(ull)(t>>61); if(r>=MOD) r-=MOD; return r; }
int n; vector<ull> H,P;
static inline ull get(int l,int len){ ull r=H[l+len]+MOD-mulmod(H[l],P[len]); if(r>=MOD) r-=MOD; return r; }
vector<int> s;
static int lcp(int a,int b){ int lo=0,hi=n; while(lo<hi){int mid=(lo+hi+1)/2; if(get(a,mid)==get(b,mid)) lo=mid; else hi=mid-1;} return lo; }
int main(){
    scanf("%d",&n);
    vector<long long> a(n);
    for(auto&x:a) scanf("%lld",&x);
    s.resize(2*n);
    for(int i=0;i<2*n;i++) s[i]= a[i%n]<a[(i+1)%n] ? 1:2;
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    ull B=rng()%(MOD-1000)+500;
    H.assign(2*n+1,0); P.assign(2*n+1,1);
    for(int i=0;i<2*n;i++){ H[i+1]=mulmod(H[i],B)+s[i]; if(H[i+1]>=MOD) H[i+1]-=MOD; P[i+1]=mulmod(P[i],B);}    
    // packed first min(64,n) symbols of each rotation, MSB first, for a fast path
    int K=min(64,n); vector<ull> W(n); { ull cur=0; for(int t=0;t<K;t++) cur=(cur<<1)|(ull)(s[t]==2); ull top=K==64?~0ULL:((1ULL<<K)-1);
      for(int i=0;i<n;i++){ W[i]=cur; cur=((cur<<1)|(ull)(s[i+K]==2))&top; } }
    vector<int> ord(n); iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int x,int y){ if(W[x]!=W[y]) return W[x]<W[y]; if(x==y) return false; int l=lcp(x,y); if(l>=n) return false; return s[x+l]<s[y+l]; });
    vector<int> best(n,0);
    for(int i=0;i+1<n;i++){ int l=lcp(ord[i],ord[i+1]); best[ord[i]]=max(best[ord[i]],l); best[ord[i+1]]=max(best[ord[i+1]],l);}    
    for(int i=0;i<n;i++) printf("%d\n", best[i]>=n?-1:best[i]+1);
}
