#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<long long> hs,he,vs,ve; // intervals [s,e)
    vector<pair<long long,long long>> H;
    for(int i=0;i<n;i++){
        char c; long long t,m,a; scanf(" %c %lld %lld %lld",&c,&t,&m,&a);
        if(c=='h') H.push_back({t-a,t-a+m});
        else { vs.push_back(t-a); ve.push_back(t-a+m); }
    }
    sort(vs.begin(),vs.end()); sort(ve.begin(),ve.end());
    long long ans=0, V=vs.size();
    for(auto&h:H){
        // disjoint: v.e <= h.s  or v.s >= h.e
        long long d1=upper_bound(ve.begin(),ve.end(),h.first)-ve.begin();
        long long d2=vs.end()-lower_bound(vs.begin(),vs.end(),h.second);
        ans+=V-d1-d2;
    }
    printf("%lld\n",ans);
}
