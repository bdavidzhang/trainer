#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<int> s(n),a(n),b(n);for(int i=0;i<n;i++)scanf("%d %d %d",&s[i],&a[i],&b[i]);
  const int T=2000005;
  // S[t] = sum_{u>=t} f(u), f(t)=best expected count when free at time t
  vector<double> S(T+2,0.0);
  int i=n-1;double fn=0; // f(t+1)
  for(int t=1000000;t>=1;t--){double best=fn;
    while(i>=0&&s[i]==t){double v=1+(S[t+a[i]]-S[t+b[i]+1])/(b[i]-a[i]+1);best=max(best,v);i--;}
    fn=best;S[t]=S[t+1]+best;}
  printf("%.9f\n",fn);}
