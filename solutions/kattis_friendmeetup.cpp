#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
int main(){
    int n;scanf("%d",&n);
    vector<ll> x(n),y(n),v(n);
    for(int i=0;i<n;i++)scanf("%lld %lld %lld",&x[i],&y[i],&v[i]);
    // Dinkelbach on max d(i,j)/(v_i+v_j)
    ll bn=0,bd=1; // best ratio as fraction
    for(int it=0;it<200;it++){
        ld t=(ld)bn/(ld)bd;
        ll nn=bn,nd=bd;
        for(int s=0;s<2;s++){
            int bi=-1,bj=-1;ld vi=-1e30L,vj=-1e30L;
            for(int i=0;i<n;i++){
                ll u=s?x[i]-y[i]:x[i]+y[i];
                ld p=(ld)u-t*v[i],q=(ld)(-u)-t*v[i];
                if(p>vi){vi=p;bi=i;}
                if(q>vj){vj=q;bj=i;}
            }
            if(bi!=bj){
                ll d=llabs(x[bi]-x[bj])+llabs(y[bi]-y[bj]);
                ll den=v[bi]+v[bj];
                if((__int128)d*nd>(__int128)nn*den){nn=d;nd=den;}
            }
        }
        if(nn==bn&&nd==bd)break;
        bn=nn;bd=nd;
    }
    printf("%.10Lf\n",(ld)bn/(ld)bd);
}
