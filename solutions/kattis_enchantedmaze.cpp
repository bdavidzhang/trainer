#include <bits/stdc++.h>
using namespace std;
int R,C; vector<string> g;
// label index of obstacle letter or -1
static int obsLabel(char c){ if(c>='A'&&c<='D') return c-'A'; if(c>='a'&&c<='d') return c-'a'; return -1; }
static bool raised(char c,int mask){
    if(c>='A'&&c<='D') return !((mask>>(c-'A'))&1);
    if(c>='a'&&c<='d') return ((mask>>(c-'a'))&1);
    return false;
}
int main(){
    cin>>R>>C; g.resize(R); for(auto&s:g) cin>>s;
    vector<int> st;
    for(int i=0;i<R;i++)for(int j=0;j<C;j++) if(g[i][j]=='S') st.push_back(i*C+j);
    int N=R*C;
    vector<int> dist((size_t)N*N*16,-1);
    auto id=[&](int a,int b,int m){return (a*N+b)*16+m;};
    queue<int> q; dist[id(st[0],st[1],0)]=0; q.push(id(st[0],st[1],0));
    int dr[4]={-1,1,0,0},dc[4]={0,0,-1,1};
    while(!q.empty()){
        int s=q.front();q.pop();
        int m=s%16, b=(s/16)%N, a=s/16/N;
        int d0=dist[s];
        if(g[a/C][a%C]=='E'&&g[b/C][b%C]=='E'){ printf("%d\n",d0); return 0; }
        for(int d=0;d<4;d++){
            int p[2]={a,b}, np[2]; bool ok=true;
            for(int t=0;t<2&&ok;t++){
                int r=p[t]/C+dr[d], c=p[t]%C+dc[d];
                if(r<0||r>=R||c<0||c>=C){ok=false;break;}
                char ch=g[r][c];
                if(ch=='*'){ok=false;break;}
                if(ch=='#'||raised(ch,m)) np[t]=p[t]; else np[t]=r*C+c;
            }
            if(!ok) continue;
            if(np[0]==np[1]) continue;
            int nm=m;
            for(int t=0;t<2&&ok;t++){
                if(np[t]==p[t]) continue;
                char ch=g[np[t]/C][np[t]%C];
                if(ch>='1'&&ch<='4'){
                    int k=ch-'1';
                    char oc=g[np[1-t]/C][np[1-t]%C];
                    if(obsLabel(oc)==k){ok=false;break;}
                    nm^=1<<k;
                }
            }
            if(!ok) continue;
            int ns=id(np[0],np[1],nm);
            if(dist[ns]<0){dist[ns]=d0+1;q.push(ns);}
        }
    }
    printf("-1\n");
}
