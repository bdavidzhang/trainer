#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 LL;
int main(){
    string a,b;ll c,d;
    cin>>a>>b>>c>>d;
    ll g=std::gcd(c,d);c/=g;d/=g;
    int n=a.size(),m=b.size();
    int cb[10]={0};
    for(char ch:b)cb[ch-'0']++;
    const ll LIM=1000000000000000000LL;
    for(int mask=1;mask<(1<<n);mask++){ // mask = kept digits
        int first=__builtin_ctz(mask);
        if(a[first]=='0')continue;
        ll v=0;int rem[10]={0};
        for(int i=0;i<n;i++){
            if(mask>>i&1)v=v*10+(a[i]-'0');
            else rem[a[i]-'0']++;
        }
        if(v%c)continue;
        LL w=(LL)(v/c)*d;
        if(w>=LIM||w<=0)continue;
        ll bv=(ll)w;
        string s=to_string(bv);
        if((int)s.size()!=m-(n-__builtin_popcount(mask)))continue;
        // subsequence check
        int j=0;int cs[10]={0};
        for(int i=0;i<m&&j<(int)s.size();i++)if(b[i]==s[j])j++;
        if(j!=(int)s.size())continue;
        for(char ch:s)cs[ch-'0']++;
        bool ok=true;
        for(int t=0;t<10;t++)if(cb[t]-cs[t]!=rem[t])ok=false;
        if(!ok)continue;
        printf("possible\n%lld %lld\n",v,bv);
        return 0;
    }
    puts("impossible");
}
