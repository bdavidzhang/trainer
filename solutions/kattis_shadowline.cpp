#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n; ll w; scanf("%d %lld",&n,&w);
    vector<ll> X(n),lo(n),hi(n);
    for(int i=0;i<n;i++) scanf("%lld %lld %lld",&X[i],&lo[i],&hi[i]);
    const double INF=1e300;
    vector<double> st,en; long long infc=0;
    vector<pair<double,double>> iv;
    for(int a=0;a<n;a++){
        ll x=X[a],y=hi[a]; iv.clear();
        for(int b=0;b<n;b++) if(b!=a){
            double L=0,H=INF;
            ll c1=y-lo[b], r1=lo[b]*x-y*X[b];
            ll c2=hi[b]-y, r2=y*X[b]-hi[b]*x;
            double v1=(double)r1/(double)c1, v2=(double)r2/(double)c2;
            if(c1>0) L=max(L,v1); else H=min(H,v1);
            if(c2>0) L=max(L,v2); else H=min(H,v2);
            if(L<H) iv.push_back({L,H});
        }
        sort(iv.begin(),iv.end());
        double cur=0;
        for(auto&p:iv){
            if(p.first>cur){st.push_back(cur);en.push_back(p.first);}
            if(p.second>cur) cur=p.second;
        }
        if(cur<INF){st.push_back(cur);infc++;}
    }
    if(infc==1){puts("-1");return 0;}
    sort(st.begin(),st.end()); sort(en.begin(),en.end());
    size_t i=0,j=0; long long cnt=0; double prev=0; long double tot=0;
    while(i<st.size()||j<en.size()){
        bool takeS; double t;
        if(j>=en.size()||(i<st.size()&&st[i]<=en[j])){takeS=true;t=st[i];}
        else {takeS=false;t=en[j];}
        if(cnt==1) tot+=t-prev;
        prev=t;
        if(takeS){cnt++;i++;} else {cnt--;j++;}
    }
    printf("%.9Lf\n",tot);
}
