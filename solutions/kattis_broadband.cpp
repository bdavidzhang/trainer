#include <bits/stdc++.h>
using namespace std;
int N;vector<double>x,p1,p2,prv,cur;
double cost(int l,int r){double s=p1[r]-p1[l],q=p2[r]-p2[l];return q-s*s/(r-l);} // (l,r]
void go(int lo,int hi,int ol,int oh){if(lo>hi)return;int mid=(lo+hi)/2;double b=1e300;int bi=ol;
 for(int j=ol;j<=min(oh,mid-1);j++){if(prv[j]>=1e299)continue;double v=prv[j]+cost(j,mid);if(v<b){b=v;bi=j;}}
 cur[mid]=b;go(lo,mid-1,ol,bi);go(mid+1,hi,bi,oh);}
int main(){int m,n,k;double s;cin>>m>>n>>k>>s;N=m+n;x.resize(N);for(auto&v:x)cin>>v;sort(x.begin(),x.end());
 p1.assign(N+1,0);p2.assign(N+1,0);for(int i=0;i<N;i++){p1[i+1]=p1[i]+x[i];p2[i+1]=p2[i]+x[i]*x[i];}
 prv.assign(N+1,1e300);prv[0]=0;double best=1e300;
 for(int t=1;t<=k;t++){cur.assign(N+1,1e300);go(1,N,0,N-1);prv=cur;best=min(best,prv[N]);}
 printf("%.8f\n",best+N*s*s/4.0);}
