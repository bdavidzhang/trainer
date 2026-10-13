#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n; scanf("%d",&n);
    vector<ll> s(n); for(auto&v:s) scanf("%lld",&v);
    sort(s.rbegin(),s.rend());
    ll att=s[0], def=0; int r=1;
    for(int i=1;i<n;i++){
        def+=s[i];
        if(def>=att){ att+=def; def=0; r=i+1; }
    }
    printf("%d\n",r);
}
