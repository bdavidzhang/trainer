#include <bits/stdc++.h>
using namespace std;
typedef long long ll; const ll MOD=998244353;
static int E[3003][3003],TL[3003][3003],TR[3003][3003];
static short CL[3003][3003],CR[3003][3003];
int main(){int n;scanf("%d",&n);vector<pair<ll,ll>> c(n);
 for(auto&p:c)scanf("%lld %lld",&p.first,&p.second);
 sort(c.begin(),c.end());
 vector<ll> a(n+2);for(int i=1;i<=n;i++)a[i]=c[i-1].first;
 // type: 0 = blocked range to the right (i, r], 1 = range to the left [l, i)
 vector<int> typ(n+2,0),lim(n+2,0);
 vector<vector<int>> byR(n+2),byL(n+2);
 for(int i=1;i<=n;i++){ll b=c[i-1].second;
   if(b>=a[i]){int r=int(lower_bound(a.begin()+1,a.begin()+n+1,b)-a.begin())-1; // last a<b
     if(r<i)r=i; typ[i]=0;lim[i]=r;byR[r].push_back(i);}
   else{int l=int(upper_bound(a.begin()+1,a.begin()+n+1,b)-a.begin()); // first a>b
     typ[i]=1;lim[i]=l;byL[l].push_back(i);}
 }
 vector<ll> inv(n+2,1);for(int i=2;i<=n+1;i++)inv[i]=(MOD-(MOD/i)*inv[MOD%i]%MOD)%MOD;
 // E[L][R]: boundaries L,R placed, nothing in between yet. alive c in (L,R): typ0 with lim<R, typ1 with lim>L
 // TL[L][R]=sum alive c of E[L][c]; TR[L][R]=sum alive c of E[c][R]; CL+CR = count alive
 for(int L=n;L>=0;L--){
   for(int R=L+1;R<=n+1;R++){
     if(R==L+1){E[L][R]=0;TL[L][R]=0;TR[L][R]=0;CL[L][R]=0;CR[L][R]=0;continue;}
     // TL, CL(count of all alive) built along R with L fixed
     ll tl=TL[L][R-1]; int cnt=CL[L][R-1];
     { int x=R-1; if(typ[x]==1&&lim[x]>L){tl+=E[L][x];cnt++;}
       for(int cc:byR[R-1]) if(cc>L){tl+=E[L][cc];cnt++;} }
     tl%=MOD;
     // TR built along L with R fixed
     ll tr=TR[L+1][R];
     { int x=L+1; if(typ[x]==0&&lim[x]<R){tr+=E[x][R];}
       for(int cc:byL[L+1]) if(cc<R){tr+=E[cc][R];} }
     tr%=MOD;
     TL[L][R]=(int)tl;TR[L][R]=(int)tr;CL[L][R]=(short)cnt;
     if(cnt==0)E[L][R]=0; else E[L][R]=(int)((1+(tl+tr)%MOD*inv[cnt])%MOD);
   }
 }
 printf("%d\n",E[0][n+1]);
}
