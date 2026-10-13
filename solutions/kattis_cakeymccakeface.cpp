#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;scanf("%d %d",&n,&m);vector<long long>a(n),b(m);for(auto&x:a)scanf("%lld",&x);for(auto&x:b)scanf("%lld",&x);
 vector<int>d;d.reserve((size_t)n*m);
 for(auto x:a)for(auto y:b)if(y>=x)d.push_back((int)(y-x));
 sort(d.begin(),d.end());
 int best=0,bc=0;
 for(size_t i=0;i<d.size();){size_t j=i;while(j<d.size()&&d[j]==d[i])j++;if((int)(j-i)>bc){bc=j-i;best=d[i];}i=j;}
 printf("%d\n",best);}
