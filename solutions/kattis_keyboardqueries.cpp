#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
const u64 MOD=(1ULL<<61)-1;
static inline u64 mul(u64 a,u64 b){ __uint128_t t=(__uint128_t)a*b; u64 r=(u64)(t&MOD)+(u64)(t>>61); if(r>=MOD) r-=MOD; return r; }
static inline u64 add(u64 a,u64 b){ u64 r=a+b; if(r>=MOD) r-=MOD; return r; }
static inline u64 sub(u64 a,u64 b){ return a>=b?a-b:a+MOD-b; }
int n,q;
vector<u64> F,R,pw;
void upd(vector<u64>&f,int i,u64 v){ for(i++;i<=n;i+=i&-i) f[i]=add(f[i],v); }
u64 qry(const vector<u64>&f,int i){ u64 s=0; for(;i>0;i-=i&-i) s=add(s,f[i]); return s; } // prefix [0,i)
u64 rng(const vector<u64>&f,int l,int r){ return sub(qry(f,r+1),qry(f,l)); }
int main(){
    scanf("%d %d",&n,&q);
    mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
    u64 base=rnd()%(MOD-1000)+500;
    pw.assign(n+1,1); for(int i=1;i<=n;i++) pw[i]=mul(pw[i-1],base);
    F.assign(n+1,0); R.assign(n+1,0);
    vector<u64> lab(n); vector<int> cls(n); vector<vector<int>> mem(n);
    for(int i=0;i<n;i++){ lab[i]=rnd()%MOD; cls[i]=i; mem[i]={i}; upd(F,i,mul(lab[i],pw[i])); upd(R,i,mul(lab[i],pw[n-1-i])); }
    // forward [a,a+len) equals reversed reading from r downward?
    auto eqrev=[&](int a,int r,int len)->bool{
        u64 h1=rng(F,a,a+len-1), h2=rng(R,r-len+1,r);
        return mul(h1,pw[n-1-r])==mul(h2,pw[a]);
    };
    string out;
    while(q--){
        int t; scanf("%d",&t);
        if(t==1){
            int l,r; scanf("%d %d",&l,&r); l--; r--;
            int len=r-l+1;
            while(!eqrev(l,r,len)){
                int lo=0,hi=len-1; // largest matching prefix length lo
                while(lo<hi){ int mid=(lo+hi+1)/2; if(eqrev(l,r,mid)) lo=mid; else hi=mid-1; }
                int x=cls[l+lo], y=cls[r-lo];
                if(mem[x].size()<mem[y].size()) swap(x,y);
                for(int p:mem[y]){
                    u64 dlt=sub(lab[x],lab[y]);
                    upd(F,p,mul(dlt,pw[p])); upd(R,p,mul(dlt,pw[n-1-p]));
                    cls[p]=x; mem[x].push_back(p);
                }
                vector<int>().swap(mem[y]);
            }
        } else {
            int a,b,x,y; scanf("%d %d %d %d",&a,&b,&x,&y); a--;b--;x--;y--;
            if(b-a!=y-x) out+="Not equal\n";
            else if(mul(rng(F,a,b),pw[x])==mul(rng(F,x,y),pw[a])) out+="Equal\n";
            else out+="Unknown\n";
        }
    }
    fputs(out.c_str(),stdout);
}
