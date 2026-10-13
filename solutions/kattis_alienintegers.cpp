#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){string s;cin>>s;ll N=stoll(s);bool used[10]={0};for(char c:s)used[c-'0']=1;
    vector<int> al;for(int d=0;d<10;d++)if(!used[d])al.push_back(d);
    if(al.empty()){puts("Impossible");return 0;}
    int mn=al.front(),mx=al.back();
    vector<ll> cand; if(!used[0])cand.push_back(0);
    int L=s.size();
    for(int len=max(1,L-1);len<=L+1;len++)for(int f:al){ if(f==0)continue;
        for(int fill:{mn,mx}){ll v=f;for(int i=1;i<len;i++)v=v*10+fill;cand.push_back(v);} }
    if(cand.empty()){puts("Impossible");return 0;}
    sort(cand.begin(),cand.end());cand.erase(unique(cand.begin(),cand.end()),cand.end());
    ll best=LLONG_MAX;for(ll v:cand)best=min(best,llabs(v-N));
    bool first=true;for(ll v:cand)if(llabs(v-N)==best){printf(first?"%lld":" %lld",v);first=false;}
    puts("");}
