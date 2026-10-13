#include <bits/stdc++.h>
using namespace std;
int main(){
    long long n;int m;scanf("%lld %d",&n,&m);
    vector<long long>g;
    for(int i=0;i<m;i++){long long c;scanf("%lld",&c);if(c<n)g.push_back(n-c);}
    if(g.empty()){puts("1");return 0;}
    sort(g.begin(),g.end());
    long long mx=g.back();
    // j clusters: mx + sum of smallest j-1 <= n-j
    long long sum=mx;int j=1;
    for(size_t i=0;i+1<g.size();i++){
        if(sum+g[i]+(j+1)<=n){sum+=g[i];j++;}
        else break;
    }
    printf("%d\n",j);
}
