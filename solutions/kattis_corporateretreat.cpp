#include <bits/stdc++.h>
using namespace std;
int n,K,m;
vector<int> adj[1005];
int excol[8];
int col2[1005][2];
vector<int> g[2005];
int idx_[2005],low_[2005],comp[2005],cnt,nc; bool onst[2005]; vector<int> st;
void tarjan(int u){
    idx_[u]=low_[u]=++cnt; st.push_back(u); onst[u]=true;
    for(int v:g[u]){ if(!idx_[v]){tarjan(v);low_[u]=min(low_[u],low_[v]);} else if(onst[v]) low_[u]=min(low_[u],idx_[v]); }
    if(low_[u]==idx_[u]){ while(true){int v=st.back();st.pop_back();onst[v]=false;comp[v]=nc; if(v==u)break;} nc++; }
}
vector<pair<int,int>> exex, nn; vector<int> exadj[1005];
bool attempt(vector<int>&res){
    for(auto&p:exex) if(excol[p.first]==excol[p.second]) return false;
    for(int v=K;v<n;v++){
        bool ban[3]={0,0,0}; for(int e:exadj[v]) ban[excol[e]]=true;
        int k=0; for(int c=0;c<3;c++) if(!ban[c]) col2[v][k++]=c;
        if(k==0) return false;
        if(k==1) col2[v][1]=col2[v][0];
    }
    for(int i=0;i<2*n;i++){g[i].clear();idx_[i]=0;}
    // literal node: 2*v+p means "v takes col2[v][p]"
    for(auto&p:nn){ int u=p.first,v=p.second;
        for(int a=0;a<2;a++)for(int b=0;b<2;b++) if(col2[u][a]==col2[v][b]){ g[2*u+a].push_back(2*v+(b^1)); g[2*v+b].push_back(2*u+(a^1)); } }
    cnt=0;nc=0;
    for(int i=2*K;i<2*n;i++) if(!idx_[i]) tarjan(i);
    for(int v=K;v<n;v++) if(comp[2*v]==comp[2*v+1]) return false;
    res.assign(n,0);
    for(int i=0;i<K;i++) res[i]=excol[i];
    for(int v=K;v<n;v++) res[v]=col2[v][ comp[2*v]<comp[2*v+1] ? 0 : 1 ];
    return true;
}
int main(){
    scanf("%d %d %d",&n,&K,&m);
    for(int i=0;i<m;i++){ int a,b; scanf("%d %d",&a,&b); a--;b--;
        if(b<K) exex.push_back({a,b}); else if(a<K) exadj[b].push_back(a); else nn.push_back({a,b}); }
    int tot=1; for(int i=1;i<K;i++) tot*=3;
    vector<int> res;
    for(int mask=0;mask<tot;mask++){
        int x=mask; excol[0]=0; for(int i=1;i<K;i++){excol[i]=x%3;x/=3;}
        if(attempt(res)){ puts("possible"); for(int i=0;i<n;i++) printf("%d%c",res[i]+1,i+1<n?' ':'\n'); return 0; }
    }
    puts("impossible");
}
