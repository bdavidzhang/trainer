#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef unsigned long long ull;
// Center m, product m^3. Per prime exponent c the additive magic square has params (a,b), |a|+|b|<=c.
// Distinctness excludes 8 lines through the origin (a=0,b=0,a=+-b,a=+-2b,b=+-2a).
int main(){
    const int N=1000000;
    vector<int> spf(N+1,0);
    for(int i=2;i<=N;i++) if(!spf[i]) for(int j=i;j<=N;j+=i) if(!spf[j]) spf[j]=i;
    vector<ll> pre(N+1,0);
    for(int m=1;m<=N;m++){
        ll A=1,B=1,C=1,D=1; int x=m;
        while(x>1){int p=spf[x],c=0; while(x%p==0){x/=p;c++;}
            A*=2LL*c*c+2*c+1; B*=2*c+1; C*=2*(c/2)+1; D*=2*(c/3)+1;}
        pre[m]=pre[m-1]+A-2*B-2*C-4*D+7;
    }
    int t; scanf("%d",&t);
    while(t--){ ull n; scanf("%llu",&n);
        ull r=(ull)cbrtl((long double)n);
        while(r*r*r>n) r--;
        while((r+1)*(r+1)*(r+1)<=n) r++;
        printf("%lld\n",pre[r]);
    }
}
