#include <bits/stdc++.h>
using namespace std;
// A block of L>=2 original crystals can become exactly the values 1..L (split into k parts,
// turn each part into a single 1, fuse the k ones); a single crystal can be a_i or 1.
// So b_j must be matched to a block of length >= b_j, or to one crystal equal to b_j.
int main(){
    int t; scanf("%d",&t);
    while(t--){
        int n,m; scanf("%d %d",&n,&m);
        vector<long long> a(n+1),b(m+1);
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
        for(int j=1;j<=m;j++) scanf("%lld",&b[j]);
        vector<char> cur(n+1,0),nx(n+1,0); cur[0]=1;
        for(int j=1;j<=m;j++){
            long long mn=-1;
            for(int i=0;i<=n;i++) if(cur[i]){mn=i;break;}
            nx[0]=0;
            for(int i=1;i<=n;i++)
                nx[i]=(cur[i-1]&&a[i]==b[j])||(mn>=0&&mn+b[j]<=i);
            swap(cur,nx);
        }
        puts(cur[n]?"YES":"NO");
    }
}
