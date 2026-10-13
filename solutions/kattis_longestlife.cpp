#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
struct Line{ ld k,b; ld at(ld x)const{ return k*x+b; } };
int sz;
vector<ld> xs;
vector<Line> tr; vector<char> has;
void ins(int o,int l,int r,Line ln){
    if(!has[o]){ tr[o]=ln; has[o]=1; return; }
    int mid=(l+r)/2;
    if(ln.at(xs[mid])<tr[o].at(xs[mid])) swap(ln,tr[o]);
    if(l==r) return;
    if(ln.at(xs[l])<tr[o].at(xs[l])) ins(o*2,l,mid,ln);
    else if(ln.at(xs[r])<tr[o].at(xs[r])) ins(o*2+1,mid+1,r,ln);
}
ld query(int o,int l,int r,int i){
    ld res= has[o]? tr[o].at(xs[i]) : 1e30L;
    if(l==r) return res;
    int mid=(l+r)/2;
    if(i<=mid) return min(res,query(o*2,l,mid,i));
    return min(res,query(o*2+1,mid+1,r,i));
}
int main(){
    long long n,c; int p;
    scanf("%lld %d %lld",&n,&p,&c);
    vector<array<long long,3>> a(p);
    for(auto&v:a) scanf("%lld %lld %lld",&v[0],&v[1],&v[2]);
    sort(a.begin(),a.end());
    xs.resize(p); for(int i=0;i<p;i++) xs[i]=a[i][0];
    tr.resize(4*p+4); has.assign(4*p+4,0);
    ins(1,0,p-1,{1.0L,0.0L});
    ld ans=n;
    for(int i=0;i<p;i++){
        ld f=query(1,0,p-1,i)+c;
        if(f<n){
            ld r=(ld)a[i][2]/a[i][1];
            ans=max(ans,xs[i]+(n-f)/r);
            ins(1,0,p-1,{r,f-r*xs[i]});
        }
    }
    printf("%.9Lf\n",ans);
}
