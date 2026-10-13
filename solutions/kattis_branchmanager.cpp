#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<vector<int>> ch(n+1);
    for(int i=0;i<n-1;i++){int a,b;scanf("%d %d",&a,&b);ch[a].push_back(b);}
    for(auto&v:ch) sort(v.begin(),v.end());
    vector<int> tin(n+1),tout(n+1),it(n+1,0);
    int T=0; vector<int> st; st.push_back(1); tin[1]=T++;
    while(!st.empty()){
        int u=st.back();
        if(it[u]<(int)ch[u].size()){int v=ch[u][it[u]++]; tin[v]=T++; st.push_back(v);}
        else {tout[u]=T-1; st.pop_back();}
    }
    int M=0,ans=0;
    for(int i=0;i<m;i++){
        int d;scanf("%d",&d);
        if(tout[d]<M) break;
        ans++; M=max(M,tin[d]);
    }
    printf("%d\n",ans);
}
