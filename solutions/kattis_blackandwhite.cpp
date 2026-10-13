#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;vector<double>p(n);for(auto&x:p)cin>>x;int F=1<<n;
 vector<double>P(F),Q(F),E(F,0);P[0]=Q[0]=1;
 for(int m=1;m<F;m++){int i=__builtin_ctz(m);P[m]=P[m&(m-1)]*p[i];Q[m]=Q[m&(m-1)]*(1-p[i]);}
 for(int m=1;m<F;m++){if(__builtin_popcount(m)<3)continue;double s=0,acc=1;
  for(int i=0;i<n;i++)if(m>>i&1){int o=m^(1<<i);double q=p[i]*Q[o]+(1-p[i])*P[o];s+=q;acc+=q*E[o];}
  E[m]=acc/s;}
 printf("%.9f\n",E[F-1]);}
