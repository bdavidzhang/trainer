#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// s = A_{K-1} followed by ones forever, where A_0 = 0^K 1 and A_j = (A_{j-1})^K 1.
vector<ll> len, ones;
ll K;
ll f(int j, ll n){ // ones among first n chars of A_j, 0<=n<=len[j]
    if(n<=0) return 0;
    if(n>=len[j]) return ones[j];
    if(j==0) return 0; // n<=K -> zeros
    ll q=n/len[j-1], r=n%len[j-1];
    return q*ones[j-1]+f(j-1,r);
}
int main(){
    ll N; 
    if(scanf("%lld %lld",&N,&K)!=2) return 0;
    len.push_back(K+1); ones.push_back(1);
    // build levels until len >= N or level K-1 reached
    while((ll)len.size()<K && len.back()<N){
        ll l=len.back(), o=ones.back();
        len.push_back(l*K+1); ones.push_back(o*K+1);
    }
    int top=len.size()-1;
    ll ans;
    if(N>len[top]) ans=ones[top]+(N-len[top]); // only possible when top==K-1: all ones afterwards
    else ans=f(top,N);
    printf("%lld\n",ans);
}
