#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
unordered_map<ll,ll> cache_;
ll ask(int x,int y){
    ll key=(ll)x*20000+y;
    auto it=cache_.find(key);
    if(it!=cache_.end()) return it->second;
    printf("? %d %d\n",x,y);fflush(stdout);
    ll v; if(scanf("%lld",&v)!=1) exit(0);
    cache_[key]=v;
    return v;
}
int main(){
    if(scanf("%d",&n)!=1) return 0;
    int r1=1,r2=n,c1=1,c2=n;
    ll best=-1; int br=0,bc=0; // best known point, always inside the current region
    while(r1<=r2&&c1<=c2){
        bool rows=(r2-r1)>=(c2-c1);
        ll M=-1; int mr=0,mc=0;
        if(rows){
            int mid=(r1+r2)/2;
            for(int c=c1;c<=c2;c++){ll v=ask(mid,c);if(v>M){M=v;mr=mid;mc=c;}}
            ll cand=max(best,M); int cr=(best>M)?br:mr, cc=(best>M)?bc:mc;
            if(mid-1>=r1){ll v=ask(mid-1,mc);if(v>cand){cand=v;cr=mid-1;cc=mc;}}
            if(mid+1<=r2){ll v=ask(mid+1,mc);if(v>cand){cand=v;cr=mid+1;cc=mc;}}
            best=cand;br=cr;bc=cc;
            if(cr==mid) break; // max of line beats both neighbours and everything known: local max
            if(cr<mid) r2=mid-1; else r1=mid+1;
        }else{
            int mid=(c1+c2)/2;
            for(int r=r1;r<=r2;r++){ll v=ask(r,mid);if(v>M){M=v;mr=r;mc=mid;}}
            ll cand=max(best,M); int cr=(best>M)?br:mr, cc=(best>M)?bc:mc;
            if(mid-1>=c1){ll v=ask(mr,mid-1);if(v>cand){cand=v;cr=mr;cc=mid-1;}}
            if(mid+1<=c2){ll v=ask(mr,mid+1);if(v>cand){cand=v;cr=mr;cc=mid+1;}}
            best=cand;br=cr;bc=cc;
            if(cc==mid) break;
            if(cc<mid) c2=mid-1; else c1=mid+1;
        }
    }
    printf("! %lld\n",best);fflush(stdout);
}
