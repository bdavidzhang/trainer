#include <bits/stdc++.h>
using namespace std;
int main(){int n;long long k;scanf("%d %lld",&n,&k);int N=1<<n;vector<long long>r(N);for(auto&x:r)scanf("%lld",&x);
 sort(r.rbegin(),r.rend());long long ans=0;
 for(int h=1;h<N;h*=2){ // A = r[0..h), B = r[h..2h), both descending
  int j=h;
  for(int i=0;i<h;i++){ if(r[i]-r[j]<=k){ans++;j++;} }
 }
 printf("%lld\n",ans);}
