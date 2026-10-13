#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<vector<ll>> amt(n, vector<ll>(m));
    for(int j=0;j<n;j++) for(int i=0;i<m;i++) scanf("%lld",&amt[j][i]);
    const ll INF=1e18;
    vector<vector<ll>> d(n, vector<ll>(n));
    for(int j=0;j<n;j++) for(int i=0;i<n;i++){ ll x; scanf("%lld",&x); d[j][i]= x<0?INF:x; }
    for(int i=0;i<n;i++) d[i][i]=0;
    for(int k=0;k<n;k++) for(int i=0;i<n;i++) if(d[i][k]<INF) for(int j=0;j<n;j++) if(d[k][j]<INF) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
    // cost[p][w]
    vector<vector<ll>> a(m+1, vector<ll>(n+1,0));
    for(int p=0;p<m;p++) for(int w=0;w<n;w++){
        ll s=0; for(int j=0;j<n;j++) s+=amt[j][p]*d[j][w];
        a[p+1][w+1]=s;
    }
    vector<ll> u(m+1),v(n+1); vector<int> p(n+1),way(n+1);
    for(int i=1;i<=m;i++){
        p[0]=i; int j0=0; vector<ll> minv(n+1,INF); vector<char> used(n+1,false);
        do{
            used[j0]=true; int i0=p[j0],j1=0; ll delta=INF;
            for(int j=1;j<=n;j++) if(!used[j]){
                ll cur=a[i0][j]-u[i0]-v[j];
                if(cur<minv[j]){minv[j]=cur;way[j]=j0;}
                if(minv[j]<delta){delta=minv[j];j1=j;}
            }
            for(int j=0;j<=n;j++) if(used[j]){u[p[j]]+=delta;v[j]-=delta;} else minv[j]-=delta;
            j0=j1;
        }while(p[j0]!=0);
        do{int j1=way[j0];p[j0]=p[j1];j0=j1;}while(j0);
    }
    printf("%lld\n",-v[0]);
}
