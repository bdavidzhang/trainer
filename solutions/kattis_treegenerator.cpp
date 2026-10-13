#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int L=18;
int n,q;ll m;
vector<int> adj[200005];
int up[L][200005],uv[L][200005],dv[L][200005],dep[200005],dg[200005];
ll pw[200005];
int main(){scanf("%d %lld %d",&n,&m,&q);for(int i=0;i<n-1;i++){int x,y;scanf("%d %d",&x,&y);adj[x].push_back(y);adj[y].push_back(x);}
    for(int i=1;i<=n;i++)scanf("%d",&dg[i]);
    pw[0]=1%m;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*10%m;
    vector<int> ord;ord.reserve(n);ord.push_back(1);up[0][1]=0;dep[1]=0;
    for(int i=0;i<(int)ord.size();i++){int v=ord[i];for(int u:adj[v])if(u!=up[0][v]){up[0][u]=v;dep[u]=dep[v]+1;ord.push_back(u);}}
    for(int v=1;v<=n;v++)uv[0][v]=dv[0][v]=dg[v]%m;
    for(int k=1;k<L;k++){ll p=pw[min(n,1<<(k-1))];for(int v=1;v<=n;v++){int a=up[k-1][v];up[k][v]=up[k-1][a];
        if(a){uv[k][v]=(uv[k-1][v]*p+uv[k-1][a])%m;dv[k][v]=(dv[k-1][a]*p+dv[k-1][v])%m;}}}
    while(q--){int a,b;scanf("%d %d",&a,&b);
        int x=a,y=b;if(dep[x]<dep[y])swap(x,y);int d=dep[x]-dep[y];for(int k=0;k<L;k++)if(d>>k&1)x=up[k][x];
        if(x!=y){for(int k=L-1;k>=0;k--)if(up[k][x]!=up[k][y]){x=up[k][x];y=up[k][y];}x=up[0][x];}
        int l=x;
        int la=dep[a]-dep[l]+1,lb=dep[b]-dep[l];
        ll A=0;int cur=a;for(int k=0;k<L;k++)if(la>>k&1){A=(A*pw[1<<k]+uv[k][cur])%m;cur=up[k][cur];}
        ll B=0;int len=0;cur=b;for(int k=0;k<L;k++)if(lb>>k&1){B=(dv[k][cur]*pw[len]+B)%m;len+=1<<k;cur=up[k][cur];}
        printf("%lld\n",(A*pw[lb]+B)%m);}
}
