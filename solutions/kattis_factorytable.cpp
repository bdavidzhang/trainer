#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int t; scanf("%d",&t);
    while(t--){
        int n; scanf("%d",&n);
        vector<ll> a(n); for(auto&x:a) scanf("%lld",&x);
        ll best=LLONG_MAX;
        // no break
        {
            ll d=a[1]-a[0];
            if(d>0 && a[0]%d==0){
                bool ok=true;
                for(int i=1;i<n;i++) if(a[i]-a[i-1]!=d) ok=false;
                if(ok) best=min(best,max(d,a[n-1]/d));
            }
        }
        for(int j=0;j+1<n;j++){
            ll i=a[j+1]-1;
            if(i<1||a[j]%i) continue;
            ll k=a[j]/i;
            if(k<i+1) continue;
            // a[j] at row i, col k ; a[0] at flat index (i-1)*k+(k-1)-j
            ll pos=(i-1)*k+(k-1)-j;
            if(pos<0) continue;
            if(pos+n-1>=k*k) continue;
            bool ok=true;
            for(int x=0;x<n&&ok;x++){
                ll p=pos+x; ll row=p/k+1,col=p%k+1;
                if(row*col!=a[x]) ok=false;
            }
            if(ok) best=min(best,k);
        }
        printf("%lld\n",best);
    }
}
