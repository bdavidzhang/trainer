#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; scanf("%d",&n);
    vector<vector<int>> all(n);
    for(int i=0;i<n;i++){
        int m; scanf("%d",&m);
        vector<pair<int,int>> p(m);
        for(auto&q:p)scanf("%d %d",&q.first,&q.second);
        sort(p.begin(),p.end());
        p.erase(unique(p.begin(),p.end()),p.end());
        int bx=p[0].first,by=p[0].second; // lexicographically smallest dot as anchor
        vector<int>&v=all[i]; v.reserve(p.size());
        for(auto&q:p) v.push_back((q.first-bx)*4001+(q.second-by+2000));
    }
    sort(all.begin(),all.end());
    all.erase(unique(all.begin(),all.end()),all.end());
    printf("%d\n",(int)all.size());
}
