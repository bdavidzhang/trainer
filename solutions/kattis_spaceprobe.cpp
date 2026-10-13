#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n,k;ll t1,t2;scanf("%d %d %lld %lld",&n,&k,&t1,&t2);
    vector<ll>m(n),b(k),e(k);
    for(auto&v:m)scanf("%lld",&v);
    for(int j=0;j<k;j++)scanf("%lld %lld",&b[j],&e[j]);
    vector<pair<ll,ll>> iv;
    for(int i=0;i<n;i++){
        // intervals [b_j-m_i, e_j-m_i] intersecting [t1,t2]: e_j>=t1+m_i, b_j<=t2+m_i
        int lo=lower_bound(e.begin(),e.end(),t1+m[i])-e.begin();
        for(int j=lo;j<k&&b[j]<=t2+m[i];j++)
            iv.push_back({max(t1,b[j]-m[i]),min(t2,e[j]-m[i])});
    }
    sort(iv.begin(),iv.end());
    ll bad=0,cur=t1;
    for(auto&p:iv){ll l=max(p.first,cur);if(p.second>l){bad+=p.second-l;cur=p.second;}}
    ll good=(t2-t1)-bad;
    printf("%.10Lf\n",(long double)good/(long double)(t2-t1));}
