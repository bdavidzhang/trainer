#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int main(){int n,x,y,d;cin>>n>>x>>y>>d;
 vector<vector<ull>> f(n+2,vector<ull>(n+2,0)),g;
 f[x][y]=1;
 auto mv=[&](int p,int dir){int q=p+dir;if(q<1||q>n)q=p;return q;};
 for(int t=0;t<d;t++){g.assign(n+2,vector<ull>(n+2,0));
  for(int a=1;a<=n;a++)for(int b=1;b<=n;b++)if(f[a][b]){
   for(int da=-1;da<=1;da+=2)for(int db=-1;db<=1;db+=2){int na=mv(a,da),nb=mv(b,db);if(na!=nb)g[na][nb]+=f[a][b];}
  }
  f=g;}
 ull tot=1ULL<<(2*d),s=0;for(auto&r:f)for(ull v:r)s+=v;
 ull num=tot-s;ull gg=std::gcd(num,tot);
 printf("%llu/%llu\n",num/gg,tot/gg);}
