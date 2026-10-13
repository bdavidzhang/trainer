#include <bits/stdc++.h>
using namespace std;
int main(){
    int N;char tc;cin>>N>>tc;
    map<string,int> idx;
    for(int i=0;i<N;i++){string w;cin>>w;idx[w]=i;}
    int own[2]={0,0},ass=0; // team 0=R,1=B
    vector<int> type(N);
    for(int i=0;i<N;i++){string c;cin>>c;if(c=="R")own[0]|=1<<i;else if(c=="B")own[1]|=1<<i;else if(c=="A")ass|=1<<i;}
    int M;cin>>M;vector<int> hint(M);
    for(int i=0;i<M;i++){int h;cin>>h;while(h--){string w;cin>>w;hint[i]|=1<<idx[w];}}
    sort(hint.begin(),hint.end());hint.erase(unique(hint.begin(),hint.end()),hint.end());M=hint.size();
    int FULL=1<<N;
    // g[t][h][mask*(sz+1)+k]
    vector<int> sz(M);
    vector<vector<double>> g[2];
    for(int t=0;t<2;t++){g[t].resize(M);for(int h=0;h<M;h++){sz[h]=__builtin_popcount(hint[h]);g[t][h].assign((size_t)FULL*(sz[h]+1),0.0);}}
    vector<double> W[2];W[0].assign(FULL,0);W[1].assign(FULL,0);
    for(int mask=FULL-1;mask>=0;mask--){
        if(mask&ass)continue;
        if((mask&own[0])==own[0]||(mask&own[1])==own[1])continue;
        for(int t=0;t<2;t++){
            double best=0;
            for(int h=0;h<M;h++){
                int S=hint[h]&~mask; if(!S)continue;
                int c=__builtin_popcount(S);
                // non-own part
                double base=0; 
                for(int x=S&~own[t];x;x&=x-1){
                    int w=x&-x,nm=mask|w;
                    if(w&ass)continue;
                    if((w&own[1-t])&&(nm&own[1-t])==own[1-t])continue;
                    base+=1-W[1-t][nm];
                }
                int ownS=S&own[t];
                double*G=&g[t][h][(size_t)mask*(sz[h]+1)];
                for(int k=1;k<=c;k++){
                    double v=base;
                    for(int x=ownS;x;x&=x-1){
                        int w=x&-x,nm=mask|w;
                        if((nm&own[t])==own[t])v+=1;
                        else if(k==1)v+=1-W[1-t][nm];
                        else v+=g[t][h][(size_t)nm*(sz[h]+1)+(k-1)];
                    }
                    G[k]=v/c; if(G[k]>best)best=G[k];
                }
                // k beyond c for callers: callers use k-1 <= c' always since c' = c_parent-1 >= k-1
            }
            W[t][mask]=best;
        }
    }
    printf("%.6f\n",W[tc=='R'?0:1][0]);
}
