#include <bits/stdc++.h>
using namespace std;
int n,m; vector<string> g; vector<int> id;
int dr[4]={-1,0,1,0},dc[4]={0,1,0,-1};
// returns -2 fail, else gid*2+orient (0=V,1=H)
int trace_(int r,int c,int d){
    while(true){
        int nr=r+dr[d],nc=c+dc[d];
        if(nr<0||nr>=n||nc<0||nc>=m){d^=2;nr=r;nc=c;}
        r=nr;c=nc; char ch=g[r][c];
        if(ch=='.')continue;
        if(ch=='#')return -2;
        if(ch=='\\'){ static const int t[4]={3,2,1,0}; d=t[d]; continue;}
        if(ch=='/'){ static const int t[4]={1,0,3,2}; d=t[d]; continue;}
        return id[r*m+c]*2+((d&1)?1:0);
    }
}
int main(){
    scanf("%d %d",&n,&m); g.resize(n); char buf[1024];
    for(int i=0;i<n;i++){scanf("%s",buf);g[i]=buf;}
    id.assign(n*m,-1); int G=0; vector<int> init;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(g[i][j]=='V'||g[i][j]=='H'){id[i*m+j]=G++;init.push_back(g[i][j]=='H');}
    vector<array<char,2>> forb(G,{0,0}); vector<vector<pair<int,int>>> adj(G);
    bool bad=false;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){int v=id[i*m+j]; if(v<0)continue;
        for(int o=0;o<2;o++)for(int d=o;d<4;d+=2){
            int res=trace_(i,j,d);
            if(res==-2){forb[v][o]=1;continue;}
            int w=res/2,oo=res&1;
            if(w==v){ if(oo!=o)bad=true; continue;}
            adj[v].push_back({w,o^oo}); adj[w].push_back({v,o^oo});
        }
    }
    if(bad){puts("-1");return 0;}
    vector<int> col(G,-1); long long ans=0;
    for(int s=0;s<G;s++){ if(col[s]>=0)continue;
        vector<int> comp; col[s]=0; comp.push_back(s); bool ok=true;
        for(size_t h=0;h<comp.size();h++){int v=comp[h]; for(auto&e:adj[v]){int w=e.first; int c=col[v]^e.second; if(col[w]<0){col[w]=c;comp.push_back(w);} else if(col[w]!=c)ok=false;}}
        if(!ok){puts("-1");return 0;}
        long long best=LLONG_MAX;
        for(int f=0;f<2;f++){ bool fe=true; long long c=0; for(int v:comp){int x=col[v]^f; if(forb[v][x]){fe=false;break;} c+=(x!=init[v]);} if(fe)best=min(best,c);}
        if(best==LLONG_MAX){puts("-1");return 0;}
        ans+=best;
    }
    printf("%lld\n",ans);
}
