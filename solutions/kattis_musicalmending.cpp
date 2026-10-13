#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n); vector<long long>a(n);
    for(int i=0;i<n;i++){scanf("%lld",&a[i]);a[i]-=i;}
    nth_element(a.begin(),a.begin()+n/2,a.end());
    long long m=a[n/2],r=0; for(auto x:a)r+=llabs(x-m);
    printf("%lld\n",r);
}
