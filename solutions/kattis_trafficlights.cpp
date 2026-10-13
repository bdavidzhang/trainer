#include <bits/stdc++.h>
using namespace std;
// Light i is green at integer time t iff t mod (r+g) >= r. t = lcm-1 always works, so the answer exists.
int main(){int n;cin>>n;vector<int>r(n),p(n);for(int i=0;i<n;i++){int g;cin>>r[i]>>g;p[i]=r[i]+g;}
 // check lights with smallest green fraction first so a red light is found early
 vector<int>o(n);iota(o.begin(),o.end(),0);sort(o.begin(),o.end(),[&](int x,int y){return (p[x]-r[x])*p[y]<(p[y]-r[y])*p[x];});
 vector<int>R(n),P(n);for(int i=0;i<n;i++){R[i]=r[o[i]];P[i]=p[o[i]];}
 long long t=1;
 while(true){long long jump=0;for(int i=0;i<n;i++){int c=t%P[i];if(c<R[i]){jump=R[i]-c;break;}}
  if(!jump){cout<<t<<"\n";return 0;}t+=jump;}
}
