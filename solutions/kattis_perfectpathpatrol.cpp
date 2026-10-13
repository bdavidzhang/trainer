#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n); vector<long long> S(n,0),M(n,0);
    for(int i=0;i<n-1;i++){int u,v;long long p;scanf("%d %d %lld",&u,&v,&p);S[u]+=p;S[v]+=p;M[u]=max(M[u],p);M[v]=max(M[v],p);}
    long long tot=0; for(int i=0;i<n;i++) tot+=max(2*M[i]-S[i],S[i]%2);
    printf("%lld\n",tot/2);
}
