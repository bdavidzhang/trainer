#include <bits/stdc++.h>
using namespace std;
int main(){ int n; cin>>n; vector<long long> t(n+1);
    for(int k=0;k<n;k++){ long long x; int i; cin>>x>>i; t[i]=x; }
    long long cur=0; for(int i=1;i<=n;i++) cur=max(cur+1,t[i]);
    cout<<cur-n<<"\n"; }
