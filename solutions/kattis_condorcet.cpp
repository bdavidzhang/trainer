#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m; ll d[5][5]; int g[5];
bool feas(ll t){
    ll r[5];
    for(int a=0;a<n;a++){ ll need=t+1-d[g[a]][a]; r[a]=need<=0?0:(need+1)/2; if(r[a]>t) return false; }
    // cycles of functional graph
    int col[5]={0};
    for(int s=0;s<n;s++){
        if(col[s])continue;
        int v=s; while(!col[v]){col[v]=s+1;v=g[v];}
        if(col[v]==s+1){ // new cycle through v
            ll sum=0; int u=v; do{sum+=t-r[u];u=g[u];}while(u!=v);
            if(sum<t) return false;
        }
        v=s; while(col[v]==s+1){col[v]=100;v=g[v];}
    }
    return true;
}
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){ char s[8]; ll k; scanf("%s %lld",s,&k);
        for(int x=0;x<n;x++)for(int y=x+1;y<n;y++){int a=s[x]-'A',b=s[y]-'A'; d[a][b]+=k; d[b][a]-=k;} }
    ll best=LLONG_MAX; int tot=1; for(int i=0;i<n;i++)tot*=n;
    for(int code=0;code<tot;code++){
        int c=code; bool ok=true; for(int a=0;a<n;a++){g[a]=c%n;c/=n; if(g[a]==a)ok=false;}
        if(!ok)continue;
        for(int p=0;p<2;p++){
            ll lo=0,hi=2000000000LL;
            if(!feas(2*hi+p))continue;
            while(lo<hi){ll mid=(lo+hi)/2; if(feas(2*mid+p))hi=mid; else lo=mid+1;}
            best=min(best,2*lo+p);
        }
    }
    printf("%lld\n",best);
}
