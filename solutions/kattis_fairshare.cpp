#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<long long> a(n),b(n); long long A=0,B=0;
    for(int i=0;i<n;i++){ scanf("%lld %lld",&a[i],&b[i]); A+=a[i]; B+=b[i]; }
    for(int i=0;i<n;i++) if(B-(A-a[i])<=b[i]){ printf("%d\n",i+1); return 0; }
    puts("impossible");
}
