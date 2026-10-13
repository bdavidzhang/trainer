#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll CAP=4000000000000000000LL;
static char buf[1000005];
int main(){
    scanf("%s",buf); string S=buf;
    string T[26];
    for(int i=0;i<26;i++){scanf("%s",buf);T[i]=buf;}
    ll K; int M; scanf("%lld %d",&K,&M);
    const int D=60;
    int kk=(int)min<ll>(K,D);
    // len[d][c]
    vector<array<ll,26>> len(kk+1);
    for(int c=0;c<26;c++) len[0][c]=1;
    for(int d=1;d<=kk;d++) for(int c=0;c<26;c++){
        ll s=0; for(char ch:T[c]){s+=len[d-1][ch-'a']; if(s>CAP){s=CAP;break;}}
        len[d][c]=s;
    }
    string base;
    if(K<=D) base=S;
    else{
        ll steps=K-D; int c=S[0]-'a';
        // cycle detection on functional graph c -> T[c][0]
        vector<ll> seen(26,-1); ll t=0;
        while(t<steps){
            if(seen[c]>=0){ll cyc=t-seen[c]; ll rem=(steps-t)%cyc; for(ll i=0;i<rem;i++) c=T[c][0]-'a'; t=steps; break;}
            seen[c]=t; c=T[c][0]-'a'; t++;
        }
        base=string(1,(char)('a'+c));
    }
    vector<ll> pre(base.size()+1,0);
    for(size_t i=0;i<base.size();i++){pre[i+1]=min(CAP,pre[i]+len[kk][base[i]-'a']);}
    while(M--){
        ll m; scanf("%lld",&m);
        // find first i with pre[i+1]>=m
        size_t i=lower_bound(pre.begin()+1,pre.end(),m)-pre.begin()-1;
        ll off=m-pre[i]; int c=base[i]-'a';
        for(int d=kk;d>0;d--){
            for(char ch:T[c]){
                ll l=len[d-1][ch-'a'];
                if(off<=l){c=ch-'a';break;}
                off-=l;
            }
        }
        printf("%c\n",'a'+c);
    }
}
