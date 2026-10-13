#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,k; scanf("%d %d",&n,&k);
    int L=n*k; vector<int> a(L); vector<vector<int>> pos(n+1);
    for(auto&x:a) scanf("%d",&x);
    for(int i=0;i<L;i++){ int x; scanf("%d",&x); pos[x].push_back(i); }
    vector<int> tails;
    for(int i=0;i<L;i++){
        auto&p=pos[a[i]];
        for(int j=p.size()-1;j>=0;j--){
            int v=p[j];
            auto it=lower_bound(tails.begin(),tails.end(),v);
            if(it==tails.end()) tails.push_back(v); else *it=v;
        }
    }
    printf("%d\n",(int)tails.size());
}
