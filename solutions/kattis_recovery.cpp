#include <bits/stdc++.h>
using namespace std;
int main(){
    string R,C; cin>>R>>C; int n=R.size(),m=C.size();
    vector<int> rs,cs;
    for(int i=0;i<n;i++) if((R[i]-'0')!=(m&1)) rs.push_back(i);
    for(int j=0;j<m;j++) if((C[j]-'0')!=(n&1)) cs.push_back(j);
    if((rs.size()+cs.size())&1){ puts("-1"); return 0; }
    while(rs.size()<cs.size()) rs.push_back(0);
    while(cs.size()<rs.size()) cs.push_back(0);
    sort(rs.begin(),rs.end()); sort(cs.begin(),cs.end());
    vector<string> g(n,string(m,'1'));
    for(size_t i=0;i<rs.size();i++) g[rs[i]][cs[i]]='0';
    for(auto&s:g) cout<<s<<"\n";
}
