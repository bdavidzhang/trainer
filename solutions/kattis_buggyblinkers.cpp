#include <bits/stdc++.h>
using namespace std;
int n,k;
int adj[5001][4], arrp[5001][4];
int main(){
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++)for(int d=0;d<4;d++)scanf("%d",&adj[i][d]);
    if(n==1){puts("0");return 0;}
    // arrp[i][d]: port of adj[i][d] that leads back to i
    for(int i=1;i<=n;i++)for(int d=0;d<4;d++){
        int j=adj[i][d]; arrp[i][d]=-1;
        if(!j)continue;
        for(int e=0;e<4;e++) if(adj[j][e]==i) arrp[i][d]=e;
    }
    // state: node, arrival port, blinker(0 off,1 left,2 right), used
    int K=k+1;
    auto id=[&](int v,int p,int b,int u){return ((v*4+p)*3+b)*K+u;};
    vector<int> dist((size_t)(n+1)*12*K,-1);
    vector<int> q; q.reserve(dist.size());
    auto push=[&](int v,int p,int b,int u,int d){
        int s=id(v,p,b,u); if(dist[s]<0){dist[s]=d;q.push_back(s);}
    };
    for(int d=0;d<4;d++){
        int j=adj[1][d]; if(!j||arrp[1][d]<0)continue;
        push(j,arrp[1][d],0,0,1);
    }
    for(size_t h=0;h<q.size();h++){
        int s=q[h]; int u=s%K; int t=s/K; int b=t%3; t/=3; int p=t%4; int v=t/4;
        int d=dist[s];
        if(v==n){printf("%d\n",d);return 0;}
        int hd=(p+2)%4;
        // straight
        {
            int o=hd; int j=adj[v][o];
            if(j&&arrp[v][o]>=0) push(j,arrp[v][o],0,u,d+1);
        }
        for(int turn=1;turn<=2;turn++){
            int o=turn==1?(hd+3)%4:(hd+1)%4;
            int j=adj[v][o]; if(!j||arrp[v][o]<0)continue;
            int nu=u+(b==turn?0:1); if(nu>k)continue;
            push(j,arrp[v][o],turn,nu,d+1);
        }
    }
    puts("impossible");
}
