#include <bits/stdc++.h>
using namespace std;
int main(){
    int m,n; cin>>m>>n; vector<string> g(m); for(auto&s:g)cin>>s;
    int cnt=0;
    for(int i=0;i<m;i++)for(int j=0;j<n;j++) if(g[i][j]=='#'){
        cnt++; vector<pair<int,int>> st{{i,j}}; g[i][j]='.';
        while(!st.empty()){auto [x,y]=st.back();st.pop_back();
            for(int dx=-1;dx<=1;dx++)for(int dy=-1;dy<=1;dy++){int a=x+dx,b=y+dy;
                if(a>=0&&a<m&&b>=0&&b<n&&g[a][b]=='#'){g[a][b]='.';st.push_back({a,b});}}}
    }
    cout<<cnt<<"\n";
}
