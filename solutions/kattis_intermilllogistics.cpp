#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; long long w; scanf("%d %lld",&n,&w);
    vector<pair<long long,long long>> a(n); // (t,p)
    for(auto&m:a) scanf("%lld %lld",&m.second,&m.first);
    sort(a.begin(),a.end());
    long double sp=0, spt=0, best=1e300L;
    for(int i=0;i<n;i++){
        sp+=a[i].second; spt+=(long double)a[i].second*a[i].first;
        long double T=((long double)w+2*spt)/sp;
        best=min(best,T);
    }
    printf("%.9Lf\n",best);
}
