#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n;scanf("%d",&n);vector<ll>P(n+1,0);for(int i=1;i<=n;i++){ll x;scanf("%lld",&x);P[i]=P[i-1]+x;}
ll S=P[n];
// f[i]: minimal last gap when last fold is at prefix position i (i=0: no fold, gap 0)
// f[i]=P[i]-P[j], j = largest j<i with P[j]+f[j]<=P[i]
vector<ll> key(n+1);deque<int> dq;key[0]=0;dq.push_back(0);ll ans=S;
for(int i=1;i<n;i++){
  while(dq.size()>=2&&key[dq[1]]<=P[i])dq.pop_front();
  int j=dq.front();ll f=P[i]-P[j];key[i]=P[i]+f;
  ans=min(ans,max(f,S-P[i]));
  while(!dq.empty()&&key[dq.back()]>=key[i])dq.pop_back();
  dq.push_back(i);
}
printf("%lld\n",ans);}
