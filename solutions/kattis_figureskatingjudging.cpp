#include <bits/stdc++.h>
using namespace std;
int main(){int n,k;scanf("%d %d",&n,&k);vector<long long>x(n);for(auto&v:x)scanf("%lld",&v);
    sort(x.begin(),x.end());
    vector<long long>s(n+1,0),q(n+1,0);
    for(int i=0;i<n;i++){s[i+1]=s[i]+x[i];q[i+1]=q[i]+x[i]*x[i];}
    __int128 best=-1;
    for(int i=0;i+k<=n;i++){__int128 S=s[i+k]-s[i],Q=q[i+k]-q[i];__int128 v=Q*k-S*S;if(best<0||v<best)best=v;}
    long double ans=(long double)best/k;
    printf("%.9Lf\n",ans);}
