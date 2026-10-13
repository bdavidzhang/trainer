#include <bits/stdc++.h>
using namespace std;
static int gc(){static char b[1<<16];static size_t p=0,l=0;if(p==l){l=fread(b,1,sizeof b,stdin);p=0;if(!l)return -1;}return b[p++];}
static int rd(){int c=gc();while(c!='-'&&(c<'0'||c>'9'))c=gc();int x=0;while(c>='0'&&c<='9'){x=x*10+c-'0';c=gc();}return x;}
vector<int> p;
int fnd(int x){while(p[x]!=x){p[x]=p[p[x]];x=p[x];}return x;}
int main(){
    int n=rd(),m=rd();
    vector<int> A(m),B(m),W(m),ord(m);
    for(int i=0;i<m;i++){A[i]=rd();B[i]=rd();W[i]=rd();ord[i]=i;}
    // counting sort by weight
    {vector<int> c(1000002,0);for(int i=0;i<m;i++)c[W[i]+1]++;for(int i=1;i<1000002;i++)c[i]+=c[i-1];for(int i=0;i<m;i++)ord[c[W[i]]++]=i;}
    p.resize(n+1);iota(p.begin(),p.end(),0);
    vector<char> in(m,0);long long mst=0;
    vector<vector<pair<int,int>>> g(n+1);
    for(int id:ord){int a=fnd(A[id]),b=fnd(B[id]);if(a!=b){p[a]=b;in[id]=1;mst+=W[id];g[A[id]].push_back({B[id],W[id]});g[B[id]].push_back({A[id],W[id]});}}
    vector<int> par(n+1,0),dep(n+1,0),pw(n+1,0);
    {vector<int> st;st.push_back(1);par[1]=0;
     while(!st.empty()){int u=st.back();st.pop_back();for(auto&e:g[u])if(e.first!=par[u]){par[e.first]=u;dep[e.first]=dep[u]+1;pw[e.first]=e.second;st.push_back(e.first);}}}
    iota(p.begin(),p.end(),0); // p[v]: topmost vertex whose parent edge is uncovered, in v's ancestor chain
    long long best=0;
    for(int id:ord){ if(in[id])continue;
        int a=fnd(A[id]),b=fnd(B[id]);
        while(a!=b){
            if(dep[a]<dep[b])swap(a,b);
            best=max(best,(long long)W[id]-pw[a]);
            p[a]=par[a];a=fnd(a);
        }
    }
    printf("%lld\n",mst+best);
}
