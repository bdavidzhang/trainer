#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; long long k;
    scanf("%d %d %lld",&n,&m,&k);
    vector<long long> a(n+1);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    vector<vector<int>> in(n+1);
    for(int i=0;i<m;i++){int x,y;scanf("%d %d",&x,&y);in[y].push_back(x);}
    vector<long long> x(n+1);
    long long tot=0;
    for(int i=1;i<=n;i++){
        long long s=a[i]%k;
        for(int j:in[i]) s=(s+x[j])%k;
        x[i]=(k-s)%k;
        tot+=x[i];
    }
    printf("%lld\n",tot);
}
