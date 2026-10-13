#include <bits/stdc++.h>
using namespace std;
const long long MOD=1000000007;
int main(){int n;if(scanf("%d",&n)!=1)return 0;
 const int B=15;mt19937_64 rng(712367);vector<long long>a(B);unordered_map<long long,int>mp;
 // choose block values so that all 2^B operator strings give distinct results starting from 0
 while(true){for(auto&x:a)x=2+rng()%(MOD-2);
  vector<long long>cur(1,0);
  for(int k=0;k<B;k++){vector<long long>nx(cur.size()*2);for(size_t i=0;i<cur.size();i++){nx[i]=(cur[i]+a[k])%MOD;nx[i|((size_t)1<<k)]=cur[i]*a[k]%MOD;}cur.swap(nx);}
  vector<long long>s=cur;sort(s.begin(),s.end());if(adjacent_find(s.begin(),s.end())==s.end())break;}
 string ops(n+1,'?');
 for(int r=n;r>=1;r-=B){int l=max(1,r-B+1),len=r-l+1;
  // table for this length (prefix of a); mask bit k set = op_{l+k} is multiply
  mp.clear();{vector<long long>cur(1,0);for(int k=0;k<len;k++){vector<long long>nx(cur.size()*2);for(size_t i=0;i<cur.size();i++){nx[i]=(cur[i]+a[k])%MOD;nx[i|((size_t)1<<k)]=cur[i]*a[k]%MOD;}cur.swap(nx);}
   for(size_t i=0;i<cur.size();i++)mp[cur[i]]=(int)i;}
  string q="?";q.reserve(12*(n+2));
  for(int i=0;i<=n;i++){q+=' ';if(i<l)q+='0';else if(i<=r)q+=to_string(a[i-l]);else q+=(ops[i]=='x'?'1':'0');}
  puts(q.c_str());fflush(stdout);
  long long res;if(scanf("%lld",&res)!=1)return 0;
  int mask=mp[res];for(int k=0;k<len;k++)ops[l+k]=(mask>>k&1)?'x':'+';}
 printf("! %s\n",ops.c_str()+1);fflush(stdout);}
