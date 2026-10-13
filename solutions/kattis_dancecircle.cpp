#include <bits/stdc++.h>
using namespace std;
int n;vector<int>p,par;
vector<int> sz;
int fnd(int x){if(p[x]==x)return x;int r=fnd(p[x]);par[x]^=par[p[x]];return p[x]=r;}
int main(){scanf("%d",&n);vector<int>A(n),B(n),X(n),W(n);
 for(int i=0;i<n;i++){int l,r,x;scanf("%d %d %d",&l,&r,&x);int a=((i-l)%n+n)%n;int len=l+r+1;X[i]=x;A[i]=a;
  if(a+len<=n){B[i]=a+len;W[i]=0;}else{B[i]=a+len-n;W[i]=1;}}
 const long long MOD=1e9+7;long long ans=0;
 for(int T=0;T<2;T++){p.assign(n+1,0);par.assign(n+1,0);sz.assign(n+1,1);iota(p.begin(),p.end(),0);int comp=n+1;bool ok=true;
  auto add=[&](int a,int b,int w){int ra=fnd(a),rb=fnd(b);int d=par[a]^par[b]^w;if(ra==rb){if(d)ok=false;return;}if(sz[ra]>sz[rb])swap(ra,rb);p[ra]=rb;par[ra]=d;sz[rb]+=sz[ra];comp--;};
  add(0,n,T);for(int i=0;i<n&&ok;i++)add(A[i],B[i],X[i]^(W[i]?T:0));
  if(ok){long long r=1;for(int i=0;i<comp-1;i++)r=r*2%MOD;ans=(ans+r)%MOD;}}
 printf("%lld\n",ans);}
