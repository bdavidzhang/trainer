#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<ll,ll> P;
ll cr(const P&o,const P&a,const P&b){return (a.first-o.first)*(b.second-o.second)-(a.second-o.second)*(b.first-o.first);}
int main(){
    int n; scanf("%d",&n); vector<P> p(n);
    for(auto&q:p) scanf("%lld %lld",&q.first,&q.second);
    sort(p.begin(),p.end()); p.erase(unique(p.begin(),p.end()),p.end()); n=p.size();
    ll best=0;
    if(n>=3){
        vector<P> h(2*n); int k=0;
        for(int i=0;i<n;i++){while(k>=2&&cr(h[k-2],h[k-1],p[i])<=0)k--;h[k++]=p[i];}
        for(int i=n-2,t=k+1;i>=0;i--){while(k>=t&&cr(h[k-2],h[k-1],p[i])<=0)k--;h[k++]=p[i];}
        h.resize(k-1); int m=h.size();
        if(m>=3){
            for(int i=0;i<m;i++){
                int c=(i+2)%m;
                for(int j=i+1;j<m;j++){
                    if(c==j) c=(c+1)%m;
                    while(true){
                        int nc=(c+1)%m; if(nc==i) break;
                        if(llabs(cr(h[i],h[j],h[nc]))>=llabs(cr(h[i],h[j],h[c]))) c=nc; else break;
                    }
                    best=max(best,llabs(cr(h[i],h[j],h[c])));
                }
            }
        }
    }
    printf("%lld.%s\n",best/2,(best&1)?"50000":"00000");
}
