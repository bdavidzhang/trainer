#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
// Choose a connected set H (walkable) containing U and D; every other empty cell is a shop.
// Windows = edges between a '.' cell of H and a '.' cell outside H. Connectivity-profile DP.
int R,C;
vector<string> g;
int w;
static ull enc(const int*lab,int closed){
    int mp[16]; memset(mp,-1,sizeof mp); mp[0]=0; int nx=1; ull s=0;
    for(int i=0;i<w;i++){ int l=lab[i]; if(mp[l]<0) mp[l]=nx++; s|=(ull)mp[l]<<(4*i);} 
    return s|((ull)closed<<60);
}
int main(){
    cin>>R>>C; g.resize(R); for(auto&s:g)cin>>s;
    if(C>R){ vector<string> t(C,string(R,'.')); for(int i=0;i<R;i++)for(int j=0;j<C;j++)t[j][i]=g[i][j]; g=t; swap(R,C);} 
    w=C;
    unordered_map<ull,int> cur,nxt;
    { int lab[16]={0}; cur[enc(lab,0)]=0; }
    for(int i=0;i<R;i++)for(int j=0;j<C;j++){
        nxt.clear();
        char ch=g[i][j];
        bool esc=(ch=='U'||ch=='D');
        for(auto&kv:cur){
            int lab[16]; for(int t=0;t<w;t++) lab[t]=(kv.first>>(4*t))&15;
            int closed=(kv.first>>60)&1; int val=kv.second;
            int up=(i>0)?lab[j]:0, left=(j>0)?lab[j-1]:0;
            bool upIn=up!=0, leftIn=left!=0;
            char upc=(i>0)?g[i-1][j]:'#', lc=(j>0)?g[i][j-1]:'#';
            // option: not in H
            if(!esc){
                bool ok=true; int nc=closed;
                if(up!=0){
                    bool other=false,any=false;
                    for(int t=0;t<w;t++) if(t!=j){ if(lab[t]==up) other=true; else if(lab[t]!=0) any=true; }
                    if(!other){ if(any) ok=false; else nc=1; }
                }
                if(ok){
                    int gain=0;
                    if(ch=='.'){ if(upIn&&upc=='.')gain++; if(leftIn&&lc=='.')gain++; }
                    int nl[16]; memcpy(nl,lab,sizeof nl); nl[j]=0;
                    ull e=enc(nl,nc); auto it=nxt.find(e);
                    if(it==nxt.end()) nxt[e]=val+gain; else if(it->second<val+gain) it->second=val+gain;
                }
            }
            // option: in H
            if(ch!='#' && !closed){
                int gain=0;
                if(ch=='.'){ if(i>0&&!upIn&&upc=='.')gain++; if(j>0&&!leftIn&&lc=='.')gain++; }
                int nl[16]; memcpy(nl,lab,sizeof nl);
                if(up==0&&left==0) nl[j]=15;
                else if(up!=0&&left!=0){ for(int t=0;t<w;t++) if(nl[t]==left) nl[t]=up; nl[j]=up; }
                else nl[j]=up?up:left;
                ull e=enc(nl,0); auto it=nxt.find(e);
                if(it==nxt.end()) nxt[e]=val+gain; else if(it->second<val+gain) it->second=val+gain;
            }
        }
        swap(cur,nxt);
    }
    int best=0;
    for(auto&kv:cur){
        int closed=(kv.first>>60)&1; int mx=0;
        for(int t=0;t<w;t++) mx=max(mx,(int)((kv.first>>(4*t))&15));
        if(closed||mx==1) best=max(best,kv.second);
    }
    printf("%d\n",best);
}
