#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;vector<double>p(n);for(auto&x:p){cin>>x;x/=100;}
 sort(p.rbegin(),p.rend());
 vector<double>f(n+1,0);f[0]=1;double best=0;
 for(int k=1;k<=n;k++){double q=p[k-1];
  for(int a=k;a>=0;a--)f[a]=f[a]*(1-q)+(a?f[a-1]*q:0);
  double e=0;for(int a=1;a<=k;a++)e+=f[a]*pow((double)a,(double)a/k);
  best=max(best,e);}
 printf("%.9f\n",best);}
