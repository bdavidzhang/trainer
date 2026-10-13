#include <bits/stdc++.h>
using namespace std;
struct Clue{int num;vector<pair<int,int>> cells;};
int main(){
    int r,c;cin>>r>>c;vector<string> g(r);for(auto&s:g)cin>>s;
    vector<Clue> ac,dn;int num=0;
    for(int i=0;i<r;i++)for(int j=0;j<c;j++){
        if(g[i][j]=='#')continue;
        bool a=(j==0||g[i][j-1]=='#'),d=(i==0||g[i-1][j]=='#');
        if(!a&&!d)continue;
        num++;
        if(a){Clue q;q.num=num;for(int k=j;k<c&&g[i][k]!='#';k++)q.cells.push_back({i,k});ac.push_back(q);}
        if(d){Clue q;q.num=num;for(int k=i;k<r&&g[k][j]!='#';k++)q.cells.push_back({k,j});dn.push_back(q);}
    }
    while(true){
        long long bn=-1,bd=1;int bt=-1,bi=-1;
        for(int t=0;t<2;t++){
            auto&v=t?dn:ac;
            for(int i=0;i<(int)v.size();i++){
                int n=v[i].cells.size();long long tot=0;bool emp=false;
                for(int k=0;k<n;k++){auto[x,y]=v[i].cells[k];if(g[x][y]=='.')emp=true;else tot+=n-k;}
                if(!emp)continue;
                long long den=(long long)n*(n+1)/2;
                if(bt<0||tot*bd>bn*den){bn=tot;bd=den;bt=t;bi=i;}
            }
        }
        if(bt<0)break;
        auto&q=(bt?dn:ac)[bi];
        for(auto[x,y]:q.cells)g[x][y]='X';
        printf("%d%c\n",q.num,bt?'D':'A');
    }
}
