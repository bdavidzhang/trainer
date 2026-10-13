#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m;cin>>n>>m;vector<string>g(n);for(auto&s:g)cin>>s;
    vector<int>d(n*m,-1);vector<int>q;q.reserve(n*m);
    int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){
        if(g[i][j]!='X')continue;
        bool e=false;
        for(int k=0;k<4;k++){int a=i+dx[k],b=j+dy[k];if(a<0||b<0||a>=n||b>=m||g[a][b]!='X')e=true;}
        if(e){d[i*m+j]=1;q.push_back(i*m+j);}
    }
    int ans=0;
    for(size_t h=0;h<q.size();h++){int c=q[h],i=c/m,j=c%m;ans=max(ans,d[c]);
        for(int k=0;k<4;k++){int a=i+dx[k],b=j+dy[k];if(a<0||b<0||a>=n||b>=m||g[a][b]!='X'||d[a*m+b]!=-1)continue;d[a*m+b]=d[c]+1;q.push_back(a*m+b);}}
    cout<<ans<<"\n";
}
