#include <bits/stdc++.h>
using namespace std;
int main(){int n,k;scanf("%d %d",&n,&k);vector<long long>s(n+1,0);
for(int e=0;e<k;e++)for(int i=1;i<=n;i++){int r;scanf("%d",&r);s[r]+=i;}
vector<int>o(n);iota(o.begin(),o.end(),1);
stable_sort(o.begin(),o.end(),[&](int a,int b){return s[a]<s[b];});
for(int i=0;i<n;i++)printf("%d%c",o[i],i+1<n?' ':'\n');}
