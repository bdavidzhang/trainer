#include <bits/stdc++.h>
using namespace std;
int main(){int n,m,k;scanf("%d %d %d",&n,&m,&k);vector<long long>s(n);long long t=0;for(auto&x:s){scanf("%lld",&x);t+=x;}
sort(s.rbegin(),s.rend());int c=min(n,m+k);long long a=0;for(int i=0;i<c;i++)a+=s[i];printf("%.9f\n",(double)(100.0L*a/t));}
