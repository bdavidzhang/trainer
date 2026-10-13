#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; long long K; cin>>n>>K; vector<pair<long long,long long>> side[2];
    for(int i=0;i<n;i++){long long x,t;cin>>x>>t; side[x<0].push_back({llabs(x),t});}
    long long ans=0;
    for(auto&v:side){
        sort(v.rbegin(),v.rend()); long long spare=0;
        for(auto&p:v){
            long long t=p.second;
            long long u=min(spare,t); spare-=u; t-=u;
            if(t>0){long long trips=(t+K-1)/K; ans+=2*p.first*trips; spare=trips*K-t;}
        }
    }
    cout<<ans<<endl;
}
