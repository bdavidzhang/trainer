#include <bits/stdc++.h>
using namespace std;
struct Pass{int lo,hi,sum,eL,eR;};
int main(){int n,m;if(scanf("%d %d",&n,&m)!=2)return 0;
 vector<char>sh(m+2),ld(m+2);
 vector<int>prevL;vector<vector<int>>f;
 const int NEG=INT_MIN/2;
 int ans=0;
 vector<int>ps(m+1),pc(m+1),val(m),nl(m),nr(m);
 for(int k=0;k<n;k++){
  scanf("%s",sh.data());scanf("%s",ld.data());
  for(int i=0;i<m;i++){int v=(sh[i]>='1'&&sh[i]<='9')?sh[i]-'0':0;val[i]=v;ps[i+1]=ps[i]+v;pc[i+1]=pc[i]+(v>0);}
  {int last=-1;for(int i=0;i<m;i++){nl[i]=last;if(val[i])last=i;}last=-1;for(int i=m-1;i>=0;i--){nr[i]=last;if(val[i])last=i;}}
  vector<int>cur;for(int i=0;i<m;i++)if(ld[i]=='|')cur.push_back(i);
  int K=cur.size();
  auto mk=[&](int p,int q){Pass r;r.lo=min(p,q);r.hi=max(p,q);r.sum=ps[r.hi+1]-ps[r.lo];r.eL=val[r.lo]?-1:nl[r.lo];r.eR=val[r.hi]?-1:nr[r.hi];return r;};
  vector<vector<int>>nf(K,vector<int>(K,NEG));
  if(k==0){for(int c=0;c<K;c++)for(int d=0;d<K;d++)nf[c][d]=0;}
  else{int P=prevL.size();
   vector<Pass>dn(P*K),up(P*K);
   for(int a=0;a<P;a++)for(int c=0;c<K;c++){dn[a*K+c]=mk(prevL[a],cur[c]);up[a*K+c]=dn[a*K+c];}
   for(int a=0;a<P;a++)for(int b=0;b<P;b++){int base=f[a][b];if(base<=NEG)continue;
    {Pass t=mk(prevL[a],prevL[b]);int g=base+t.sum;if(t.eL>=0)g+=val[t.eL];if(t.eR>=0)g+=val[t.eR];ans=max(ans,g);}
    for(int c=0;c<K;c++){const Pass&x=dn[a*K+c];
     for(int d=0;d<K;d++){const Pass&y=up[b*K+d];
      int lo=max(x.lo,y.lo),hi=min(x.hi,y.hi);
      if(lo<=hi&&pc[hi+1]-pc[lo]>0)continue;
      int g=base+x.sum+y.sum;
      int e1=-1,e2=-1;
      if(x.eL>=0&&(x.eL<y.lo||x.eL>y.hi)){g+=val[x.eL];e1=x.eL;}
      if(x.eR>=0&&(x.eR<y.lo||x.eR>y.hi)){g+=val[x.eR];e2=x.eR;}
      if(y.eL>=0&&(y.eL<x.lo||y.eL>x.hi)&&y.eL!=e1&&y.eL!=e2)g+=val[y.eL];
      if(y.eR>=0&&(y.eR<x.lo||y.eR>x.hi)&&y.eR!=e1&&y.eR!=e2)g+=val[y.eR];
      if(g>nf[c][d])nf[c][d]=g;}}}}
  f.swap(nf);prevL=cur;}
 for(auto&r:f)for(int v:r)ans=max(ans,v);
 printf("%d\n",ans);}
