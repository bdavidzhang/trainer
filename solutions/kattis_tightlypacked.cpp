#include <bits/stdc++.h>
using namespace std;
int main(){long long n;cin>>n;long long best=LLONG_MAX;
 for(long long w=1;;w++){long long h=(n+w-1)/w;bool last=false;if(h<=w){h=w;last=true;}
  if(h<=2*w)best=min(best,w*h-n);
  if(last)break;}
 cout<<best<<endl;}
