#include <bits/stdc++.h>
using namespace std;
// 2-SAT. Alan can score at most 2. Either he scores 2 and every friend scores <=1
// (at-most-one over 7 literals = 21 clauses), or he scores >=1 and all friends score 0.
int V; // number of variables
vector<int> off(8);
int n; vector<array<int,7>> fr; int a6,a7;
static int lit(int day,int b){ // node index: 2*var + (neg?1:0)
    int v=off[day]+abs(b)-1; return 2*v+(b<0?1:0);
}
struct TwoSat{
    int N; vector<int> head,nxt,to;
    TwoSat(int n):N(n),head(n,-1){}
    void edge(int a,int b){to.push_back(b);nxt.push_back(head[a]);head[a]=(int)to.size()-1;}
    void clause(int a,int b){edge(a^1,b);edge(b^1,a);} // a or b
    void force(int a){edge(a^1,a);}
    bool solve(){
        vector<int> idx(N,-1),low(N,0),comp(N,-1),st,it(N);
        vector<int> cs; int t=0,c=0;
        for(int s=0;s<N;s++) if(idx[s]<0){
            cs.push_back(s); idx[s]=low[s]=t++; st.push_back(s); it[s]=head[s];
            while(!cs.empty()){
                int u=cs.back();
                if(it[u]!=-1){
                    int v=to[it[u]]; it[u]=nxt[it[u]];
                    if(idx[v]<0){idx[v]=low[v]=t++;st.push_back(v);it[v]=head[v];cs.push_back(v);}
                    else if(comp[v]<0) low[u]=min(low[u],idx[v]);
                } else {
                    if(low[u]==idx[u]){
                        while(true){int w=st.back();st.pop_back();comp[w]=c;if(w==u)break;}
                        c++;
                    }
                    cs.pop_back();
                    if(!cs.empty()) low[cs.back()]=min(low[cs.back()],low[u]);
                }
            }
        }
        for(int i=0;i<N;i+=2) if(comp[i]==comp[i+1]) return false;
        return true;
    }
};
int main(){
    scanf("%d",&n);
    int d[7]; V=0;
    for(int i=0;i<7;i++){scanf("%d",&d[i]);off[i]=V;V+=d[i];}
    fr.resize(n);
    for(auto&f:fr) for(int i=0;i<7;i++) scanf("%d",&f[i]);
    scanf("%d %d",&a6,&a7);
    int A6=lit(5,a6),A7=lit(6,a7);
    // case 1: both true, friends at most one
    {
        TwoSat ts(2*V);
        ts.force(A6); ts.force(A7);
        for(auto&f:fr){
            int l[7]; for(int i=0;i<7;i++) l[i]=lit(i,f[i]);
            for(int i=0;i<7;i++) for(int j=i+1;j<7;j++) ts.clause(l[i]^1,l[j]^1);
        }
        if(ts.solve()){puts("possible");return 0;}
    }
    // case 2: all friend literals false, one of Alan's true
    {
        vector<signed char> val(V,-1); bool ok=true;
        for(auto&f:fr){
            for(int i=0;i<7&&ok;i++){
                int l=lit(i,f[i]); int v=l>>1; signed char want=(l&1)?1:0; // literal false
                if(val[v]>=0&&val[v]!=want) ok=false;
                val[v]=want;
            }
            if(!ok)break;
        }
        if(ok){
            for(int A:{A6,A7}){
                int v=A>>1; signed char want=(A&1)?0:1;
                if(val[v]<0||val[v]==want){puts("possible");return 0;}
            }
        }
    }
    puts("impossible");
}
