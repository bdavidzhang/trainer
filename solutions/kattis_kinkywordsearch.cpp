#include <bits/stdc++.h>
using namespace std;
int main(){
    int r,c; cin>>r>>c; vector<string> g(r,string(c,' '));
    for(auto&row:g)for(auto&ch:row){cin>>ch;}
    int k; string w; cin>>k>>w; int L=w.size();
    if(L==1){ bool f=false; for(auto&row:g)for(char ch:row)if(ch==w[0])f=true; puts(f&&k==0?"Yes":"No"); return 0; }
    if(k>L-2){puts("No");return 0;}
    int dr[8]={-1,-1,-1,0,0,1,1,1},dc[8]={-1,0,1,-1,1,-1,0,1};
    int K=k+1;
    // dp[cell][dir][kinks]
    auto id=[&](int cell,int d,int q){return (cell*8+d)*K+q;};
    vector<char> cur(r*c*8*K,0),nx;
    for(int i=0;i<r;i++)for(int j=0;j<c;j++)if(g[i][j]==w[0])for(int d=0;d<8;d++){
        int a=i+dr[d],b=j+dc[d]; if(a<0||b<0||a>=r||b>=c||g[a][b]!=w[1])continue;
        cur[id(a*c+b,d,0)]=1;
    }
    for(int p=2;p<L;p++){
        nx.assign(r*c*8*K,0);
        for(int i=0;i<r;i++)for(int j=0;j<c;j++)if(g[i][j]==w[p-1])for(int d=0;d<8;d++)for(int q=0;q<K;q++)if(cur[id(i*c+j,d,q)]){
            for(int e=0;e<8;e++){ int a=i+dr[e],b=j+dc[e]; if(a<0||b<0||a>=r||b>=c||g[a][b]!=w[p])continue;
                int nq=q+(e!=d); if(nq<K) nx[id(a*c+b,e,nq)]=1; }
        }
        cur.swap(nx);
    }
    bool f=false; for(int x=0;x<r*c*8;x++)if(cur[x*K+k])f=true;
    puts(f?"Yes":"No");
}
