#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n); vector<unsigned> a(n); for(auto&x:a) scanf("%u",&x);
    vector<int> idx(n); iota(idx.begin(),idx.end(),0);
    sort(idx.begin(),idx.end(),[&](int x,int y){return a[x]<a[y];});
    // try divisors in increasing order; small values have ~n/a expected multiples
    for(int t=0;t<n;t++){
        int i=idx[t]; unsigned d=a[i];
        for(int j=0;j<n;j++) if(j!=i && a[j]%d==0){ printf("%d %d\n",i+1,j+1); return 0; }
    }
    printf("1 2\n");
}
