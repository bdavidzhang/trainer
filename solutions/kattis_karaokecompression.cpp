#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;int n=s.size();
vector<int> sa(n),rk(n),tmp(n),lcp(n,0);
for(int i=0;i<n;i++){sa[i]=i;rk[i]=s[i];}
for(int k=1;;k<<=1){auto cmp=[&](int a,int b){if(rk[a]!=rk[b])return rk[a]<rk[b];int ra=a+k<n?rk[a+k]:-1,rb=b+k<n?rk[b+k]:-1;return ra<rb;};
 sort(sa.begin(),sa.end(),cmp);tmp[sa[0]]=0;for(int i=1;i<n;i++)tmp[sa[i]]=tmp[sa[i-1]]+(cmp(sa[i-1],sa[i])?1:0);rk=tmp;if(rk[sa[n-1]]==n-1)break;}
// kasai: lcp[i] = lcp(sa[i-1],sa[i])
for(int i=0,h=0;i<n;i++){if(rk[i]>0){int j=sa[rk[i]-1];while(i+h<n&&j+h<n&&s[i+h]==s[j+h])h++;lcp[rk[i]]=h;if(h>0)h--;}else h=0;}
int best=n+1;vector<int> id(n),last(n),cnt(n);
for(int L=2;L<=n;L++){int g=0;for(int i=0;i<n;i++){if(i>0&&lcp[i]<L)g=i;id[sa[i]]=g;}
 fill(last.begin(),last.end(),0);fill(cnt.begin(),cnt.end(),0);int mx=0;
 for(int i=0;i+L<=n;i++){int d=id[i];if(i>=last[d]){last[d]=i+L;if(++cnt[d]>mx)mx=cnt[d];}}
 if(mx<2&&L>1){ if(mx==1) best=min(best,L+n-(L-1)); break;}
 best=min(best,L+n-mx*(L-1));}
cout<<best<<"\n";}
