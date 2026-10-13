#include <bits/stdc++.h>
using namespace std;
int n; int card[100][5][5];
int stamp[3001],cur=0;
int main(){
    scanf("%d",&n);
    vector<vector<pair<int,int>>> occ(3001);
    for(int i=0;i<n;i++)for(int r=0;r<5;r++)for(int c=0;c<5;c++){ scanf("%d",&card[i][r][c]); occ[card[i][r][c]].push_back({i,r}); }
    pair<int,int> best={n,n};
    for(int x=1;x<=3000;x++){
        auto&v=occ[x];
        for(size_t i=0;i<v.size();i++)for(size_t j=i+1;j<v.size();j++){
            pair<int,int> pr={v[i].first,v[j].first};
            if(pr.first==pr.second) continue;
            if(pr>=best) continue;
            cur++;
            for(int c=0;c<5;c++){ stamp[card[v[i].first][v[i].second][c]]=cur; stamp[card[v[j].first][v[j].second][c]]=cur; }
            stamp[x]=0;
            bool ok=true;
            for(int q=0;q<n&&ok;q++)for(int r=0;r<5;r++){
                int cnt=0; for(int c=0;c<5;c++) cnt+=stamp[card[q][r][c]]==cur;
                if(cnt==5){ ok=false; break; }
            }
            if(ok) best=pr;
        }
    }
    if(best.first==n) puts("no ties"); else printf("%d %d\n",best.first+1,best.second+1);
}
