#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n,m; ll L; scanf("%d %d %lld",&n,&m,&L);
    vector<array<ll,11>> s(n);
    for(auto&a:s) for(int x=0;x<11;x++){ scanf("%lld",&a[x]); a[x]*=(x+1); }
    vector<int> alive(n); iota(alive.begin(),alive.end(),0);
    array<ll,11> cnt; cnt.fill(0);
    for(int j=0;j<m;j++){
        int x; scanf("%d",&x);
        if(x<12){ cnt[x-1]++; continue; }
        int catchR=-1,catchL=-1;
        vector<int> right,left;
        for(int i:alive){
            ll p=0;
            for(int k=0;k<11;k++) if(cnt[k]){ p+=cnt[k]*s[i][k]; if(p>=L){p=L;break;} }
            if(2*p>=L){ right.push_back(i); if(catchR<0 && L<4*(L-p)) catchR=i; }
            else { left.push_back(i); if(catchL<0 && L<4*p) catchL=i; }
        }
        int c = catchR>=0?catchR:catchL;
        bool any=false; string out;
        for(int i:right) if(i!=c){ out+=to_string(i+1); out+=' '; any=true; }
        if(!any) puts("None"); else { out.pop_back(); puts(out.c_str()); }
        if(c<0) puts("None"); else printf("%d\n",c+1);
        alive.clear();
        for(int i:left) if(i!=c) alive.push_back(i);
        cnt.fill(0);
    }
}
