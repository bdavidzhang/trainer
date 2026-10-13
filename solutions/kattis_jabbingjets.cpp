#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; double e; cin>>n>>e;
    const double PI=acos(-1.0);
    long long ans=0;
    for(int i=0;i<n;i++){
        double r; cin>>r; r+=5e-7;
        if(2*r<e){ ans+=1; continue; }
        double x=min(1.0,e/(2*r));
        long long k=(long long)floor(PI/asin(x));
        if(k<2) k=2;
        ans+=k;
    }
    cout<<ans<<"\n";
}
