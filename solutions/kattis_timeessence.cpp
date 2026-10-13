#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull CAP=100000000000ULL; // 1e11 > 2*m, so result rounds to 0 when capped
ull mulcap(ull a,ull b){ __int128 r=(__int128)a*b; return r>CAP?CAP:(ull)r; }
int main(){
    int n; cin>>n;
    vector<string> name(n); vector<ull> c(n-1);
    for(int i=0;i<n;i++){
        cin>>name[i];
        if(i<n-1){ cin>>c[i]; if(c[i]>CAP)c[i]=CAP; }
    }
    ull m; cin>>m;
    ull P1=1,P2=1;
    for(int i=0;i<n-1;i++)P1=mulcap(P1,c[i]);
    for(int i=1;i<n-1;i++)P2=mulcap(P2,c[i]);
    auto rnd=[&](ull P){ return (2*m+P)/(2*P); };
    cout<<rnd(P1)<<" "<<name[0]<<"\n";
    ull t=rnd(P2);
    cout<<t/c[0]<<" "<<name[0]<<" "<<t%c[0]<<" "<<name[1]<<"\n";
}
