#include <bits/stdc++.h>
using namespace std;
typedef long long ll;typedef unsigned long long ull;
const ll MOD=998244353;
int main(){
    int n;scanf("%d",&n);vector<ull> a(n);
    for(auto&x:a)scanf("%llu",&x);
    ull all=~0ULL;for(ull x:a)all&=x;
    if(all){
        ll p=1;for(int i=0;i<n;i++)p=p*2%MOD;
        printf("%lld\n",((p-n)%MOD+MOD)%MOD);return 0;
    }
    // lo[c]: smallest j with AND a[j..c-1] != 0, for c=1..n
    vector<int> lo(n+1,0);
    {
        int cnt[60]={0};int j=0;int nz=0; // nz = number of bits with cnt==len
        // maintain window [j,c-1]
        for(int c=1;c<=n;c++){
            ull x=a[c-1];
            for(int b=0;b<60;b++)if(x>>b&1)cnt[b]++;
            while(true){
                int len=c-j;bool ok=false;
                for(int b=0;b<60;b++)if(cnt[b]==len){ok=true;break;}
                if(ok)break;
                ull y=a[j];for(int b=0;b<60;b++)if(y>>b&1)cnt[b]--;
                j++;
            }
            lo[c]=j;
        }
        (void)nz;
    }
    // prefix ANDs from 0 going right
    vector<ull> pre(n);pre[0]=a[0];for(int i=1;i<n;i++)pre[i]=pre[i-1]&a[i];
    ll ans=0;
    vector<ll> g(n+2),ps(n+2);
    // l from 0 down to -(n-1): element index (l+n)%n, cut position c = l+n (1..n)
    ull M=a[0];int c=n; // class starts at c (l=0)
    while(c>=1&&M){
        // find extent of class: cuts c, c-1, ..., c2 with same mask
        int c2=c;
        while(c2-1>=1&&((M&a[c2-1])==M))c2--;
        // R(M): max r with M & pre[r] != 0
        int lo_=0,hi=n-1;
        while(lo_<hi){int mid=(lo_+hi+1)/2;if(M&pre[mid])lo_=mid;else hi=mid-1;}
        int R=lo_;
        ps[0]=0;
        for(int x=1;x<=n;x++){
            ll v=(x<=R+1)?1:0;
            int L=max(lo[x],1);
            if(L<=x-1)v+=ps[x-1]-ps[L-1];
            v%=MOD;if(v<0)v+=MOD;
            g[x]=v;ps[x]=(ps[x-1]+v)%MOD;
        }
        ans=(ans+ps[c]-ps[c2-1])%MOD;
        if(c2-1>=1)M&=a[c2-1];
        c=c2-1;
    }
    ans%=MOD;if(ans<0)ans+=MOD;
    printf("%lld\n",ans);
}
