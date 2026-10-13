#include <bits/stdc++.h>
using namespace std;
int main(){int n;if(scanf("%d",&n)!=1)return 0;
vector<long long> pre(n+1,0);
for(int r=2;r<=n;r++){printf("? 1 %d\n",r);fflush(stdout);if(scanf("%lld",&pre[r])!=1||pre[r]<0)return 0;}
// c[r] = number of earlier elements greater than p_r
vector<int> p(n+1),rem(n);iota(rem.begin(),rem.end(),1);
for(int r=n;r>=1;r--){int c=(int)(pre[r]-pre[r-1]);int idx=r-c-1; // (r-c)-th smallest among remaining
 p[r]=rem[idx];rem.erase(rem.begin()+idx);}
vector<int> t;for(int i=1;i<=n;i++){auto it=lower_bound(t.begin(),t.end(),p[i]);if(it==t.end())t.push_back(p[i]);else *it=p[i];}
printf("! %d\n",(int)t.size());fflush(stdout);}
