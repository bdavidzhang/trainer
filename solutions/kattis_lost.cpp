#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m;cin>>n>>m;
    map<string,int> id;id["English"]=0;
    for(int i=1;i<=n;i++){string s;cin>>s;id[s]=i;}
    vector<vector<pair<int,int>>> g(n+1);
    for(int i=0;i<m;i++){
        string a,b;int c;cin>>a>>b>>c;
        int u=id[a],v=id[b];
        g[u].push_back({v,c});g[v].push_back({u,c});
    }
    vector<int> d(n+1,-1);d[0]=0;
    queue<int> q;q.push(0);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(auto&e:g[u])if(d[e.first]<0){d[e.first]=d[u]+1;q.push(e.first);}
    }
    long long tot=0;
    for(int v=1;v<=n;v++){
        if(d[v]<0){puts("Impossible");return 0;}
        int best=INT_MAX;
        for(auto&e:g[v])if(d[e.first]==d[v]-1)best=min(best,e.second);
        tot+=best;
    }
    cout<<tot<<endl;
}
