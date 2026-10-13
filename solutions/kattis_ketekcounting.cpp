#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=998244353;
int main(){
    static char buf[30005]; scanf("%s",buf);
    string s=buf; int n=s.size(); int H=n/2;
    vector<ll> g(H+1,0); g[0]=1;
    for(int c=1;c<=2*H-1;c++){
        int d=n-c;
        int l=(c-1)/2;
        ll prod=1;
        // initial range [l, c-l) 
        for(int p=l;p<c-l;p++){
            char x=s[p],y=s[p+d];
            if(x=='?'&&y=='?')prod=prod*26%MOD;
            else if(x!='?'&&y!='?'&&x!=y)prod=0;
        }
        while(prod){
            int j=c-l;
            if(j>H)break;
            if(g[l]) g[j]=(g[j]+g[l]*prod)%MOD;
            if(l==0)break;
            l--;
            // add positions l and c-l-1
            for(int p: {l,c-l-1}){
                char x=s[p],y=s[p+d];
                if(x=='?'&&y=='?')prod=prod*26%MOD;
                else if(x!='?'&&y!='?'&&x!=y){prod=0;break;}
            }
        }
    }
    // inner(j): middle [j, n-j)
    vector<int> pq(n+1,0); for(int i=0;i<n;i++)pq[i+1]=pq[i]+(s[i]=='?');
    vector<ll> pw(n+1,1); for(int i=1;i<=n;i++)pw[i]=pw[i-1]*26%MOD;
    ll ans=0;
    for(int j=0;j<=H;j++){
        ll inner = (n-2*j==0)?1:pw[pq[n-j]-pq[j]];
        ans=(ans+g[j]*inner)%MOD;
    }
    printf("%lld\n",ans);
}
