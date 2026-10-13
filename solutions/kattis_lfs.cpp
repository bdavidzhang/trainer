#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
// f(t) = max count of a single character. A substring occurring f times must start with a
// character c of maximum count and extend every occurrence of c identically, so the answer is
// max over such c of min(r - lastocc + 1, min LCP of consecutive occurrences of c in [l,r]).
static const ull MOD=(1ULL<<61)-1;
static inline ull mulmod(ull a,ull b){ __uint128_t t=(__uint128_t)a*b; ull lo=(ull)(t&MOD), hi=(ull)(t>>61); ull r=lo+hi; if(r>=MOD) r-=MOD; return r; }
int n,q; static char s[500005];
vector<ull> H,PW;
static inline ull gh(int l,int len){ // hash of s[l..l+len)
    ull r=H[l+len]+MOD-mulmod(H[l],PW[len]); if(r>=MOD) r-=MOD; return r;
}
int main(){
    if(scanf("%d %d",&n,&q)!=2) return 0;
    scanf("%s",s);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    ull B=rng()%(MOD-1000)+500;
    H.assign(n+1,0); PW.assign(n+1,1);
    for(int i=0;i<n;i++){ H[i+1]=mulmod(H[i],B)+(ull)(s[i]-'a'+1); if(H[i+1]>=MOD) H[i+1]-=MOD; PW[i+1]=mulmod(PW[i],B); }
    vector<vector<int>> pos(26);
    for(int i=0;i<n;i++) pos[s[i]-'a'].push_back(i);
    // prefix counts
    vector<array<int,26>> cnt(n+1);
    cnt[0].fill(0);
    for(int i=0;i<n;i++){ cnt[i+1]=cnt[i]; cnt[i+1][s[i]-'a']++; }
    // sparse tables of D over consecutive occurrences
    vector<vector<vector<int>>> sp(26);
    for(int c=0;c<26;c++){
        int k=(int)pos[c].size()-1; if(k<=0) continue;
        vector<int> D(k);
        for(int i=0;i<k;i++){
            int a=pos[c][i], b=pos[c][i+1];
            int lo=1, hi=n-b; // lcp in [1, n-b]
            while(lo<hi){ int mid=(lo+hi+1)/2; if(gh(a,mid)==gh(b,mid)) lo=mid; else hi=mid-1; }
            D[i]=lo;
        }
        sp[c].push_back(D);
        for(int j=1;(1<<j)<=k;j++){
            const vector<int>&pr=sp[c][j-1]; vector<int> cur(k-(1<<j)+1);
            for(int i=0;i+(1<<j)<=k;i++) cur[i]=min(pr[i],pr[i+(1<<(j-1))]);
            sp[c].push_back(std::move(cur));
        }
    }
    string out; out.reserve((size_t)q*7);
    for(int qi=0;qi<q;qi++){
        int l,r; scanf("%d %d",&l,&r); // 1-indexed inclusive -> counts cnt[l-1], cnt[r]
        const array<int,26>&A=cnt[l-1]; const array<int,26>&Bc=cnt[r];
        int f=0; for(int c=0;c<26;c++) f=max(f,Bc[c]-A[c]);
        int best=0;
        for(int c=0;c<26;c++) if(Bc[c]-A[c]==f){
            int i=A[c], j=Bc[c]-1; // occurrence indices
            int v=r-pos[c][j]; // (r-1) - pos + 1
            if(j>i){
                int len=j-i; int lg=31-__builtin_clz(len);
                v=min(v,min(sp[c][lg][i],sp[c][lg][j-(1<<lg)]));
            }
            best=max(best,v);
        }
        out+=to_string(best); out+='\n';
    }
    fputs(out.c_str(),stdout);
}
