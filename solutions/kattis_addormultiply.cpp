#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1e9+7;
struct Nd{ bool full; ll pre,mid,suf; }; // full: single product stored in pre
int n,m;
vector<int> val; vector<char> op; // op[i]=1 if '*' between i and i+1 (0-indexed)
vector<array<Nd,2>> t;
static inline Nd mergeN(const Nd&L,const Nd&R,bool mul){
    Nd r;
    if(mul){
        if(L.full&&R.full){r.full=true;r.pre=L.pre*R.pre%MOD;r.mid=r.suf=0;}
        else if(L.full){r.full=false;r.pre=L.pre*R.pre%MOD;r.mid=R.mid;r.suf=R.suf;}
        else if(R.full){r.full=false;r.pre=L.pre;r.mid=L.mid;r.suf=L.suf*R.pre%MOD;}
        else {r.full=false;r.pre=L.pre;r.mid=(L.mid+L.suf*R.pre+R.mid)%MOD;r.suf=R.suf;}
    } else {
        r.full=false; r.pre=L.pre; r.suf=R.full?R.pre:R.suf;
        ll mid=0;
        if(!L.full) mid+=L.mid+L.suf;
        if(!R.full) mid+=R.pre+R.mid;
        r.mid=mid%MOD;
    }
    return r;
}
void pull(int o,int l,int r){
    int md=(l+r)/2;
    bool mul=op[md];
    t[o][0]=mergeN(t[2*o][0],t[2*o+1][0],mul);
    t[o][1]=mergeN(t[2*o][1],t[2*o+1][1],!mul);
}
void build(int o,int l,int r){
    if(l==r){t[o][0]=t[o][1]={true,val[l],0,0};return;}
    int md=(l+r)/2; build(2*o,l,md); build(2*o+1,md+1,r); pull(o,l,r);
}
// refresh leaf p (value) ; or refresh the node whose split is at p (operator)
void updVal(int o,int l,int r,int p){
    if(l==r){t[o][0]=t[o][1]={true,val[l],0,0};return;}
    int md=(l+r)/2; if(p<=md) updVal(2*o,l,md,p); else updVal(2*o+1,md+1,r,p); pull(o,l,r);
}
void updOp(int o,int l,int r,int p){ // operator between p and p+1
    if(l==r) return;
    int md=(l+r)/2;
    if(p<md) updOp(2*o,l,md,p); else if(p>md) updOp(2*o+1,md+1,r,p);
    pull(o,l,r);
}
int main(){
    scanf("%d %d",&n,&m);
    static char buf[400005]; scanf("%s",buf);
    val.resize(n); op.assign(n,0);
    for(int i=0;i<n;i++){val[i]=buf[2*i]-'0'; if(i+1<n) op[i]=(buf[2*i+1]=='*');}
    t.resize(4*n);
    build(1,0,n-1);
    int flip=0;
    auto out=[&](){ const Nd&r=t[1][flip]; printf("%lld\n",r.full?r.pre:(r.pre+r.mid+r.suf)%MOD); };
    out();
    for(int q=0;q<m;q++){
        char c[4]; scanf("%s",c);
        if(c[0]=='s'){int i,j;scanf("%d %d",&i,&j);i--;j--; if(i!=j){swap(val[i],val[j]);updVal(1,0,n-1,i);updVal(1,0,n-1,j);} }
        else if(c[0]=='f'){int i;scanf("%d",&i);i--;op[i]^=1;updOp(1,0,n-1,i);}
        else flip^=1;
        out();
    }
}
