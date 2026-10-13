#include <bits/stdc++.h>
using namespace std;
int main(){
    int H,W; cin>>H>>W; vector<string> g(H); for(auto&r:g)cin>>r;
    string s; cin>>s; int n=s.size();
    int sr=0,sc=0;
    for(int i=0;i<H;i++)for(int j=0;j<W;j++)if(g[i][j]=='S'){sr=i;sc=j;}
    auto id=[&](int r,int c,int i){return (r*W+c)*(n+1)+i;};
    vector<int> d(H*W*(n+1),INT_MAX);
    deque<int> dq; d[id(sr,sc,0)]=0; dq.push_back(id(sr,sc,0));
    const int dr[4]={0,0,-1,1},dc[4]={-1,1,0,0}; const string dirs="LRUD";
    auto mv=[&](int r,int c,int k){int nr=r+dr[k],nc=c+dc[k];
        if(nr<0||nc<0||nr>=H||nc>=W||g[nr][nc]=='#')return make_pair(r,c);return make_pair(nr,nc);};
    while(!dq.empty()){
        int u=dq.front();dq.pop_front();
        int i=u%(n+1),cell=u/(n+1),r=cell/W,c=cell%W; int du=d[u];
        if(g[r][c]=='G'){printf("%d\n",du);return 0;}
        auto relax=[&](int v,int w){ if(du+w<d[v]){d[v]=du+w; if(w)dq.push_back(v); else dq.push_front(v);} };
        if(i<n){
            auto p=mv(r,c,dirs.find(s[i]));
            relax(id(p.first,p.second,i+1),0);
            relax(id(r,c,i+1),1);
        }
        for(int k=0;k<4;k++){auto p=mv(r,c,k); relax(id(p.first,p.second,i),1);}
    }
}
