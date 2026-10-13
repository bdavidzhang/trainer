#include <bits/stdc++.h>
using namespace std;
int par[1000005]; char px[1000005];
int find(int x,int &parity){ int r=x,p=0; while(par[r]!=r){p^=px[r]; r=par[r];}
    // compress
    int cur=x,cp=p; while(par[cur]!=cur){ int nx=par[cur]; int np=cp^px[cur]; par[cur]=r; px[cur]=cp; cur=nx; cp=np; }
    parity=p; return r; }
int main(){
    int n,m; long long p; scanf("%d %d %lld",&n,&m,&p);
    for(int i=1;i<=n;i++){par[i]=i;px[i]=0;}
    int comps=n; bool bad=false;
    for(int i=0;i<m;i++){ int a,b; scanf("%d %d",&a,&b); int pa,pb; int ra=find(a,pa), rb=find(b,pb);
        if(ra==rb){ if(pa==pb) bad=true; } else { par[ra]=rb; px[ra]=pa^pb^1; comps--; } }
    if(bad){ puts("impossible"); return 0; }
    long long r=1%p; for(int i=0;i<comps-1;i++) r=r*2%p;
    printf("%lld\n",(r+1)%p);
}
