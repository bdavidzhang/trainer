#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n;ll p,k;scanf("%d %lld %lld",&n,&p,&k);vector<ll>d(n),pre(2*n+1,0);for(auto&x:d)scanf("%lld",&x);
    for(int i=0;i<2*n;i++)pre[i+1]=pre[i]+d[i%n];ll S=pre[n];
    vector<int> nx(n);vector<ll> ct(n);
    ll t=p/S,rem=p%S;
    for(int i=0;i<n;i++){int e=int(upper_bound(pre.begin()+i,pre.end(),pre[i]+rem)-pre.begin())-1-i;
        ll c=i+e;ct[i]=t+c/n;nx[i]=c%n;}
    int cur=0;ll ans=0;
    while(k){if(k&1){ans+=ct[cur];cur=nx[cur];}
        k>>=1;if(!k)break;
        vector<int> n2(n);vector<ll> c2(n);for(int i=0;i<n;i++){n2[i]=nx[nx[i]];c2[i]=ct[i]+ct[nx[i]];}nx.swap(n2);ct.swap(c2);}
    printf("%lld\n",ans);
}
