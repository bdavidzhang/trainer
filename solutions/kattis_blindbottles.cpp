#include <bits/stdc++.h>
using namespace std;
int n;
int ask(const vector<int>&g){
    for(int i=0;i<n;i++)printf("%d%c",g[i],i+1<n?' ':'\n');
    fflush(stdout);
    int k; if(scanf("%d",&k)!=1)exit(0);
    if(k==n)exit(0);
    return k;
}
int main(){
    scanf("%d",&n);
    mt19937 rng(712367);
    vector<int> b(n); iota(b.begin(),b.end(),1);
    // baseline with zero correct positions
    while(true){ shuffle(b.begin(),b.end(),rng); if(ask(b)==0)break; }
    // sigma(i)=j means the true value at position i is b[j]. Swapping i,j in the baseline
    // returns [sigma(i)=j]+[sigma(j)=i]: the undirected edges of sigma's cycle structure.
    vector<vector<int>> adj(n);
    vector<int> sig(n,-1);
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){
        if((int)adj[i].size()==2||(int)adj[j].size()==2||sig[i]>=0||sig[j]>=0)continue;
        vector<int> g=b; swap(g[i],g[j]);
        int k=ask(g);
        if(k==2){sig[i]=j;sig[j]=i;}
        else if(k==1){adj[i].push_back(j);adj[j].push_back(i);}
    }
    vector<int> cur=b; // resolved positions hold true values, others baseline (score 0)
    int resolved=0;
    for(int i=0;i<n;i++)if(sig[i]>=0){cur[i]=b[sig[i]];resolved++;}
    vector<char> done(n,0);
    for(int i=0;i<n;i++){
        if(sig[i]>=0||done[i])continue;
        // walk the cycle
        vector<int> cyc; int prev=-1,x=i;
        while(true){
            cyc.push_back(x);done[x]=1;
            int nx=(adj[x][0]!=prev)?adj[x][0]:adj[x][1];
            prev=x;x=nx;
            if(x==i)break;
        }
        int L=cyc.size();
        vector<int> g=cur;
        for(int t=0;t<L;t++)g[cyc[t]]=b[cyc[(t+1)%L]];
        int k=ask(g);
        if(k==resolved+L){ for(int t=0;t<L;t++){sig[cyc[t]]=cyc[(t+1)%L];} }
        else { for(int t=0;t<L;t++){sig[cyc[t]]=cyc[(t+L-1)%L];} }
        for(int t=0;t<L;t++)cur[cyc[t]]=b[sig[cyc[t]]];
        resolved+=L;
    }
    ask(cur);
    return 0;
}
