#include <bits/stdc++.h>
using namespace std;
int N,M; vector<string> g;
vector<int> par;
int fnd(int x){while(par[x]!=x){par[x]=par[par[x]];x=par[x];}return x;}
// sweep columns in given order; out: W[j], Bk[j], T[j] for the block of columns swept so far ending at j
void sweep(bool rev, vector<int>&W, vector<int>&Bk, vector<int>&T){
    par.resize(N*M); iota(par.begin(),par.end(),0);
    int cnt[2]={0,0};
    vector<int> seen(N*M,-1);
    for(int s=0;s<M;s++){
        int j=rev?M-1-s:s, pj=rev?j+1:j-1;
        for(int i=0;i<N;i++){
            int col=g[i][j]-'0'; cnt[col]++;
            int id=i*M+j;
            if(i>0&&g[i-1][j]==g[i][j]){int a=fnd(id),b=fnd(id-M); if(a!=b){par[a]=b;cnt[col]--;}}
            if(s>0&&g[i][pj]==g[i][j]){int a=fnd(id),b=fnd(i*M+pj); if(a!=b){par[a]=b;cnt[col]--;}}
        }
        W[j]=cnt[0]; Bk[j]=cnt[1];
        int t=0;
        for(int i=0;i<N;i++) if(g[i][j]=='1'){int r=fnd(i*M+j); if(seen[r]!=j){seen[r]=j;t++;}}
        T[j]=t;
    }
}
int main(){
    cin>>N>>M; g.resize(N); for(auto&s:g)cin>>s;
    vector<int> WL(M),BL(M),TL(M),WR(M),BR(M),TR(M);
    sweep(false,WL,BL,TL); sweep(true,WR,BR,TR);
    long long bestTot=-1,bw=0,bb=0;
    for(int c=0;c<M;c++){
        long long w=0,b=1;
        if(c>0){w+=WL[c-1]; b+=BL[c-1]-TL[c-1];}
        if(c<M-1){w+=WR[c+1]; b+=BR[c+1]-TR[c+1];}
        if(w+b>bestTot||(w+b==bestTot&&w>bw)){bestTot=w+b;bw=w;bb=b;}
    }
    cout<<bw<<" "<<bb<<"\n";
}
