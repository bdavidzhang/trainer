#include <bits/stdc++.h>
using namespace std;
typedef long long ll;typedef pair<ll,ll> P;
static char buf[1<<25];size_t bl=0,bp=0;
inline int gc(){if(bp==bl){bl=fread(buf,1,sizeof buf,stdin);bp=0;if(!bl)return -1;}return buf[bp++];}
inline ll rd(){int c=gc();while(c!='-'&&(c<'0'||c>'9'))c=gc();bool ng=false;if(c=='-'){ng=true;c=gc();}ll x=0;while(c>='0'&&c<='9'){x=x*10+c-'0';c=gc();}return ng?-x:x;}
inline ll cr(const P&o,const P&a,const P&b){return (a.first-o.first)*(b.second-o.second)-(a.second-o.second)*(b.first-o.first);}
int main(){int n=rd();vector<P> p(n);for(auto&q:p){q.first=rd();q.second=rd();}
 sort(p.begin(),p.end());p.erase(unique(p.begin(),p.end()),p.end());n=p.size();
 vector<P> h(2*n+1);int k=0;
 for(int i=0;i<n;i++){while(k>=2&&cr(h[k-2],h[k-1],p[i])<=0)k--;h[k++]=p[i];}
 for(int i=n-2,t=k+1;i>=0;i--){while(k>=t&&cr(h[k-2],h[k-1],p[i])<=0)k--;h[k++]=p[i];}
 if(n>1)k--;
 h.resize(k);
 if(k<3){printf("0.000000\n");return 0;}
 long double best=1e30L;int j=1;
 for(int i=0;i<k;i++){const P&a=h[i];const P&b=h[(i+1)%k];
  while(cr(a,b,h[(j+1)%k])>cr(a,b,h[j]))j=(j+1)%k;
  long double d=(long double)cr(a,b,h[j])/sqrtl((long double)((b.first-a.first)*(b.first-a.first)+(b.second-a.second)*(b.second-a.second)));
  if(d<best)best=d;}
 printf("%.7Lf\n",best);}
