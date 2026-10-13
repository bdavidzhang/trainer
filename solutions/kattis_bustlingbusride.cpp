#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,b;ll r,w;vector<ll>D;vector<int>t;
vector<int>f1,f2,cntStop;
void upd(vector<int>&f,int i,int v){for(;i<=b;i+=i&-i)f[i]+=v;}
int qry(vector<int>&f,int i){int s=0;for(;i>0;i-=i&-i)s+=f[i];return s;}
bool feas(ll T){
 int i=0;
 for(ll j=0;;j++){
  if(i==n)return true;
  ll base=j*r;if(base>T)return false;
  ll cost=0,mx=0;int st=i,cntP=0;
  while(i<n){int x=t[i];ll delta;
   if(cntStop[x])delta=2LL*qry(f1,x);
   else delta=2LL*qry(f1,x-1)+2+2LL*(cntP-qry(f2,x));
   ll nm=max(mx,D[x]);
   if(base+w*(cost+delta)+nm<=T){cost+=delta;mx=nm;if(!cntStop[x])upd(f1,x,1);cntStop[x]++;upd(f2,x,1);cntP++;i++;}
   else break;}
  for(int p=st;p<i;p++){int x=t[p];cntStop[x]--;if(!cntStop[x])upd(f1,x,-1);upd(f2,x,-1);}
  if(i==st)return false;
 }
}
int main(){scanf("%d %d %lld %lld",&n,&b,&r,&w);D.assign(b+1,0);for(int i=1;i<=b;i++){ll d;scanf("%lld",&d);D[i]=D[i-1]+d;}
 t.resize(n);for(int&x:t)scanf("%d",&x);
 f1.assign(b+1,0);f2.assign(b+1,0);cntStop.assign(b+1,0);
 ll lo=0,hi=(ll)(n-1)*r+2*w+D[b];
 while(lo<hi){ll mid=(lo+hi)/2;if(feas(mid))hi=mid;else lo=mid+1;}
 printf("%lld\n",lo);}
