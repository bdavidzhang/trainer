#include <bits/stdc++.h>
using namespace std;
const long long M=998244353;
long long pw(long long b,long long e){long long r=1;b%=M;while(e){if(e&1)r=r*b%M;b=b*b%M;e>>=1;}return r;}
int main(){
    long long m,k; cin>>m>>k;
    vector<int> mu(k+1,1); vector<char> comp(k+1,0); vector<int> pr;
    for(int i=2;i<=k;i++){ if(!comp[i]){pr.push_back(i);mu[i]=-1;}
        for(int p:pr){ if((long long)p*i>k)break; comp[p*i]=1; if(i%p==0){mu[p*i]=0;break;} mu[p*i]=-mu[i]; } }
    long long ans=1;
    for(long long d=1;d<=k;d++){ if(!mu[d])continue; long long v=(pw(2*(k/d)+1,m)-1+M)%M; ans=(ans+mu[d]*v+M)%M; }
    printf("%lld\n",ans);
}
