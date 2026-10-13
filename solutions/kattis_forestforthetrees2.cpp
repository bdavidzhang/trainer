#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int nt,ns,rm; scanf("%d %d %d",&nt,&ns,&rm);
    vector<int> tx(nt),ty(nt); 
    unordered_set<ll> S; S.reserve(nt*4);
    auto key=[](ll x,ll y){return (x+1000000)*4000003LL+(y+1000000);};
    for(int i=0;i<nt;i++){scanf("%d %d",&tx[i],&ty[i]);S.insert(key(tx[i],ty[i]));}
    vector<int> sx(ns),sy(ns); for(int i=0;i<ns;i++)scanf("%d %d",&sx[i],&sy[i]);
    int found=0; ll ax=0,ay=0;
    set<array<ll,3>> seen;
    for(int o=0;o<4&&found<2;o++){
        vector<int> dx(ns),dy(ns);
        for(int i=0;i<ns;i++){
            int a=sx[i],b=sy[i];
            if(o==0){dx[i]=a;dy[i]=b;} else if(o==1){dx[i]=b;dy[i]=-a;} else if(o==2){dx[i]=-a;dy[i]=-b;} else {dx[i]=-b;dy[i]=a;}
        }
        for(int t=0;t<nt&&found<2;t++){
            ll rx=tx[t]-dx[0], ry=ty[t]-dy[0];
            if(S.count(key(rx,ry)))continue;
            bool ok=true;
            for(int i=1;i<ns&&ok;i++) if(!S.count(key(rx+dx[i],ry+dy[i])))ok=false;
            if(!ok)continue;
            int c=0;
            for(int i=0;i<nt;i++) if(llabs(tx[i]-rx)+llabs(ty[i]-ry)<=rm){ if(++c>ns)break; }
            if(c!=ns)continue;
            found++; ax=rx; ay=ry;
        }
    }
    if(found==0)puts("Impossible"); else if(found>1)puts("Ambiguous"); else printf("%lld %lld\n",ax,ay);
}
