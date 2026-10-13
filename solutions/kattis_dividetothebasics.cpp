#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1e9+7;
int main(){
    ll n; cin>>n;
    vector<ll> ps; ll m=n;
    for(ll p=2;p*p<=m;p++) if(m%p==0){ps.push_back(p);while(m%p==0)m/=p;}
    if(m>1)ps.push_back(m);
    vector<ll> divs={1};
    for(ll p:ps){
        size_t sz=divs.size(); ll q=1, t=n;
        while(t%p==0){t/=p;q*=p; for(size_t i=0;i<sz;i++) divs.push_back(divs[i]*q);}
    }
    sort(divs.begin(),divs.end());
    int D=divs.size();
    vector<ll> h(D,0); h[0]=1;
    for(int i=1;i<D;i++){
        ll s=0, x=divs[i];
        for(int j=0;j<i;j++) if(x%divs[j]==0) s+=h[j];
        h[i]=s%MOD;
    }
    cout<<h[D-1]<<"\n";
}
