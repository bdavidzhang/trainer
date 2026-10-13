#include <bits/stdc++.h>
using namespace std;
int main(){int T;scanf("%d",&T);while(T--){int n;scanf("%d",&n);vector<long long>a(n);for(auto&x:a)scanf("%lld",&x);
vector<int>L(n),R(n);vector<long long>t;
for(int i=0;i<n;i++){auto it=lower_bound(t.begin(),t.end(),a[i]);L[i]=it-t.begin()+1;if(it==t.end())t.push_back(a[i]);else *it=a[i];}
t.clear();
for(int i=n-1;i>=0;i--){auto it=lower_bound(t.begin(),t.end(),a[i]);R[i]=it-t.begin()+1;if(it==t.end())t.push_back(a[i]);else *it=a[i];}
int b=0;for(int i=0;i<n;i++)if(L[i]>=2&&R[i]>=2)b=max(b,L[i]+R[i]-1);printf("%d\n",b);}}
