#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<int> q(n+1);
    for(int i=1;i<=n;i++){
        char buf[64]; scanf("%63s",buf);
        int v=0; for(char*p=buf;*p;p++) if(isdigit((unsigned char)*p)) v=v*10+(*p-'0');
        q[i]=1000-v; // survive prob in thousandths
    }
    vector<vector<int>> adj(n+1);
    for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);adj[a].push_back(b);}
    // iterative Tarjan
    vector<int> idx(n+1,-1),low(n+1,0),comp(n+1,-1),it(n+1,0),st,cs;
    vector<char> on(n+1,0);
    int timer=0,nc=0;
    for(int s=1;s<=n;s++){
        if(idx[s]>=0)continue;
        cs.push_back(s); idx[s]=low[s]=timer++; st.push_back(s); on[s]=1;
        while(!cs.empty()){
            int v=cs.back();
            if(it[v]<(int)adj[v].size()){
                int w=adj[v][it[v]++];
                if(idx[w]<0){idx[w]=low[w]=timer++;st.push_back(w);on[w]=1;cs.push_back(w);}
                else if(on[w]) low[v]=min(low[v],idx[w]);
            } else {
                if(low[v]==idx[v]){
                    while(true){int w=st.back();st.pop_back();on[w]=0;comp[w]=nc;if(w==v)break;}
                    nc++;
                }
                cs.pop_back();
                if(!cs.empty()) low[cs.back()]=min(low[cs.back()],low[v]);
            }
        }
    }
    vector<char> sink(nc,1),zero(nc,0);
    vector<double> lg(nc,0.0);
    for(int v=1;v<=n;v++){
        for(int w:adj[v]) if(comp[w]!=comp[v]) sink[comp[v]]=0;
        if(q[v]==0) zero[comp[v]]=1; else lg[comp[v]]+=log10((double)q[v])-3.0;
    }
    bool found=false; double best=0;
    for(int c=0;c<nc;c++) if(sink[c]&&!zero[c]){ if(!found||lg[c]>best){best=lg[c];found=true;} }
    if(!found||best<-250){puts("0");return 0;}
    double e=floor(best); double mant=pow(10.0,best-e);
    if(mant>=10){mant/=10;e+=1;}
    printf("%.10fe%d\n",mant,(int)e);
}
