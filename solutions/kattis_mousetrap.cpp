#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef __int128 LL;
// E = (sum of areas of all C(n,3) triangles) / area. For a<b the cross p_a x p_b has coefficient n+2a-2b.
int main(){
    int n; scanf("%d",&n);
    vector<ll> x(n),y(n);
    for(int i=0;i<n;i++) scanf("%lld %lld",&x[i],&y[i]);
    for(int i=n-1;i>=0;i--){x[i]-=x[0];y[i]-=y[0];}
    LL Sx=0,Sy=0,Tx=0,Ty=0,tot=0,area=0;
    for(int b=0;b<n;b++){
        LL c1=Sx*y[b]-Sy*x[b];
        LL c2=Tx*y[b]-Ty*x[b];
        tot+=(LL)(n-2*b)*c1+2*c2;
        Sx+=x[b];Sy+=y[b];Tx+=(LL)b*x[b];Ty+=(LL)b*y[b];
        int nb=(b+1)%n;
        area+=(LL)x[b]*y[nb]-(LL)y[b]*x[nb];
    }
    printf("%.9Lf\n",(long double)tot/(long double)area);
}
