#include <bits/stdc++.h>
using namespace std;
// Build a bitonic permutation by placing values 1..n at the leftmost / rightmost free position.
// Track open paths (start/end) so that the number of closed cycles is maintained incrementally.
static const int LIM=2000;
int n,m; int st[105],en[105],perm[105];
vector<vector<int>> res;
void dfs(int v,int a,int r,int cyc){
    if((int)res.size()>=LIM) return;
    if(v==n){ if(cyc==m) res.push_back(vector<int>(perm+1,perm+n+1)); return; }
    // upper bound on cycles still closable: before the first right move every step can be a
    // fixed point; afterwards cycles only close once the free interval meets the placed values.
    int fut = r==0 ? n-v : min(n-v,(n-v+r+1)/2);
    if(cyc>m||cyc+fut<m) return;
    int w=v+1;
    for(int side=0;side<2;side++){
        if(v==n-1&&side==1) continue;
        int u= side==0? a+1 : n-r;
        int su=st[u], ew=en[w]; int o1=st[ew],o2=en[su]; int c=cyc;
        if(su==w) c++; else {st[ew]=su; en[su]=ew;}
        perm[u]=w;
        dfs(v+1,a+(side==0),r+(side==1),c);
        if(su!=w){st[ew]=o1; en[su]=o2;}
    }
}
void runDfs(int nn,int mm){
    n=nn;m=mm; for(int i=1;i<=n;i++) st[i]=en[i]=i;
    res.clear(); dfs(0,0,0,0);
}
int main(){
    int N,M; scanf("%d %d",&N,&M);
    int d=N-M; int t=0;
    if(N<=23||d<=9){
        runDfs(N,M);              // exhaustive (stops at 2000)
    } else if(d<=22){
        runDfs(23,23-d);          // count(23,23-d)>=2000 for d>=10; pad with fixed points
        t=N-23;
    } else {
        int mp=min(M,4), np=d+mp; t=M-mp;
        mt19937_64 rng(88172645463325252ULL);
        set<vector<int>> seen; vector<int> p(np+1); vector<char> vis(np+1);
        while((int)res.size()<LIM){
            int a=1,b=np;
            for(int v=1;v<=np;v++){ if(rng()&1) p[a++]=v; else p[b--]=v; }
            fill(vis.begin(),vis.end(),0); int c=0;
            for(int i=1;i<=np&&c<=mp;i++) if(!vis[i]){c++; for(int j=i;!vis[j];j=p[j])vis[j]=1;}
            if(c!=mp) continue;
            vector<int> q(p.begin()+1,p.end());
            if(seen.insert(q).second) res.push_back(q);
        }
    }
    printf("%d\n",(int)res.size());
    string out;
    for(auto&q:res){
        for(int i=1;i<=t;i++){ out+=to_string(i); out+=' '; }
        for(size_t i=0;i<q.size();i++){ out+=to_string(q[i]+t); out+=(i+1<q.size()?' ':'\n'); }
        if(q.empty()) out+='\n';
    }
    fputs(out.c_str(),stdout);
}
