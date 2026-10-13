#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> p;
int find(int x){ while(p[x]!=x){p[x]=p[p[x]];x=p[x];} return x; }
int main(){
    int n; scanf("%d",&n);
    vector<ll> s(n),t(n), vals;
    for(int i=0;i<n;i++){ scanf("%lld %lld",&s[i],&t[i]); vals.push_back(s[i]); vals.push_back(t[i]); }
    sort(vals.begin(),vals.end()); vals.erase(unique(vals.begin(),vals.end()),vals.end());
    int V=vals.size(); p.resize(V); iota(p.begin(),p.end(),0);
    ll ans=0;
    vector<pair<int,int>> e(n);
    for(int i=0;i<n;i++){
        int a=lower_bound(vals.begin(),vals.end(),s[i])-vals.begin();
        int b=lower_bound(vals.begin(),vals.end(),t[i])-vals.begin();
        e[i]={a,b}; ans+=s[i]+t[i];
        p[find(a)]=find(b);
    }
    vector<int> ec(V,0), vc(V,0); vector<ll> mx(V,0);
    for(int i=0;i<n;i++) ec[find(e[i].first)]++;
    for(int v=0;v<V;v++){ int r=find(v); vc[r]++; mx[r]=max(mx[r],vals[v]); ans-=vals[v]; }
    for(int v=0;v<V;v++) if(find(v)==v && ec[v]==vc[v]-1) ans+=mx[v];
    printf("%lld\n",ans);
}
