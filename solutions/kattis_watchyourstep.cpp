#include <bits/stdc++.h>
using namespace std;
int n;static unsigned char g[2500][2500];
int idx[2500],low[2500],timer_=0;bool onst[2500];vector<int> st;long long sumsq=0;
void dfs(int u){
    idx[u]=low[u]=++timer_;st.push_back(u);onst[u]=true;
    for(int v=0;v<n;v++)if(g[u][v]){
        if(!idx[v]){dfs(v);low[u]=min(low[u],low[v]);}
        else if(onst[v])low[u]=min(low[u],idx[v]);
    }
    if(low[u]==idx[u]){long long s=0;while(true){int v=st.back();st.pop_back();onst[v]=false;s++;if(v==u)break;}sumsq+=s*s;}
}
int main(){
    scanf("%d",&n);long long E=0;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){int c;do c=getchar();while(c!='0'&&c!='1');g[i][j]=c-'0';E+=g[i][j];}
    for(int i=0;i<n;i++)if(!idx[i])dfs(i);
    long long N=n;
    printf("%lld\n",(N*N-sumsq)/2+sumsq-N-E);
}
