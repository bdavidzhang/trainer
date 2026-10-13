#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<vector<int>> g(n+1);
    for(int i=0;i<m;i++){int u,v; scanf("%d %d",&u,&v); g[u].push_back(v); g[v].push_back(u);}
    vector<int> col(n+1,-1);
    int comps=0; bool odd=false;
    vector<int> st;
    for(int s=1;s<=n;s++) if(col[s]<0){
        comps++; col[s]=0; st.push_back(s);
        while(!st.empty()){
            int u=st.back(); st.pop_back();
            for(int v:g[u]){
                if(col[v]<0){col[v]=col[u]^1; st.push_back(v);}
                else if(col[v]==col[u]) odd=true;
            }
        }
    }
    printf("%d\n",comps-1+(odd?0:1));
}
