#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<long long> a(n);
    for(auto&x:a) scanf("%lld",&x);
    map<string,int> id={{"ppp",0},{"pp",1},{"p",2},{"mp",3},{"mf",4},{"f",5},{"ff",6},{"fff",7}};
    vector<int> dyn(n,-1);
    for(int i=0;i<m;i++){int x; char s[8]; scanf("%d %7s",&x,s); dyn[x-1]=id[s];}
    for(int i=1;i<n;i++) if(dyn[i]<0) dyn[i]=dyn[i-1];
    vector<long long> g[8];
    for(int i=0;i<n;i++) g[dyn[i]].push_back(a[i]);
    for(auto&v:g) sort(v.begin(),v.end());
    long long ans=0;
    for(int lo=0;lo<8;lo++) for(int hi=lo+1;hi<8;hi++){
        // pairs x in g[lo], y in g[hi] with x>=y
        size_t p=0;
        for(long long x:g[lo]){ while(p<g[hi].size()&&g[hi][p]<=x) p++; ans+=p; }
    }
    printf("%lld\n",ans);
}
