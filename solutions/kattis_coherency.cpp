#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int par[200005];
int fnd(int x){while(par[x]!=x){par[x]=par[par[x]];x=par[x];}return x;}
int main(){
    int n;scanf("%d",&n);
    vector<ll> x(n),y(n),d(n);
    const ll C=211, W=600000;
    vector<pair<ll,int>> a(n);
    for(int i=0;i<n;i++){
        scanf("%lld %lld %lld",&x[i],&y[i],&d[i]);
        a[i]={(x[i]/C+1)*W+(y[i]/C+1),i};
    }
    sort(a.begin(),a.end());
    vector<ll> keys(n);
    for(int i=0;i<n;i++)keys[i]=a[i].first;
    for(int i=0;i<n;i++)par[i]=i;
    vector<int> deg(n,0);
    int comps=n;
    for(int p=0;p<n;p++){
        int i=a[p].second;
        ll cx=keys[p]/W, cy=keys[p]%W;
        for(ll gx=cx-1;gx<=cx+1;gx++){
            ll lo=gx*W+cy-1, hi=gx*W+cy+1;
            int q=lower_bound(keys.begin(),keys.end(),lo)-keys.begin();
            for(;q<n&&keys[q]<=hi;q++){
                int j=a[q].second;
                if(j<=i)continue;
                ll dx=x[i]-x[j],dy=y[i]-y[j];
                ll th=508+5*(d[i]+d[j]);
                if(100*(dx*dx+dy*dy)<=th*th){
                    deg[i]++;deg[j]++;
                    int u=fnd(i),v=fnd(j);
                    if(u!=v){par[u]=v;comps--;}
                }
            }
        }
    }
    bool ok=comps==1;
    if(ok&&n>=7)for(int i=0;i<n;i++)if(deg[i]<2){ok=false;break;}
    puts(ok?"yes":"no");
}
