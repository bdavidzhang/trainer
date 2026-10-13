#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll c,d,e,f,g;
bool tryit(ll V1,ll V2,ll V3){
    if(c>=V1||d>=V2||e>=V3)return false;
    ll N=f+(((c-f)%V1)+V1)%V1;
    for(;N<=g;N+=V1) if(N%V2==d&&N%V3==e){cout<<N<<endl;return true;}
    return false;
}
int main(){
    ll a,b; cin>>a>>b>>c>>d>>e>>f>>g;
    vector<ll> v;
    for(ll x=1;2*x<a;x++) v.push_back((a-2*x)*(b-2*x)*x);
    sort(v.rbegin(),v.rend());
    // primary reading: the three largest boxes (different cut sizes; volumes may tie)
    if(tryit(v[0],v[1],v[2]))return 0;
    // fallback reading: three largest distinct volumes
    v.erase(unique(v.begin(),v.end()),v.end());
    if(v.size()>=3)tryit(v[0],v[1],v[2]);
    return 0;
}
