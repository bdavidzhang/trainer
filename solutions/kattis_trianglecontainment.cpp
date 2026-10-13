#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n; vector<ll> bit;
void upd(int i,ll v){for(i++;i<=n;i+=i&-i)bit[i]+=v;}
ll qry(int i){ll s=0;for(;i>0;i-=i&-i)s+=bit[i];return s;} // sum of ranks < i
int main(){
    ll X; scanf("%d %lld",&n,&X);
    vector<ll> x(n),y(n),v(n);
    for(int i=0;i<n;i++)scanf("%lld %lld %lld",&x[i],&y[i],&v[i]);
    vector<int> a(n),b(n);
    iota(a.begin(),a.end(),0); iota(b.begin(),b.end(),0);
    // angle at origin from +x axis, ascending
    sort(a.begin(),a.end(),[&](int p,int q){return x[p]*y[q]-y[p]*x[q]>0;});
    // angle at (X,0) from -x axis, ascending
    sort(b.begin(),b.end(),[&](int p,int q){return (x[p]-X)*y[q]-y[p]*(x[q]-X)<0;});
    vector<int> rk(n); for(int i=0;i<n;i++) rk[b[i]]=i;
    bit.assign(n+1,0);
    vector<ll> ans(n);
    for(int i:a){ ans[i]=qry(rk[i]); upd(rk[i],v[i]); }
    for(int i=0;i<n;i++)printf("%lld\n",ans[i]);
}
