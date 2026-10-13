#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n;scanf("%d",&n);vector<ll>a(n);for(auto&x:a)scanf("%lld",&x);
 vector<int>nx(n+1,n);// nx[i]: first non-one index >= i
 for(int i=n-1;i>=0;i--)nx[i]=a[i]!=1?i:nx[i+1];
 vector<ll>pre(n+1,0);for(int i=0;i<n;i++)pre[i+1]=pre[i]+a[i];
 ll ans=0;
 for(int l=0;l<n;l++){ll lim=pre[n]-pre[l];ll P=a[l];int r=l;
  while(true){ // segment [l..r], product P, r is l or non-one
   ll S=pre[r+1]-pre[l]; if(r>l&&P==S)ans++;
   int q=nx[r+1];ll c=q-r-1; if(c>0&&P>=S+1&&P<=S+c)ans++;
   if(q>=n)break; if(P>lim/a[q])break; P*=a[q]; r=q;}
 }
 printf("%lld\n",ans);}
