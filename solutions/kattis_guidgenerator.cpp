#include <bits/stdc++.h>
using namespace std;
int n; char s[2005]; int val[2005];
vector<int> g[2005];
int (*tr)[16]; int cnt=1;
int main(){
    scanf("%d %s",&n,s+1);
    for(int i=1;i<=n;i++) val[i]=isdigit(s[i])?s[i]-'0':s[i]-'a'+10;
    for(int i=0;i<n-1;i++){int u,v;scanf("%d %d",&u,&v);g[u].push_back(v);g[v].push_back(u);}
    tr=(int(*)[16])calloc((size_t)n*n+2,sizeof(int[16]));
    vector<array<int,3>> st; // node, parent, trie node
    for(int r=1;r<=n;r++){
        st.push_back({r,0,0});
        while(!st.empty()){
            auto [v,p,t]=st.back(); st.pop_back();
            int &nx=tr[t][val[v]];
            if(!nx) nx=cnt++;
            int tt=nx;
            for(int u:g[v]) if(u!=p) st.push_back({u,v,tt});
        }
    }
    printf("%d\n",cnt-1);
}
