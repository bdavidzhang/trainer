#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
typedef long long ll;
const unsigned CAP=2000000000u;
struct Node{ int lc,rc,cnt; unsigned L[4]; u64 B[3]; };
vector<Node> t;
int n,s,q;
unsigned capL(ll u,int d){ // C(u+d-1,d) capped
    __int128 v=1;
    for(int i=1;i<=d;i++){ v=v*(u+d-i)/1; }
    __int128 f=1; for(int i=1;i<=d;i++) f*=i;
    v/=f;
    return v>CAP?CAP:(unsigned)v;
}
int ins(int prev,int l,int r,int pos,int val){
    int id=t.size(); t.push_back(t[prev]);
    {
        Node&x=t[id];
        x.cnt++;
        for(int d=1;d<=4;d++){ u64 z=(u64)x.L[d-1]+capL(val,d); x.L[d-1]=z>CAP?CAP:(unsigned)z; }
        u64 p=val;
        x.B[0]+=p; x.B[1]+=p*(p-1)/2; x.B[2]+=p*(p-1)/2*(p-2)/3;
    }
    if(l==r) return id;
    int m=(l+r)/2;
    if(pos<=m){ int c=ins(t[prev].lc,l,m,pos,val); t[id].lc=c; }
    else { int c=ins(t[prev].rc,m+1,r,pos,val); t[id].rc=c; }
    return id;
}
ll gbinom(ll x,int m){ // generalized binomial, m<=3
    if(m<0) return 0;
    if(m==0) return 1;
    if(m==1) return x;
    if(m==2) return x*(x-1)/2;
    __int128 v=(__int128)x*(x-1)*(x-2)/6;
    return (ll)v;
}
int main(){
    scanf("%d %d %d",&n,&s,&q);
    vector<int> p(n+1),pos(n+1);
    for(int i=1;i<=n;i++){scanf("%d",&p[i]);pos[p[i]]=i;}
    t.reserve((size_t)n*19+10);
    Node z; memset(&z,0,sizeof z); t.push_back(z);
    vector<int> root(n+1,0);
    for(int v=1;v<=n;v++) root[v]=ins(root[v-1],1,n,pos[v],v);
    while(q--){
        int k; ll a; scanf("%d %lld",&k,&a);
        int v=n,tt=s; u64 ans=0;
        while(true){
            if(k>v) break;
            if(tt==0){ ans+=(v==k); break; }
            int d=tt-1;
            int x=root[v],y=root[k-1];
            int l=1,r=n; ll rem=a;
            u64 S[4]={0,0,0,0};
            while(l<r){
                int m=(l+r)/2;
                int xl=t[x].lc, yl=t[y].lc;
                ll lv=d==0?t[xl].cnt:t[xl].L[d-1];
                if(rem<=lv){ x=xl;y=yl;r=m; }
                else{
                    rem-=lv;
                    S[0]+=(u64)(t[xl].cnt-t[yl].cnt);
                    for(int j=0;j<3;j++) S[j+1]+=t[xl].B[j]-t[yl].B[j];
                    x=t[x].rc;y=t[y].rc;l=m+1;
                }
            }
            int u=p[l];
            if(d==0){ if(pos[k]<l) ans+=1; }
            else{
                for(int j=0;j<=d-1;j++) ans+=(u64)gbinom((ll)d-1-k,d-1-j)*S[j];
            }
            v=u; tt=d; a=rem;
        }
        printf("%llu\n",ans);
    }
}
