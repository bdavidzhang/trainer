#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n,m;ll r;scanf("%d %d %lld",&n,&m,&r);
    vector<ll>x(n),y(n),a(m),b(m),c(m);
    for(int i=0;i<n;i++)scanf("%lld %lld",&x[i],&y[i]);
    for(int i=0;i<m;i++)scanf("%lld %lld %lld",&a[i],&b[i],&c[i]);
    ll pieces=1+m;
    for(int i=0;i<m;i++)for(int j=i+1;j<m;j++){
        ll D=a[i]*b[j]-a[j]*b[i];
        if(!D)continue;
        ll X=b[i]*c[j]-b[j]*c[i],Y=c[i]*a[j]-c[j]*a[i];
        // point (X/D,Y/D)
        if((__int128)X*X+(__int128)Y*Y<(__int128)r*r*D*D)pieces++;
    }
    set<vector<bool>> s;
    for(int i=0;i<n;i++){vector<bool>v(m);for(int j=0;j<m;j++)v[j]=a[j]*x[i]+b[j]*y[i]+c[j]>0;s.insert(v);}
    puts(pieces==n&&(int)s.size()==n?"yes":"no");}
