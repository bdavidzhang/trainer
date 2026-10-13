#include <bits/stdc++.h>
using namespace std;
int main(){int n;long long m;scanf("%d %lld",&n,&m);vector<long long>w(n);for(auto&x:w)scanf("%lld",&x);
sort(w.begin(),w.end());int i=0,j=n-1,r=0;while(i<=j){if(i<j&&w[i]+w[j]<=m)i++;j--;r++;}printf("%d\n",r);}
