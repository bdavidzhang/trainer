#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n,k; ll xb;
    scanf("%d %d %lld",&n,&k,&xb);
    vector<ll> a(n); ll tot=0;
    for(auto&v:a){scanf("%lld",&v);tot+=v;}
    sort(a.begin(),a.end());
    long double best=fabsl((long double)(tot-xb*n))/n;
    auto upd=[&](ll d,int j){ long double c=(long double)d/(n-j); if(c<best) best=c; };
    auto labs2=[](ll v){return v<0?-v:v;};
    if(k>=1){
        ll T=tot-xb*(n-1), d=LLONG_MAX;
        for(int i=0;i<n;i++) d=min(d,labs2(a[i]-T));
        upd(d,1);
    }
    if(k>=2){
        ll T=tot-xb*(n-2), d=LLONG_MAX;
        int lo=0,hi=n-1;
        while(lo<hi){ ll s=a[lo]+a[hi]; d=min(d,labs2(s-T)); if(s<T) lo++; else hi--; }
        upd(d,2);
    }
    if(k>=3){
        ll T0=tot-xb*(n-3), d=LLONG_MAX;
        for(int i=0;i+2<n;i++){
            ll T=T0-a[i]; int lo=i+1,hi=n-1;
            while(lo<hi){ ll s=a[lo]+a[hi]; d=min(d,labs2(s-T)); if(s<T) lo++; else hi--; }
        }
        upd(d,3);
    }
    if(k>=4){
        ll T0=tot-xb*(n-4), d=LLONG_MAX;
        // indices i<j<k2<l ; sorted vector of pair sums (i,j) with j<k2 grows; use set
        set<ll> S;
        for(int c=2;c+1<n;c++){
            for(int i=0;i<c-1;i++) S.insert(a[i]+a[c-1]);
            for(int l=c+1;l<n;l++){
                ll T=T0-a[c]-a[l];
                auto it=S.lower_bound(T);
                if(it!=S.end()) d=min(d,*it-T);
                if(it!=S.begin()){--it; d=min(d,T-*it);}
            }
            if(d==0) break;
        }
        upd(d,4);
    }
    printf("%.10Lf\n",best);
}
