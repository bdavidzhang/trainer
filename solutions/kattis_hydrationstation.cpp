#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 i128;
// y = x-1. F(y) = (y+1) * sum ceil(b_i / y); optimum at a breakpoint y = b_i/j.
// With u = 1/y = j/v: sum ceil(b_i/y) = n + #{(i,j>=1): j/b_i < u}. Sweep breakpoints in increasing u.
struct El{double u;int v,j;};
int main(){
    int n;scanf("%d",&n);
    const int V=100000;
    vector<int> cnt(V+1,0);
    ll B=0;int mx=0;
    for(int i=0;i<n;i++){int b;scanf("%d",&b);cnt[b]++;B+=b;mx=max(mx,b);}
    vector<int> vals;
    for(int v=1;v<=V;v++)if(cnt[v])vals.push_back(v);
    // upper bound U on the optimum from some integer y
    auto F=[&](ll y)->ll{
        ll s=0;for(int v:vals)s+=(ll)cnt[v]*((v+y-1)/y);
        return (y+1)*s;
    };
    ll U=F(mx);
    {
        set<ll> tries;
        double y0=sqrt((double)B/n);
        for(double f=0.25;f<=4.01;f*=1.189207115)tries.insert(max(1LL,min((ll)mx,(ll)llround(y0*f))));
        for(double y=1;y<=mx;y*=1.5)tries.insert((ll)y);
        for(ll y:tries)U=min(U,F(y));
    }
    // F(y) >= B*(1+1/y)  =>  only u <= (U-B)/B can be optimal
    ll Pn=U-B,Q=B;
    vector<ll> jmax(V+1,0);
    double total=0;
    for(int v:vals){jmax[v]=min((ll)v*Pn/Q,(ll)v) ; total+=jmax[v];}
    // (u <= 1 is not required in general, but jmax = floor(v*P/Q) is the real cap)
    for(int v:vals)jmax[v]=(ll)v*Pn/Q;
    total=0;for(int v:vals)total+=jmax[v];
    ll D=max(1LL,(ll)(total/131072.0*((double)Q/max(1LL,Pn))) );
    // chunks: u in [c/D,(c+1)/D); number of chunks ~ umax*D
    ll bestNum=-1,bestDen=1;int bv=0,bj=0; // F = (v+j)*(n+W)/j
    ll Wt=0;
    vector<El> els,tmp;vector<int> head;
    ll maxc=(ll)((i128)Pn*D/Q);
    for(ll c=0;c<=maxc;c++){
        els.clear();
        for(int v:vals){
            ll jlo=(c*v+D-1)/D;if(jlo<1)jlo=1;
            ll jhi=min(jmax[v],((c+1)*v-1)/D);
            for(ll j=jlo;j<=jhi;j++)els.push_back({(double)j/v,v,(int)j});
        }
        int m=els.size();
        if(!m)continue;
        // bucket sort by u
        head.assign(m+2,0);
        tmp.resize(m);
        vector<int>&h=head;
        static vector<int> bid;bid.resize(m);
        for(int i=0;i<m;i++){
            double p=(els[i].u*(double)D-(double)c)*m;
            int b=p<0?0:(p>=m?m-1:(int)p);
            bid[i]=b;h[b+1]++;
        }
        for(int b=0;b<m;b++)h[b+1]+=h[b];
        for(int i=0;i<m;i++)tmp[h[bid[i]]++]=els[i];
        // h[b] is now end of bucket b; insertion sort overall (buckets are tiny and ordered)
        for(int i=1;i<m;i++){
            El x=tmp[i];int k=i-1;
            while(k>=0&&tmp[k].u>x.u){tmp[k+1]=tmp[k];k--;}
            tmp[k+1]=x;
        }
        for(int i=0;i<m;){
            int k=i;ll add=0;
            while(k<m&&tmp[k].u==tmp[i].u){add+=cnt[tmp[k].v];k++;}
            ll num=(ll)(tmp[i].v+tmp[i].j)*(n+Wt),den=tmp[i].j;
            if(bestNum<0||(i128)num*bestDen<(i128)bestNum*den){bestNum=num;bestDen=den;bv=tmp[i].v;bj=tmp[i].j;}
            Wt+=add;
            i=k;
        }
    }
    ll p=bv+bj,q=bj;
    ll g=std::gcd(p,q);
    printf("%lld/%lld\n",p/g,q/g);
}
