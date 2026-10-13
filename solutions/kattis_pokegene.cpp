#include <bits/stdc++.h>
using namespace std;
int main(){int n,q;scanf("%d %d",&n,&q);vector<string>s(n);static char buf[200005];for(auto&x:s){scanf("%s",buf);x=buf;}
vector<int>ord(n);iota(ord.begin(),ord.end(),0);sort(ord.begin(),ord.end(),[&](int a,int b){return s[a]<s[b];});
vector<int>rk(n),len(n);for(int i=0;i<n;i++){rk[ord[i]]=i;len[i]=s[ord[i]].size();}
int LG=1;while((1<<LG)<n)LG++;
vector<vector<int>> sp(LG+1,vector<int>(max(n,1),0));
for(int i=0;i+1<n;i++){const string&a=s[ord[i]],&b=s[ord[i+1]];int m=min(a.size(),b.size()),l=0;while(l<m&&a[l]==b[l])l++;sp[0][i]=l;}
for(int j=1;j<=LG;j++)for(int i=0;i+(1<<j)<=n-1;i++)sp[j][i]=min(sp[j-1][i],sp[j-1][i+(1<<(j-1))]);
auto lcp=[&](int a,int b)->int{ // ranks a<=b
 if(a==b)return len[a];int l=31-__builtin_clz(b-a);return min(sp[l][a],sp[l][b-(1<<l)]);};
vector<int>v;
while(q--){int K,L;scanf("%d %d",&K,&L);v.resize(K);for(auto&x:v){scanf("%d",&x);x=rk[x-1];}sort(v.begin(),v.end());
 long long ans=0;for(int i=0;i+L<=K;i++){int hi=lcp(v[i],v[i+L-1]);int lo=0;if(i>0)lo=max(lo,lcp(v[i-1],v[i]));if(i+L<K)lo=max(lo,lcp(v[i+L-1],v[i+L]));if(hi>lo)ans+=hi-lo;}
 printf("%lld\n",ans);}
}
