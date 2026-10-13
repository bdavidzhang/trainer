#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
static const ull MOD=(1ULL<<61)-1;
static inline ull mulmod(ull a,ull b){__uint128_t t=(__uint128_t)a*b;ull r=(ull)(t&MOD)+(ull)(t>>61);if(r>=MOD)r-=MOD;return r;}
int main(){
    static char buf[200005];
    scanf("%s",buf); string s=buf; int n=s.size();
    int q; scanf("%d",&q);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    ull B=rng()%(MOD-1000)+500;
    vector<ull> pw(n+2); pw[0]=1; for(int i=1;i<=n+1;i++) pw[i]=mulmod(pw[i-1],B);
    vector<ull> pre(n+1,0); for(int i=0;i<n;i++){ull v=mulmod(pre[i],B)+(ull)(s[i]-'a'+1); if(v>=MOD)v-=MOD; pre[i+1]=v;}
    // group queries by length
    map<int,vector<array<ull,3>>> byLen; // hash,k,idx
    vector<int> ans(q,-1);
    for(int i=0;i<q;i++){
        int k; scanf("%s %d",buf,&k);
        int L=strlen(buf);
        if(L>n) continue;
        ull hv=0; for(int j=0;j<L;j++){hv=mulmod(hv,B)+(ull)(buf[j]-'a'+1); if(hv>=MOD)hv-=MOD;}
        byLen[L].push_back({hv,(ull)k,(ull)i});
    }
    for(auto &pr:byLen){
        int L=pr.first; auto &v=pr.second;
        sort(v.begin(),v.end());
        int m=v.size();
        // distinct hashes -> groups [st,en)
        vector<ull> keys; vector<int> st;
        for(int i=0;i<m;i++) if(i==0||v[i][0]!=v[i-1][0]){keys.push_back(v[i][0]);st.push_back(i);}
        int g=keys.size(); st.push_back(m);
        int cap=4; while(cap<2*g) cap<<=1;
        vector<int> tab(cap,-1);
        for(int i=0;i<g;i++){int p=(int)((keys[i]*0x9E3779B97F4A7C15ULL)>>40)&(cap-1); while(tab[p]>=0)p=(p+1)&(cap-1); tab[p]=i;}
        vector<int> cnt(g,0),ptr(st.begin(),st.begin()+g);
        int remaining=g;
        ull pL=pw[L];
        for(int i=0;i+L<=n&&remaining>0;i++){
            ull hv=pre[i+L]+MOD-mulmod(pre[i],pL); if(hv>=MOD)hv-=MOD;
            int p=(int)((hv*0x9E3779B97F4A7C15ULL)>>40)&(cap-1);
            while(tab[p]>=0&&keys[tab[p]]!=hv)p=(p+1)&(cap-1);
            if(tab[p]<0) continue;
            int id=tab[p];
            if(ptr[id]>=st[id+1]) continue;
            cnt[id]++;
            while(ptr[id]<st[id+1]&&v[ptr[id]][1]==(ull)cnt[id]){ans[v[ptr[id]][2]]=i+1;ptr[id]++; if(ptr[id]==st[id+1])remaining--;}
        }
    }
    string out; for(int i=0;i<q;i++){out+=to_string(ans[i]);out+='\n';}
    fputs(out.c_str(),stdout);
}
