#include <bits/stdc++.h>
using namespace std;
// 0-1 principle + segment tree over thresholds.
int N;vector<long long>mx,lz;
const long long NEG=-(1LL<<40);
void build(int o,int l,int r,const vector<long long>&init){lz[o]=0;if(l==r){mx[o]=init[l];return;}int m=(l+r)/2;build(2*o,l,m,init);build(2*o+1,m+1,r,init);mx[o]=max(mx[2*o],mx[2*o+1]);}
void upd(int o,int l,int r,int a,int b,long long v){if(a>b||b<l||r<a)return;if(a<=l&&r<=b){mx[o]+=v;lz[o]+=v;return;}int m=(l+r)/2;upd(2*o,l,m,a,b,v);upd(2*o+1,m+1,r,a,b,v);mx[o]=max(mx[2*o],mx[2*o+1])+lz[o];}
long long qry(int o,int l,int r,int a,int b){if(a>b||b<l||r<a)return NEG*4;if(a<=l&&r<=b)return mx[o];int m=(l+r)/2;return max(qry(2*o,l,m,a,b),qry(2*o+1,m+1,r,a,b))+lz[o];}
int main(){int n;scanf("%d",&n);N=n+1;vector<int>a(N);for(auto&x:a)scanf("%d",&x);
 vector<int>ord(N);iota(ord.begin(),ord.end(),0);stable_sort(ord.begin(),ord.end(),[&](int x,int y){return a[x]<a[y];});
 mx.assign(4*N,0);lz.assign(4*N,0);vector<long long>init(N);
 for(int i=0;i<N;i++)init[i]=NEG+i+(i%2==0?1:0);
 build(1,0,N-1,init);
 vector<char>zero(N,0);int first=0;long long ans=0;
 for(int k=0;k<N;k++){int p=ord[k];zero[p]=1;
  upd(1,0,N-1,p,p,-NEG);upd(1,0,N-1,p+1,N-1,-1);upd(1,0,N-1,0,p-1,1);
  while(first<N&&zero[first])first++;
  if(first<N)ans=max(ans,qry(1,0,N-1,first+1,N-1));}
 printf("%lld\n",ans);}
