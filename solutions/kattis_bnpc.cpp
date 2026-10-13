#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n;ll k;cin>>n>>k;unordered_map<string,int>id;vector<ll>s(n);for(int i=0;i<n;i++){string a;cin>>a>>s[i];id[a]=i;}
 int l;cin>>l;vector<ll>mx(n,-1),e(n,0),c(n,0);vector<vector<ll>>ev(n);
 for(int i=0;i<l;i++){string a;ll t;cin>>a>>t;int j=id[a];c[j]++;ev[j].push_back(t);if(t>mx[j]){mx[j]=t;e[j]=1;}else if(t==mx[j])e[j]++;}
 ll base=0,cmax=0;vector<ll>first;
 for(int j=0;j<n;j++){if(!c[j])continue;if(s[j]<mx[j]){k-=mx[j]-s[j];s[j]=mx[j];if(k<0){puts("0");return 0;}}
  cmax=max(cmax,c[j]);
  if(s[j]==mx[j]){base+=s[j]*(c[j]-e[j]);first.push_back(s[j]*e[j]+c[j]);}else base+=s[j]*c[j];}
 sort(first.rbegin(),first.rend());
 for(ll g:first){if(k<=0||g<=cmax)break;base+=g;k--;}
 base+=k*cmax;printf("%lld\n",base);}
