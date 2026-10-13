#include <bits/stdc++.h>
using namespace std;
int p[100005];
int f(int x){ while(p[x]!=x){p[x]=p[p[x]];x=p[x];} return x; }
int main(){
    int n,m,k; scanf("%d %d %d",&n,&m,&k);
    for(int i=1;i<=n;i++) p[i]=i;
    vector<int> xs(m);
    for(int i=0;i<m;i++){int x,y; scanf("%d %d",&x,&y); xs[i]=x; p[f(x)]=f(y);}    
    vector<long long> sz(n+1,0),ec(n+1,0);
    for(int i=1;i<=n;i++) sz[f(i)]++;
    for(int i=0;i<m;i++) ec[f(xs[i])]++;
    long long ans=0;
    for(int i=1;i<=n;i++) if(f(i)==i && sz[i]==k && ec[i]==(long long)k*(k-1)) ans++;
    printf("%lld\n",ans);
}
