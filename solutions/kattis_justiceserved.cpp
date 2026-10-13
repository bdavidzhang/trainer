#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<long long> a(n),e(n);
    for(int i=0;i<n;i++){long long t;scanf("%lld %lld",&a[i],&t);e[i]=a[i]+t;}
    vector<long long> xs(e); sort(xs.begin(),xs.end()); xs.erase(unique(xs.begin(),xs.end()),xs.end());
    int m=xs.size();
    vector<int> ord(n); iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int x,int y){ if(a[x]!=a[y]) return a[x]<a[y]; return e[x]>e[y]; });
    // fenwick for suffix max: index reversed
    vector<int> bit(m+1,-1), res(n);
    for(int i:ord){
        int p=m-(int)(lower_bound(xs.begin(),xs.end(),e[i])-xs.begin()); // 1..m, larger end -> smaller p
        int best=-1; for(int x=p;x>0;x-=x&-x) best=max(best,bit[x]);
        res[i]=best+1;
        for(int x=p;x<=m;x+=x&-x) bit[x]=max(bit[x],res[i]);
    }
    for(int i=0;i<n;i++) printf("%d%c",res[i],i+1<n?' ':'\n');
}
