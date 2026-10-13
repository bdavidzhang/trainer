#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 LL;
// Li Chao (min) over x in [-1e6,1e6] for lines -2*gx*x + (gx^2+gy^2)
const int OFF=1000000, SZ=1<<21;
vector<ll> lm, lc;
static inline ll ev(ll m,ll c,int x){return m*(ll)(x-OFF)+c;}
void addl(ll a,ll b){
    int node=1,lo=0,hi=SZ-1;
    while(true){
        int mid=(lo+hi)/2;
        bool lf=ev(a,b,lo)<ev(lm[node],lc[node],lo);
        bool md=ev(a,b,mid)<ev(lm[node],lc[node],mid);
        if(md){swap(a,lm[node]);swap(b,lc[node]);}
        if(lo==hi)break;
        if(lf!=md){node=2*node;hi=mid;}else{node=2*node+1;lo=mid+1;}
    }
}
ll qry(int x){
    int node=1,lo=0,hi=SZ-1;ll r=LLONG_MAX;
    while(true){
        r=min(r,ev(lm[node],lc[node],x));
        if(lo==hi)break;
        int mid=(lo+hi)/2;
        if(x<=mid){node=2*node;hi=mid;}else{node=2*node+1;lo=mid+1;}
    }
    return r;
}
int main(){
    int n,k; scanf("%d %d",&n,&k);
    vector<ll> gx(n+1),gy(n+1); vector<char> known(n+1,0);
    lm.assign(2*SZ,0); lc.assign(2*SZ,(ll)4e18);
    for(int i=0;i<k;i++){ll x,y;int f;scanf("%lld %lld %d",&x,&y,&f);gx[f]=x;gy[f]=y;known[f]=1;addl(-2*x,x*x+y*y);}
    vector<ll> xs(n); vector<int> fs(n);
    for(int i=0;i<n;i++)scanf("%lld %d",&xs[i],&fs[i]);
    // d^2 of known readings
    vector<ll> d2(n,-1);
    for(int i=0;i<n;i++)if(known[fs[i]]){ll dx=gx[fs[i]]-xs[i];d2[i]=dx*dx+gy[fs[i]]*gy[fs[i]];}
    vector<int> L(n,-1),Rr(n,-1);
    int last=-1;
    for(int i=0;i<n;i++){L[i]=last;if(d2[i]>=0)last=i;}
    last=-1;
    for(int i=n-1;i>=0;i--){Rr[i]=last;if(d2[i]>=0)last=i;}
    vector<pair<int,long double>> out;
    for(int i=0;i<n;i++)if(d2[i]<0){
        ll xu=xs[i];
        ll R2=qry((int)(xu+OFF))+xu*xu; // min squared distance to a known gem
        // delta^2 as fraction pn/pd, maximum over the two neighbours
        LL bn=0,bd=1;
        for(int t=0;t<2;t++){
            int kk=t?Rr[i]:L[i]; if(kk<0)continue;
            ll D=llabs(xu-xs[kk]);
            ll p=d2[kk]-R2-D*D;
            if(p>0){
                LL pn=(LL)p*p, pd=(LL)4*D*D;
                if((long double)pn*(long double)bd>(long double)bn*(long double)pd){bn=pn;bd=pd;}
            }
        }
        LL num=(LL)R2*bd-bn; // depth^2 = num/bd
        long double dep=sqrtl((long double)num/(long double)bd);
        out.push_back({fs[i],-dep});
    }
    sort(out.begin(),out.end());
    for(auto&o:out)printf("%d %.9Lf\n",o.first,o.second);
}
