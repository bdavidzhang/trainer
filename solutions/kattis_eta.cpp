#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll a,b; char ch; cin>>a>>ch>>b;
    for(ll k=1;k<=5000;k++){
        ll n=k*b,S=k*a;
        if(S<n-1) break; // only gets worse as k grows when a<b
        if(S>n*(n-1)/2) continue;
        // assign depths greedily
        vector<int> last(n+1,0); last[0]=1;
        ll rem=S; int mx=0;
        string out; out+=to_string(n)+" "+to_string(n-1)+"\n";
        for(ll i=2;i<=n;i++){
            ll d=min<ll>(mx+1, rem-(n-i));
            out+=to_string(last[d-1])+" "+to_string(i)+"\n";
            last[d]=i; mx=max<ll>(mx,d); rem-=d;
        }
        fputs(out.c_str(),stdout);
        return 0;
    }
    puts("impossible");
}
