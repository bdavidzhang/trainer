#include <bits/stdc++.h>
using namespace std;
// Special components must be wholly on or wholly off the cycle, so only path
// components are usable (a cycle component is itself an answer). Contract each
// path to a matched pair of ends, split each free vertex into a matched pair,
// and look for an alternating cycle through a path's matching edge = an
// augmenting path between its two ends (Edmonds blossom).
int n,m,k;
vector<int> sadj[155];
bool adjN[155][155];
int typ[155]; // 0 free,1 end,2 internal,3 banned
int objOf[155];
vector<vector<int>> objs; // path vertex order
// split graph
int V;
vector<int> g[310];
int mate[310], mt[310], par[310], base_[310], orig[310];
bool usedv[310], blossom[310];
int lca(int a,int b){
    static bool u[310]; memset(u,0,sizeof u);
    for(;;){ a=base_[a]; u[a]=true; if(mt[a]==-1) break; a=par[mt[a]]; }
    for(;;){ b=base_[b]; if(u[b]) return b; b=par[mt[b]]; }
}
void mark_path(int v,int b,int ch){
    while(base_[v]!=b){
        blossom[base_[v]]=blossom[base_[mt[v]]]=true;
        par[v]=ch; ch=mt[v]; v=par[mt[v]];
    }
}
int find_path(int root){
    memset(usedv,0,sizeof usedv); memset(par,-1,sizeof par);
    for(int i=0;i<V;i++) base_[i]=i;
    vector<int> q; q.push_back(root); usedv[root]=true;
    for(size_t h=0;h<q.size();h++){
        int v=q[h];
        for(int to:g[v]){
            if(base_[v]==base_[to]||mt[v]==to) continue;
            if(to==root||(mt[to]!=-1&&par[mt[to]]!=-1)){
                int cb=lca(v,to);
                memset(blossom,0,sizeof blossom);
                mark_path(v,cb,to); mark_path(to,cb,v);
                for(int i=0;i<V;i++) if(blossom[base_[i]]){
                    base_[i]=cb;
                    if(!usedv[i]){usedv[i]=true;q.push_back(i);}
                }
            } else if(par[to]==-1){
                par[to]=v;
                if(mt[to]==-1) return to;
                to=mt[to]; usedv[to]=true; q.push_back(to);
            }
        }
    }
    return -1;
}
void output(const vector<int>&c){
    printf("%d\n",(int)c.size());
    for(int v:c) printf("%d\n",v);
}
int fpar[155], fstate[155];
vector<int> fcyc;
bool fdfs(int v,int p){
    fstate[v]=1; fpar[v]=p;
    for(int w=1;w<=n;w++) if(adjN[v][w]&&typ[w]==0&&w!=p){
        if(fstate[w]==1){ // back edge
            int x=v; fcyc.push_back(x);
            while(x!=w){x=fpar[x];fcyc.push_back(x);}
            return true;
        }
        if(fstate[w]==0 && fdfs(w,v)) return true;
    }
    fstate[v]=2; return false;
}
int main(){
    scanf("%d %d %d",&n,&m,&k);
    for(int i=0;i<m;i++){
        int a,b;scanf("%d %d",&a,&b);
        if(i<k){sadj[a].push_back(b);sadj[b].push_back(a);}
        else adjN[a][b]=adjN[b][a]=true;
    }
    vector<int> comp(n+1,-1);
    for(int v=1;v<=n;v++){
        if(comp[v]!=-1) continue;
        if(sadj[v].empty()){typ[v]=0;comp[v]=v;continue;}
        vector<int> vs; vs.push_back(v); comp[v]=v;
        for(size_t h=0;h<vs.size();h++) for(int w:sadj[vs[h]]) if(comp[w]==-1){comp[w]=v;vs.push_back(w);}
        int ne=0,mx=0;
        for(int x:vs){ne+=sadj[x].size();mx=max(mx,(int)sadj[x].size());}
        ne/=2;
        if(mx<=2 && ne==(int)vs.size()){
            vector<int> c; int prev=-1,cur=v;
            do{ c.push_back(cur); int nx=sadj[cur][0]==prev?sadj[cur][1]:sadj[cur][0]; prev=cur;cur=nx; }while(cur!=v);
            output(c); return 0;
        }
        if(mx<=2 && ne==(int)vs.size()-1){
            int st=-1; for(int x:vs) if(sadj[x].size()==1){st=x;break;}
            vector<int> c; int prev=-1,cur=st;
            while(true){
                c.push_back(cur);
                int nx=-1; for(int w:sadj[cur]) if(w!=prev) nx=w;
                if(nx==-1) break; prev=cur;cur=nx;
            }
            for(int x:c){typ[x]=2;objOf[x]=objs.size();}
            typ[c.front()]=typ[c.back()]=1;
            objs.push_back(c);
        } else for(int x:vs) typ[x]=3;
    }
    // cycle among free vertices only
    for(int v=1;v<=n;v++) if(typ[v]==0&&fstate[v]==0){
        if(fdfs(v,-1)){output(fcyc);return 0;}
    }
    // split graph
    vector<array<int,2>> ids(n+1,array<int,2>{-1,-1});
    V=0;
    for(int v=1;v<=n;v++){
        if(typ[v]==0){ids[v]={V,V+1};orig[V]=orig[V+1]=v;mate[V]=V+1;mate[V+1]=V;V+=2;}
        else if(typ[v]==1){ids[v]={V,-1};orig[V]=v;V++;}
    }
    for(auto&c:objs){int a=ids[c.front()][0],b=ids[c.back()][0];mate[a]=b;mate[b]=a;}
    for(int x=1;x<=n;x++) for(int y=x+1;y<=n;y++) if(adjN[x][y]&&typ[x]<=1&&typ[y]<=1){
        for(int i=0;i<2;i++) if(ids[x][i]>=0) for(int j=0;j<2;j++) if(ids[y][j]>=0){
            g[ids[x][i]].push_back(ids[y][j]); g[ids[y][j]].push_back(ids[x][i]);
        }
    }
    for(auto&c:objs){
        int a=ids[c.front()][0],b=ids[c.back()][0];
        for(int i=0;i<V;i++) mt[i]=mate[i];
        mt[a]=mt[b]=-1;
        int e=find_path(a);
        if(e==-1) continue;
        vector<int> seq; int v=e;
        while(v!=-1){int pv=par[v];int ppv=mt[pv];seq.push_back(v);seq.push_back(pv);v=ppv;}
        // seq[0]=b ... seq.back()=a
        vector<int> cyc; cyc.push_back(orig[seq[0]]);
        for(size_t i=1;i+1<seq.size();i+=2){
            int x=orig[seq[i]],y=orig[seq[i+1]];
            if(x==y) cyc.push_back(x);
            else{
                vector<int> pth=objs[objOf[x]];
                if(pth.front()!=x) reverse(pth.begin(),pth.end());
                for(int z:pth) cyc.push_back(z);
            }
        }
        cyc.push_back(orig[seq.back()]);
        // interior from a back to b
        for(size_t i=1;i+1<c.size();i++) cyc.push_back(c[i]);
        output(cyc); return 0;
    }
    puts("-1");
}
