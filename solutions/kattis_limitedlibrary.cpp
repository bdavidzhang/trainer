#include <bits/stdc++.h>
using namespace std;
int n,m,x,y; vector<long long> a,b;
// a ascending, b descending. k shortest shelves get art.
bool ok(int k){
    int bi=0;
    for(int i=n-1;i>=0 && bi<m;i--){
        int cap = (i<k)? y : x;
        if(b[bi]>a[i]) return false;
        bi=min(m,bi+cap);
    }
    return bi>=m;
}
int main(){
    scanf("%d %d %d %d",&n,&m,&x,&y);
    a.resize(n); b.resize(m);
    for(auto&v:a) scanf("%lld",&v);
    for(auto&v:b) scanf("%lld",&v);
    sort(a.begin(),a.end());
    sort(b.rbegin(),b.rend());
    if(!ok(0)){ puts("impossible"); return 0; }
    int lo=0,hi=n;
    while(lo<hi){ int mid=(lo+hi+1)/2; if(ok(mid)) lo=mid; else hi=mid-1; }
    printf("%d\n",lo);
}
