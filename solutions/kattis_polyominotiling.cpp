#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef unsigned long long ull;
int k,n; string s; vector<int> L;
static inline char comp(char c){ return c=='u'?'d':c=='d'?'u':c=='l'?'r':'l'; }
static inline bool mt(int x,int y){ x%=k; if(x<0)x+=k; y%=k; if(y<0)y+=k; return s[y]==comp(s[x]); }
static inline bool valid(int p,int q){ return q-p<=L[(p+q-1)%k]; }
int main(){
    cin>>k>>s; if(k%2){puts("0");return 0;} n=k/2;
    L.assign(k,0);
    for(int c=0;c<k;c++){
        if(c%2==0){ int m=c/2; if(!mt(m,m+n)) continue; int len=1;
            for(int t=1;2*t+1<=n;t++){ if(mt(m-t,m+t+n)&&mt(m+t,m-t+n)) len=2*t+1; else break; }
            L[c]=len;
        } else { int lo=(c+1)/2,hi=(c-1)/2; int len=0;
            for(int t=1;2*t<=n;t++){ int x1=lo-t,x2=hi+t; if(mt(x1,x2+n)&&mt(x2,x1+n)) len=2*t; else break; }
            L[c]=len;
        }
    }
    int W=k/64+1;
    vector<ull> F((size_t)k*W,0);
    for(int i=0;i<k;i++){ ull* f=&F[(size_t)i*W]; int top=min(i+n,k-1); for(int e=i+1;e<=top;e++) if(valid(i,e)) f[e>>6]|=1ULL<<(e&63); }
    ll cnt=0; vector<ull> E(W);
    for(int st=0;st<n;st++){
        for(int a=1;a<n;a++) if(valid(st,st+a)&&valid(st+a,st+n)) cnt++;
        fill(E.begin(),E.end(),0); bool any=false;
        for(int e=st+2;e<=st+n-1;e++) if(valid(e,st+n)){ E[e>>6]|=1ULL<<(e&63); any=true; }
        if(!any) continue;
        int hw=(st+n-1)>>6;
        for(int i=st+1;i<=st+n-2;i++) if(valid(st,i)){
            const ull* f=&F[(size_t)i*W]; ll c=0;
            for(int w=i>>6;w<=hw;w++) c+=__builtin_popcountll(f[w]&E[w]);
            cnt+=c;
        }
    }
    printf("%lld\n",2*cnt);
}
