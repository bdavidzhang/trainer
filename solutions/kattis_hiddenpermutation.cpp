#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 L;
int main(){
    int N,K; if(!(cin>>N>>K)) return 0;
    vector<ll> p(K); for(auto &x:p) cin>>x;
    vector<L> m(K);
    L tot=0;
    for(int i=0;i<K;i++){ string s; cin>>s; L v=0; for(char c:s) v=v*10+(c-'0'); m[i]=v; tot+=v; }
    auto fail=[](){ puts("impossible"); exit(0); };
    if(tot!=((L)1<<N)) fail();
    // F(d) = #strings fixed by f^d = 2^{sum over cycles gcd(c,d)} = sum of m_i with p_i | d
    vector<ll> G(N+1,0);
    for(int d=1;d<=N;d++){
        L F=0; for(int i=0;i<K;i++) if(d%p[i]==0) F+=m[i];
        if(F<=0||(F&(F-1))) fail();
        int e=0; while(((L)1<<e)<F) e++;
        G[d]=e;
    }
    vector<int> mu(N+1,0),phi(N+1,0);
    for(int i=1;i<=N;i++){
        int x=i,mm=1,ph=i; bool sq=false;
        for(int q=2;q*q<=x;q++) if(x%q==0){ int c=0; while(x%q==0){ x/=q; c++; } if(c>1) sq=true; mm=-mm; ph=ph/q*(q-1); }
        if(x>1){ mm=-mm; ph=ph/x*(x-1); }
        mu[i]=sq?0:mm; phi[i]=ph;
    }
    // G(d) = sum_{e|d} phi(e) S(e), S(e) = #cycles with length divisible by e
    vector<ll> S(N+1,0),cnt(N+1,0);
    for(int d=1;d<=N;d++){
        ll X=0; for(int e=1;e<=d;e++) if(d%e==0) X+=mu[d/e]*G[e];
        if(X<0||X%phi[d]) fail();
        S[d]=X/phi[d];
    }
    ll sum=0;
    for(int c=1;c<=N;c++){
        ll v=0; for(int d=c;d<=N;d+=c) v+=mu[d/c]*S[d];
        if(v<0) fail();
        cnt[c]=v; sum+=v*c;
    }
    if(sum!=N) fail();
    vector<pair<ll,ll>> cyc; for(int c=1;c<=N;c++) if(cnt[c]) cyc.push_back({c,cnt[c]});
    auto Gf=[&](ll d){ ll r=0; for(auto &pr:cyc) r+=pr.second*std::gcd(pr.first,d); return r; };
    // verify every given period count by Moebius inversion over divisors of p_i
    for(int i=0;i<K;i++){
        ll x=p[i]; vector<ll> pr;
        for(ll q=2;q*q<=x;q++) if(x%q==0){ pr.push_back(q); while(x%q==0) x/=q; }
        if(x>1) pr.push_back(x);
        int k=pr.size(); L val=0;
        for(int mask=0;mask<(1<<k);mask++){
            ll d=p[i]; int sg=1;
            for(int j=0;j<k;j++) if(mask>>j&1){ d/=pr[j]; sg=-sg; }
            ll g=Gf(d);
            val+=sg*((L)1<<g);
        }
        if(val!=m[i]) fail();
    }
    vector<int> f(N+1); int pos=1;
    for(auto &pr:cyc) for(ll r=0;r<pr.second;r++){
        int c=pr.first;
        for(int j=0;j<c;j++) f[pos+j]=pos+(j+1)%c;
        pos+=c;
    }
    for(int i=1;i<=N;i++) printf("%d%c",f[i],i==N?'\n':' ');
}
