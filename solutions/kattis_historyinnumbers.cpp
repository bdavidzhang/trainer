#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Node{
    ll lv,rv,fm,lm; int fs,ls; bool has,ok,emp;
};
static inline int sgn(ll x){return (x>0)-(x<0);}
static Node mergeN(const Node&A,const Node&B){
    if(A.emp)return B; if(B.emp)return A;
    Node C; C.emp=false;
    C.lv=A.lv; C.rv=B.rv;
    int d=sgn(B.lv-A.rv);
    bool jn=false; ll jv=0;
    if(A.ls==-1 && (d>0 || (d==0 && B.fs==1))){jn=true;jv=A.rv;}
    else if(B.fs==1 && d<0){jn=true;jv=B.lv;}
    C.ok=A.ok&&B.ok;
    C.has=false; C.fm=C.lm=0;
    auto add=[&](ll f,ll l){
        if(!C.has){C.has=true;C.fm=f;C.lm=l;}
        else{ if(C.lm>=f)C.ok=false; C.lm=l; }
    };
    if(A.has)add(A.fm,A.lm);
    if(jn)add(jv,jv);
    if(B.has)add(B.fm,B.lm);
    C.fs=A.fs?A.fs:(d?d:B.fs);
    C.ls=B.ls?B.ls:(d?d:A.ls);
    return C;
}
int n;
vector<Node> t; vector<ll> lz; vector<ll> e;
void app(int x,ll v){t[x].lv+=v;t[x].rv+=v;t[x].fm+=v;t[x].lm+=v;lz[x]+=v;}
void push(int x){if(lz[x]){app(2*x,lz[x]);app(2*x+1,lz[x]);lz[x]=0;}}
void build(int x,int l,int r){
    if(l==r){t[x]={e[l],e[l],0,0,0,0,false,true,false};return;}
    int m=(l+r)/2;build(2*x,l,m);build(2*x+1,m+1,r);t[x]=mergeN(t[2*x],t[2*x+1]);
}
void upd(int x,int l,int r,int a,int b,ll v){
    if(a<=l&&r<=b){app(x,v);return;}
    push(x);int m=(l+r)/2;
    if(a<=m)upd(2*x,l,m,a,b,v);
    if(b>m)upd(2*x+1,m+1,r,a,b,v);
    t[x]=mergeN(t[2*x],t[2*x+1]);
}
Node qry(int x,int l,int r,int a,int b){
    if(a<=l&&r<=b)return t[x];
    push(x);int m=(l+r)/2;
    if(b<=m)return qry(2*x,l,m,a,b);
    if(a>m)return qry(2*x+1,m+1,r,a,b);
    return mergeN(qry(2*x,l,m,a,b),qry(2*x+1,m+1,r,a,b));
}
int main(){
    scanf("%d",&n);e.resize(n);
    for(auto&x:e)scanf("%lld",&x);
    t.resize(4*n);lz.assign(4*n,0);
    build(1,0,n-1);
    int m;scanf("%d",&m);
    char buf[16];
    while(m--){
        scanf("%s",buf);
        if(buf[0]=='u'){
            int s,f;ll d;scanf("%d %d %lld",&s,&f,&d);
            upd(1,0,n-1,s-1,f-1,d);
        }else{
            int s,f;scanf("%d %d",&s,&f);
            Node q=qry(1,0,n-1,s-1,f-1);
            bool ok=q.ok;
            if(q.fs!=0){
                bool hasPrev=false; ll prev=0;
                auto add=[&](ll v){ if(hasPrev&&prev>=v)ok=false; prev=v;hasPrev=true; };
                if(q.fs==1)add(q.lv);
                if(q.has){add(q.fm);prev=q.lm;}
                if(q.ls==-1)add(q.rv);
            }
            puts(ok?"YES":"NO");
        }
    }
}
