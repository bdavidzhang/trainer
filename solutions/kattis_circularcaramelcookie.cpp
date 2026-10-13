#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static ll isq(ll v){ ll r=(ll)sqrtl((long double)v); while(r*r>v) r--; while((r+1)*(r+1)<=v) r++; return r; }
static ll cnt(ll R){ ll t=0; for(ll x=1;x*x<R;x++) t+=isq(R-x*x); return 4*t; }
int main(){
    ll s; cin>>s;
    ll lo=1,hi=2000000000LL; // smallest R with cnt(R)>s
    while(lo<hi){ ll m=(lo+hi)/2; if(cnt(m)>s) hi=m; else lo=m+1; }
    printf("%.10f\n",sqrt((double)lo));
}
