#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m,B;scanf("%d %d %d",&n,&m,&B);
    vector<int>p(n),r(n),s(n);for(int i=0;i<n;i++)scanf("%d %d %d",&p[i],&r[i],&s[i]);
    vector<vector<int>> c(n,vector<int>(m+1,0)),d(n,vector<int>(m+1,0));
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)scanf("%d",&c[i][j]);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)scanf("%d",&d[i][j]);
    const long long INF=LLONG_MAX/4;
    vector<long long> f(B+1,INF),g;f[0]=0;
    for(int i=0;i<n;i++){
        g.assign(B+1,INF);
        for(int b=0;b<=B;b++)if(f[b]<INF)for(int nb=0;nb<=B;nb++)for(int j=0;j<=m;j++){
            int x=max(0,r[i]+nb+d[i][j]-s[i]-b);
            g[nb]=min(g[nb],f[b]+(long long)p[i]*x-c[i][j]);
        }
        f=g;
    }
    printf("%lld\n",*min_element(f.begin(),f.end()));
}
