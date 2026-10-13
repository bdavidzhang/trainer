#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1e9+7;
int main(){
    ll E;int L,R; scanf("%lld %d %d",&E,&L,&R);
    vector<bool> comp(R+1,false);
    ll prod=1;
    for(int i=2;i<=R;i++){
        if(!comp[i]){
            if(i>=L)prod=prod*i%MOD;
            for(ll j=(ll)i*i;j<=R;j+=i)comp[j]=true;
        }
    }
    ll r=1,b=prod;
    while(E){if(E&1)r=r*b%MOD;b=b*b%MOD;E>>=1;}
    printf("%lld\n",r);
}
