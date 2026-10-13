#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<long long> x(n),y(n),h(n);
    for(int i=0;i<n;i++) scanf("%lld %lld %lld",&x[i],&y[i],&h[i]);
    for(int i=0;i<n;i++){
        long long best=h[i];
        for(int j=0;j<n;j++) if(h[j]>h[i]){
            long long d2=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
            long long r=(long long)sqrtl((long double)d2);
            while(r*r>d2) r--;
            while((r+1)*(r+1)<=d2) r++;
            best=min(best,r);
        }
        printf("%lld\n",best);
    }
}
