#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// A bisector with dx>dy is a curve x=f(y): f(Y)=clamp(+-Y+c, lo, hi) (doubled coordinates).
// dx<dy: same with axes swapped. dx==dy: contains both kinds of curve -> meets everything.
// Curves of different orientation always meet. Same orientation: disjoint iff ranges disjoint,
// or same monotonicity with c1<c2, lo1<lo2, hi1<hi2 (and ranges overlapping).
struct T{ll c,lo,hi;int r;};
struct BIT{
    int n; vector<int> t;
    void init(int n_){n=n_;t.assign(n+1,0);}
    void add(int i,int v){for(i++;i<=n;i+=i&-i)t[i]+=v;}
    int sum(int i){int s=0;for(;i>0;i-=i&-i)s+=t[i];return s;} // count of ranks < i
};
BIT bit; vector<T> a,tmp;
ll cdq(int l,int r){
    if(r-l<=1)return 0;
    int m=(l+r)/2;
    ll res=cdq(l,m)+cdq(m,r);
    int i=l;
    for(int j=m;j<r;j++){
        while(i<m&&a[i].lo<a[j].lo){bit.add(a[i].r,1);i++;}
        res+=bit.sum(a[j].r);
    }
    for(int t=l;t<i;t++)bit.add(a[t].r,-1);
    merge(a.begin()+l,a.begin()+m,a.begin()+m,a.begin()+r,tmp.begin()+l,[](const T&u,const T&v){return u.lo<v.lo;});
    copy(tmp.begin()+l,tmp.begin()+r,a.begin()+l);
    return res;
}
ll extra(vector<T> v){ // #(c1<c2,lo1<lo2,hi1<hi2) - #(c1<c2,hi1<lo2)
    int n=v.size(); if(n<2)return 0;
    vector<ll> hs; for(auto&t:v)hs.push_back(t.hi);
    sort(hs.begin(),hs.end()); hs.erase(unique(hs.begin(),hs.end()),hs.end());
    for(auto&t:v)t.r=lower_bound(hs.begin(),hs.end(),t.hi)-hs.begin();
    sort(v.begin(),v.end(),[](const T&u,const T&w){ if(u.c!=w.c)return u.c<w.c; return u.lo>w.lo;});
    bit.init(hs.size());
    // dom2
    ll d2=0;
    for(int s=0;s<n;){
        int e=s; while(e<n&&v[e].c==v[s].c)e++;
        for(int t=s;t<e;t++) d2+=bit.sum(lower_bound(hs.begin(),hs.end(),v[t].lo)-hs.begin());
        for(int t=s;t<e;t++) bit.add(v[t].r,1);
        s=e;
    }
    bit.init(hs.size());
    a=v; tmp.resize(n);
    ll d3=cdq(0,n);
    return d3-d2;
}
ll rangeDisjoint(const vector<pair<ll,ll>>&iv){
    vector<ll> los; for(auto&p:iv)los.push_back(p.first);
    sort(los.begin(),los.end());
    ll res=0;
    for(auto&p:iv) res+=los.end()-upper_bound(los.begin(),los.end(),p.second);
    return res;
}
int main(){
    int n; scanf("%d",&n);
    vector<pair<ll,ll>> iv[2]; vector<T> mono[2][2];
    for(int i=0;i<n;i++){
        ll x1,y1,x2,y2; scanf("%lld %lld %lld %lld",&x1,&y1,&x2,&y2);
        ll dx=llabs(x1-x2),dy=llabs(y1-y2);
        if(dx==dy)continue;
        int o=0;
        if(dx<dy){swap(x1,y1);swap(x2,y2);o=1;}
        if(x1>x2){swap(x1,x2);swap(y1,y2);}
        ll base=x1+x2,dv=y2-y1,ad=llabs(dv);
        iv[o].push_back({base-ad,base+ad});
        if(dv>0) mono[o][0].push_back({x1+x2+y1+y2,base-ad,base+ad,0});
        else if(dv<0) mono[o][1].push_back({x1+x2-y1-y2,base-ad,base+ad,0});
    }
    ll non=0;
    for(int o=0;o<2;o++){
        non+=rangeDisjoint(iv[o]);
        for(int k=0;k<2;k++)non+=extra(mono[o][k]);
    }
    printf("%lld\n",(ll)n*(n-1)/2-non);
}
