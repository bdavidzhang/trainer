#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll M=1e9+7;
ll pw(ll b,ll e){ll r=1;b%=M;while(e){if(e&1)r=r*b%M;b=b*b%M;e>>=1;}return r;}
int n,q;
vector<ll> f1,f2;
void upd(vector<ll>&f,int i,ll v){for(;i<=n;i+=i&-i)f[i]=(f[i]+v)%M;}
ll qry(vector<ll>&f,int i){ll r=0;for(;i>0;i-=i&-i)r+=f[i];return r%M;}
int main(){
    char buf[64];
    scanf("%d %d %63s",&n,&q,buf);
    // parse p as integer over 10^6
    ll num=0; int dec=0; bool dot=false;
    for(char*c=buf;*c;c++){ if(*c=='.'){dot=true;continue;} num=num*10+(*c-'0'); if(dot)dec++; }
    while(dec<6){num*=10;dec++;}
    ll den=1; for(int i=0;i<dec;i++)den*=10;
    ll r=((den-num)%M+M)%M*pw(den,M-2)%M; // 1-p
    ll ri=pw(r,M-2);
    vector<ll> P(n+1),PI(n+1); P[0]=PI[0]=1;
    for(int i=1;i<=n;i++){P[i]=P[i-1]*r%M;PI[i]=PI[i-1]*ri%M;}
    f1.assign(n+1,0);f2.assign(n+1,0);
    while(q--){
        char op[4]; scanf("%3s",op);
        if(op[0]=='?'){
            int x; scanf("%d",&x);
            ll a=qry(f1,x)*P[x]%M;                       // sum b*r^{-pos}, pos<=x
            ll b=((qry(f2,n)-qry(f2,x))%M+M)%M*PI[x]%M;  // sum b*r^{pos}, pos>x
            printf("%lld\n",(a+b)%M);
        } else {
            ll b; int x; scanf("%lld %d",&b,&x);
            b%=M; if(op[0]=='-') b=(M-b)%M;
            upd(f1,x,b*PI[x]%M); upd(f2,x,b*P[x]%M);
        }
    }
}
