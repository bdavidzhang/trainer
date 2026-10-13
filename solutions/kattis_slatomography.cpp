#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n; scanf("%d",&n);
    vector<ll> x(n); for(auto&v:x)scanf("%lld",&v);
    int s=0; while(s<n&&x[s]==0)s++;
    if(s==n){puts("impossible");return 0;}
    ll cnt=2;
    for(int i=s+1;i<n;i++){
        if(x[i]>x[i-1])cnt+=1;
        else cnt+=x[i-1]-x[i];
    }
    printf("%lld\n",cnt+x[n-1]);
}
