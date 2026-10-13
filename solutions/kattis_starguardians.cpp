#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;vector<long long>a(n),s(n);for(auto&x:a)cin>>x;for(auto&x:s)cin>>x;
    sort(s.rbegin(),s.rend());double best=0;long long pre=0;
    for(int i=0;i<n;i++){pre+=s[i];best=max(best,(double)(pre+a[i])/(i+1));}
    printf("%.7f\n",best);}
