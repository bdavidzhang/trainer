#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n,m;scanf("%d %d",&n,&m);vector<ll> s(n),p(m),t(m,0);for(auto&x:s)scanf("%lld",&x);for(auto&x:p)scanf("%lld",&x);
vector<int> ord(n);iota(ord.begin(),ord.end(),0);sort(ord.begin(),ord.end(),[&](int a,int b){return s[a]>s[b];});
vector<vector<int>> r(m);
for(int i:ord){int b=0;for(int j=1;j<m;j++){ // minimize (t_j+s)/p_j
 if((t[j]+s[i])*p[b]<(t[b]+s[i])*p[j])b=j;}
 t[b]+=s[i];r[b].push_back(i+1);}
for(int j=0;j<m;j++){printf("%d",(int)r[j].size());for(int x:r[j])printf(" %d",x);puts("");}}
