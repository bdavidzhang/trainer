#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1e9+7;
vector<int> p, stamp; int cur=0;
ll solve(int l,int len){
    if(len==1) return 1;
    int h=len/2;
    ++cur;
    for(int i=l;i<l+h;i++) stamp[p[i]]=cur;
    bool overlap=false;
    for(int i=l+h;i<l+len;i++) if(stamp[p[i]]==cur){overlap=true;break;}
    if(!overlap){
        ll a=solve(l,h); if(!a) return 0;
        return a*solve(l+h,h)%MOD;
    }
    for(int i=0;i<h;i++) if(p[l+i]!=p[l+h+i]) return 0;
    return 2*solve(l,h)%MOD;
}
int main(){
    int m,n; scanf("%d %d",&m,&n);
    int N=1<<m; p.resize(N); stamp.assign(n+1,0);
    for(auto&x:p) scanf("%d",&x);
    printf("%lld\n",solve(0,N));
}
