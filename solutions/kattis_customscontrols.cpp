#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){ int n,m,k; scanf("%d %d %d",&n,&m,&k); vector<ll>t(n); for(auto&x:t)scanf("%lld",&x);
    vector<vector<int>> g(n); bool direct=false;
    for(int i=0;i<m;i++){int u,v;scanf("%d %d",&u,&v);u--;v--;g[u].push_back(v);g[v].push_back(u); if((u==0&&v==n-1)||(v==0&&u==n-1))direct=true;}
    string s(n,'S');
    if(direct){
        if(n==2){ if(k==1){puts("impossible");return 0;} if(k==2)s="NN"; }
        else if(k>=2){ s[0]=s[n-1]='N'; int c=k-2; for(int i=1;i<n-1&&c>0;i++){s[i]='N';c--;} }
        else { if(k==1) s[1]='N'; }
        puts(s.c_str()); return 0;
    }
    vector<ll> d(n,LLONG_MAX); priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>> pq; d[0]=t[0]; pq.push({d[0],0});
    while(!pq.empty()){ auto [dd,u]=pq.top(); pq.pop(); if(dd>d[u])continue; for(int v:g[u]) if(dd+t[v]<d[v]){d[v]=dd+t[v];pq.push({d[v],v});} }
    vector<int> ord(n); iota(ord.begin(),ord.end(),0); sort(ord.begin(),ord.end(),[&](int a,int b){return d[a]<d[b];});
    for(int i=0;i<k;i++) s[ord[i]]='N';
    puts(s.c_str()); }
