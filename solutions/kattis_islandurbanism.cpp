#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=(ll)4e18;
int main(){int n,m,v,k;scanf("%d %d %d %d",&n,&m,&v,&k);
 vector<int>u(v),st(v+1,0);for(int i=0;i<v;i++){scanf("%d",&u[i]);st[i+1]=st[i]+u[i];}
 vector<int>vil(n);for(int i=0;i<v;i++)for(int j=st[i];j<st[i+1];j++)vil[j]=i;
 vector<vector<pair<int,ll>>>adj(n);vector<ll>E(v,0);
 for(int i=0;i<m;i++){int a,b;ll c;scanf("%d %d %lld",&a,&b,&c);a--;b--;
  if(vil[a]==vil[b]){adj[a].push_back({b,c});adj[b].push_back({a,c});}
  else{int x=vil[a],y=vil[b];
   // ring edge between consecutive villages
   int j;if((x+1)%v==y)j=x;else j=y;
   E[j]=c;}}
 vector<vector<int>>T(v);for(int i=0;i<k;i++){int t;scanf("%d",&t);t--;T[vil[t]].push_back(t);}
 vector<ll>Cfull(v),Cf(v),Cl(v),Csplit(v),Cnone(v);
 vector<ll>dp;
 for(int i=0;i<v;i++){
  int sz=u[i],base=st[i];int f=0,l=sz-1;int nt=T[i].size();int nb=nt+1;int full=1<<nb;
  dp.assign((size_t)full*sz,INF);
  auto D=[&](int mask,int x)->ll&{return dp[(size_t)mask*sz+x];};
  for(int x=0;x<sz;x++)D(0,x)=0;
  for(int j=0;j<nt;j++)D(1<<j,T[i][j]-base)=0;
  D(1<<nt,l)=0;
  priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>pq;
  for(int mask=1;mask<full;mask++){
   ll*row=&dp[(size_t)mask*sz];
   for(int s=(mask-1)&mask;s>0;s=(s-1)&mask){
    if(s<(mask^s))continue;
    ll*r1=&dp[(size_t)s*sz];ll*r2=&dp[(size_t)(mask^s)*sz];
    for(int x=0;x<sz;x++){ll val=r1[x]+r2[x];if(val<row[x])row[x]=val;}
   }
   for(int x=0;x<sz;x++)if(row[x]<INF)pq.push({row[x],x});
   while(!pq.empty()){auto [d,x]=pq.top();pq.pop();if(d>row[x])continue;
    for(auto&e:adj[base+x]){int y=e.first-base;ll nd=d+e.second;if(nd<row[y]){row[y]=nd;pq.push({nd,y});}}}
  }
  int tm=(1<<nt)-1;
  Cfull[i]=D(tm|(1<<nt),f);
  Cf[i]=D(tm,f);Cl[i]=D(tm,l);
  ll mn=INF;for(int x=0;x<sz;x++)mn=min(mn,D(tm,x));Cnone[i]=mn;
  ll sp=INF;for(int s=0;s<=tm;s++)sp=min(sp,D(s,f)+D(tm^s,l));Csplit[i]=sp;
 }
 ll sumE=0,sumF=0;for(int i=0;i<v;i++){sumE+=E[i];sumF+=Cfull[i];}
 vector<int>tv;for(int i=0;i<v;i++)if(!T[i].empty())tv.push_back(i);
 int q=tv.size();ll ans=INF;
 for(int j=0;j<q;j++)ans=min(ans,sumE+sumF-Cfull[tv[j]]+Csplit[tv[j]]);
 if(q==1)ans=min(ans,Cnone[tv[0]]);
 else{
  for(int g=0;g<q;g++){int a=tv[g],b=tv[(g+1)%q];
   ll gc=0;int x=a;while(x!=b){gc+=E[x];x=(x+1)%v;if(x!=b)gc+=Cfull[x];}
   ans=min(ans,sumE+sumF-gc-Cfull[a]-Cfull[b]+Cf[a]+Cl[b]);}
 }
 printf("%lld\n",ans);}
