#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    const int M=1300005;
    vector<int> x(n+1); vector<char> occ(M,0);
    for(int i=1;i<=n;i++){ scanf("%d",&x[i]); occ[x[i]]=1; }
    set<int> emp;
    for(int i=1;i<M;i++) if(!occ[i]) emp.insert(emp.end(),i);
    int q; scanf("%d",&q);
    while(q--){
        int i; scanf("%d",&i);
        auto it=emp.upper_bound(x[i]);
        int p=*it; emp.erase(it); emp.insert(x[i]); x[i]=p;
        printf("%d\n",p);
    }
}
