#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;ll s;
vector<ll> w;
vector<ll> pc;vector<int> p1,p2;
static ll cost1(ll x){return (x+2)/3;}
bool ok(int k){
    if(k<=2)return k<=s;
    // prefix of k smallest; choose two end chargers among the largest few
    ll tot=pc[k];int c1=p1[k],c2=p2[k];
    int lo=max(0,k-6);
    ll best=LLONG_MAX;
    for(int i=lo;i<k;i++)for(int j=i+1;j<k;j++){
        ll t=tot-cost1(w[i])-cost1(w[j]);
        int a=c1-(w[i]%3==1)-(w[j]%3==1),b=c2-(w[i]%3==2)-(w[j]%3==2);
        t-=min(a,(a+b)/2);
        best=min(best,t);
    }
    return best+2<=s;
}
int main(){
    scanf("%d %lld",&n,&s);
    w.resize(n);
    for(auto&x:w)scanf("%lld",&x);
    sort(w.begin(),w.end());
    pc.assign(n+1,0);p1.assign(n+1,0);p2.assign(n+1,0);
    for(int i=0;i<n;i++){pc[i+1]=pc[i]+cost1(w[i]);p1[i+1]=p1[i]+(w[i]%3==1);p2[i+1]=p2[i]+(w[i]%3==2);}
    int lo=0,hi=n;
    while(lo<hi){int mid=(lo+hi+1)/2;if(ok(mid))lo=mid;else hi=mid-1;}
    printf("%d\n",lo);
}
