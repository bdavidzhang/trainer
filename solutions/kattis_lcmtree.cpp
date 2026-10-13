#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1000000007;
ll C[30][30],fact[30],ifact[30],ipw2[30];
ll power(ll b,ll e){ ll r=1; b%=MOD; while(e){ if(e&1) r=r*b%MOD; b=b*b%MOD; e>>=1; } return r; }
int D; vector<ll> val; vector<int> mult;
// State string: counts of floating (parentless) subtree roots per distinct value index (D bytes),
// plus within a stage: byte D = a (floating v-nodes created in the latest round), byte D+1 = b (older floating v-nodes).
typedef unordered_map<string,ll> Map;
int J,M,remAfter;
vector<pair<int,int>> prs; // pairs (x,y), x<=y<J with lcm = val[J]
vector<int> dvs;           // indices y<J with val[y] | val[J]
vector<Map> bucket;
static inline void add(Map&m,const string&s,ll w){ ll &r=m[s]; r+=w; if(r>=MOD) r-=MOD; }
// number of ways to pick t disjoint unordered pairs out of c items
ll pairsFrom(int c,int t){ return fact[c]*ifact[c-2*t]%MOD*ifact[t]%MOD*ipw2[t]%MOD; }
bool tooMany(const string&s,int used){
    int f=0; for(unsigned char ch:s) f+=ch;
    return f>remAfter+(M-used)+1;
}
void rec0(string&s,size_t pos,int used,ll w){
    // option: stop choosing pairs, then choose number of leaves
    for(int l=0;used+l<=M;l++){
        if(used+l==0) continue;
        string t=s; t[D]=(char)(used+l);
        if(tooMany(t,used+l)) continue;
        add(bucket[used+l],t,w*ifact[l]%MOD);
    }
    if(used==M) return;
    for(size_t p=pos;p<prs.size();p++){
        int x=prs[p].first,y=prs[p].second;
        if(x==y){
            int c=s[x];
            for(int t=1;2*t<=c&&used+t<=M;t++){
                s[x]=(char)(c-2*t);
                rec0(s,p+1,used+t,w*pairsFrom(c,t)%MOD);
            }
            s[x]=(char)c;
        } else {
            int cx=s[x],cy=s[y];
            for(int t=1;t<=cx&&t<=cy&&used+t<=M;t++){
                s[x]=(char)(cx-t); s[y]=(char)(cy-t);
                rec0(s,p+1,used+t,w*C[cx][t]%MOD*C[cy][t]%MOD*fact[t]%MOD);
            }
            s[x]=(char)cx; s[y]=(char)cy;
        }
    }
}
// round >=1: arem = remaining items of the newest layer, k = nodes created this round so far
void recR(string&s,size_t pos,int arem,int bOld,int used,int k,ll w){
    if(k>0){
        string t=s; t[D]=(char)k; t[D+1]=(char)(arem+bOld);
        if(!tooMany(t,used)) add(bucket[used],t,w);
    }
    if(used==M||arem==0) return;
    for(size_t p=pos;p<dvs.size();p++){
        int y=dvs[p]; int c=s[y];
        for(int t=1;t<=c&&t<=arem&&used+t<=M;t++){
            s[y]=(char)(c-t);
            recR(s,p+1,arem-t,bOld,used+t,k+t,w*C[arem][t]%MOD*C[c][t]%MOD*fact[t]%MOD);
        }
        s[y]=(char)c;
    }
}
int main(){
    for(int i=0;i<30;i++){ C[i][0]=1; for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD; }
    fact[0]=1; for(int i=1;i<30;i++) fact[i]=fact[i-1]*i%MOD;
    ll i2=power(2,MOD-2); ipw2[0]=1;
    for(int i=0;i<30;i++){ ifact[i]=power(fact[i],MOD-2); if(i) ipw2[i]=ipw2[i-1]*i2%MOD; }
    int n; scanf("%d",&n);
    vector<ll> a(n); for(auto&x:a) scanf("%lld",&x);
    sort(a.begin(),a.end());
    for(int i=0;i<n;i++){ if(i&&a[i]==a[i-1]) mult.back()++; else { val.push_back(a[i]); mult.push_back(1); } }
    D=val.size();
    Map cur; cur[string(D+2,'\0')]=1;
    int rem=n;
    for(int j=0;j<D;j++){
        J=j; M=mult[j]; rem-=M; remAfter=rem;
        prs.clear(); dvs.clear();
        for(int x=0;x<j;x++){
            if(val[j]%val[x]==0) dvs.push_back(x);
            for(int y=x;y<j;y++){ ll g=std::gcd(val[x],val[y]); if(val[x]/g*val[y]==val[j]) prs.push_back({x,y}); }
        }
        bucket.assign(M+1,Map());
        for(auto&kv:cur){ string s=kv.first; rec0(s,0,0,kv.second); }
        for(int u=1;u<M;u++){
            for(auto&kv:bucket[u]){
                string s=kv.first; int A=s[D],B=s[D+1];
                if(A==0) continue;
                s[D]=0; s[D+1]=0;
                for(int t1=0;2*t1<=A&&u+t1<=M;t1++){
                    ll w1=kv.second*pairsFrom(A,t1)%MOD; int a1=A-2*t1;
                    for(int t2=0;t2<=a1&&t2<=B&&u+t1+t2<=M;t2++){
                        ll w2=w1*C[a1][t2]%MOD*C[B][t2]%MOD*fact[t2]%MOD;
                        recR(s,0,a1-t2,B-t2,u+t1+t2,t1+t2,w2);
                    }
                }
            }
            bucket[u].clear();
        }
        Map nxt;
        for(auto&kv:bucket[M]){
            string s=kv.first; s[j]=(char)(s[D]+s[D+1]); s[D]=0; s[D+1]=0;
            add(nxt,s,kv.second);
        }
        cur.swap(nxt);
    }
    ll T=0;
    for(auto&kv:cur){ int f=0; for(unsigned char ch:kv.first) f+=ch; if(f==1) T=(T+kv.second)%MOD; }
    for(int j=0;j<D;j++) T=T*fact[mult[j]]%MOD;
    printf("%lld\n",T);
}
