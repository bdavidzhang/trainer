#include <bits/stdc++.h>
using namespace std;
int main(){
    long long n; int m; cin>>n>>m;
    // g[t][j] = max n decidable with t experiments, j pallets
    const long long CAP=1000000;
    vector<vector<long long>> g(1,vector<long long>(m+1,0));
    int T=0;
    while(g[T][m]<n){
        vector<long long> nx(m+1,0);
        for(int j=1;j<=m;j++) nx[j]=min(CAP,g[T][j-1]+g[T][j]+1);
        g.push_back(nx); T++;
    }
    long long lo=max(1LL,n-g[T-1][m]), hi=min(n,g[T-1][m-1]+1);
    if(lo==hi) printf("%d %lld\n",T,lo); else printf("%d %lld-%lld\n",T,lo,hi);
}
