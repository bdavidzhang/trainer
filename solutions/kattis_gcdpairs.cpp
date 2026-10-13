#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int cntp[1000001],cntn[1000001];
int main(){
    int n;scanf("%d",&n);
    vector<int> primes;
    {vector<char> s(10001,0);for(int i=2;i<=10000;i++){if(!s[i]){primes.push_back(i);for(int j=i*i;j<=10000;j+=i)s[j]=1;}}}
    // cnt[d] for squarefree d with d^2 | a ; sign stored separately
    static signed char sg[1000001];
    static int cnt[1000001];
    vector<ll> a(n);
    for(auto&x:a)scanf("%lld",&x);
    sort(a.begin(),a.end());
    vector<ll> ds;
    for(int i=0;i<n;){
        int j=i;while(j<n&&a[j]==a[i])j++;
        int mult=j-i;
        ll x=a[i];
        vector<ll> sq;
        for(int p:primes){
            if((ll)p*p>x)break;
            if(x%p==0){
                int e=0;while(x%p==0){x/=p;e++;}
                if(e>=2)sq.push_back(p);
            }
        }
        if(x>1){
            ll r=(ll)sqrtl((long double)x);
            while(r*r>x)r--;
            while((r+1)*(r+1)<=x)r++;
            if(r*r==x&&r>1)sq.push_back(r);
        }
        int s=sq.size();
        for(int mask=0;mask<(1<<s);mask++){
            ll d=1;for(int b=0;b<s;b++)if(mask>>b&1)d*=sq[b];
            cnt[d]+=mult;sg[d]=(__builtin_popcount(mask)&1)?-1:1;
        }
        i=j;
    }
    ll ans=0;
    for(int d=1;d<=1000000;d++)if(cnt[d]>1)ans+=sg[d]*((ll)cnt[d]*(cnt[d]-1)/2);
    printf("%lld\n",ans);
}
