#include <bits/stdc++.h>
using namespace std;
const int V=100000;
int dp[V+1];
int main(){
    int n,m;scanf("%d %d",&n,&m);
    vector<int>d(n);vector<char>removed(V+1,0);
    for(auto&x:d)scanf("%d",&x);
    vector<char>c(m);vector<int>v(m);
    for(int i=0;i<m;i++){scanf(" %c %d",&c[i],&v[i]);if(c[i]=='X')removed[v[i]]=1;}
    const int INF=1e9;
    for(int i=1;i<=V;i++)dp[i]=INF;
    dp[0]=0;
    auto add=[&](int x){for(int i=x;i<=V;i++){int t=dp[i-x]+1;if(t<dp[i])dp[i]=t;}};
    for(int x:d)if(!removed[x])add(x);
    vector<int>ans;
    for(int i=m-1;i>=0;i--){
        if(c[i]=='Q')ans.push_back(dp[v[i]]>=INF?-1:dp[v[i]]);
        else add(v[i]);
    }
    for(int i=(int)ans.size()-1;i>=0;i--)printf("%d\n",ans[i]);
}
