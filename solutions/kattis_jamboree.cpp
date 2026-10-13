#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; cin>>n>>m; vector<long long> a(2*m,0);
    for(int i=0;i<n;i++) cin>>a[i];
    sort(a.begin(),a.end());
    long long best=0;
    for(int i=0;i<m;i++) best=max(best,a[i]+a[2*m-1-i]);
    cout<<best<<"\n";
}
