#include <bits/stdc++.h>
using namespace std;
int R,C;
vector<string> g;
vector<int> nxt,cntS;
vector<array<int,4>> spots;
int distinct=0,ans=0;
inline void add(int v){ for(int k=0;k<4;k++){int s=spots[v][k]; if(s>=0&&cntS[s]++==0)distinct++;} }
inline void rem(int v){ for(int k=0;k<4;k++){int s=spots[v][k]; if(s>=0&&--cntS[s]==0)distinct--;} }
int main(){
    scanf("%d %d",&R,&C);
    g.resize(R);
    for(int i=0;i<R;i++){char buf[600];scanf("%s",buf);g[i]=buf;}
    int N=R*C;
    nxt.assign(N,-1);cntS.assign(N,0);spots.resize(N);
    auto river=[&](int r,int c){return r>=0&&r<R&&c>=0&&c<C&&g[r][c]!='.'&&g[r][c]!='#';};
    int dr[4]={-1,1,0,0},dc[4]={0,0,1,-1};
    for(int r=0;r<R;r++)for(int c=0;c<C;c++){
        int v=r*C+c; spots[v].fill(-1);
        if(!river(r,c))continue;
        for(int k=0;k<4;k++){int a=r+dr[k],b=c+dc[k]; if(a>=0&&a<R&&b>=0&&b<C&&g[a][b]=='#')spots[v][k]=a*C+b;}
        int k=g[r][c]=='^'?0:g[r][c]=='v'?1:g[r][c]=='>'?2:3;
        int a=r+dr[k],b=c+dc[k];
        if(river(a,b))nxt[v]=a*C+b;
    }
    // reverse graph CSR
    vector<int> head(N+1,0),ch;
    for(int v=0;v<N;v++)if(nxt[v]>=0)head[nxt[v]+1]++;
    for(int i=0;i<N;i++)head[i+1]+=head[i];
    ch.resize(head[N]);
    {vector<int> pos(head.begin(),head.end()-1); for(int v=0;v<N;v++)if(nxt[v]>=0)ch[pos[nxt[v]]++]=v;}
    // cycle detection
    vector<char> onCyc(N,0); vector<int> col(N,0);
    vector<vector<int>> cycles;
    for(int r=0;r<R;r++)for(int c=0;c<C;c++){
        int s=r*C+c; if(!river(r,c)||col[s])continue;
        int v=s; vector<int> path;
        while(v>=0&&col[v]==0){col[v]=1;path.push_back(v);v=nxt[v];}
        if(v>=0&&col[v]==1){
            vector<int> cyc; int u=v; do{cyc.push_back(u);onCyc[u]=1;u=nxt[u];}while(u!=v);
            cycles.push_back(cyc);
        }
        for(int u:path)col[u]=2;
    }
    vector<pair<int,int>> st;
    auto dfs=[&](int root){
        add(root); ans=max(ans,distinct);
        st.push_back({root,head[root]});
        while(!st.empty()){
            int v=st.back().first; int &i=st.back().second;
            if(i<head[v+1]){
                int w=ch[i++];
                if(onCyc[w])continue;
                add(w); ans=max(ans,distinct);
                st.push_back({w,head[w]});
            } else { rem(v); st.pop_back(); }
        }
    };
    for(int r=0;r<R;r++)for(int c=0;c<C;c++){int v=r*C+c; if(river(r,c)&&nxt[v]<0)dfs(v);}
    for(auto&cyc:cycles){
        for(int v:cyc)add(v);
        ans=max(ans,distinct);
        for(int v:cyc) for(int i=head[v];i<head[v+1];i++){int w=ch[i]; if(!onCyc[w])dfs(w);}
        for(int v:cyc)rem(v);
    }
    printf("%d\n",ans);
}
