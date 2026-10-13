#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n; ll k; int d,s;
    scanf("%d %lld %d %d",&n,&k,&d,&s);
    vector<ll> a(n);
    for(auto&x:a) scanf("%lld",&x);
    int kk=k%n;
    vector<ll> pre(2*n+1,0);
    for(int i=0;i<2*n;i++) pre[i+1]=pre[i]+a[i%n];
    vector<ll> W(n),F(n);
    for(int p=0;p<n;p++) W[p]=pre[p+s]-pre[p];
    // F[p] = sum_{l<d} W[(p+kk*l)%n]
    vector<char> vis(n,0);
    vector<int> cyc; vector<ll> cp;
    for(int st=0;st<n;st++) if(!vis[st]){
        cyc.clear();
        int p=st;
        while(!vis[p]){vis[p]=1;cyc.push_back(p);p=(p+kk)%n;}
        int c=cyc.size();
        cp.assign(2*c+1,0);
        for(int i=0;i<2*c;i++) cp[i+1]=cp[i]+W[cyc[i%c]];
        ll q=d/c; int r=d%c;
        for(int i=0;i<c;i++) F[cyc[i]]=q*cp[c]+cp[i+r]-cp[i];
    }
    // M[p] = max F over cyclic window of length L=n-s+1 starting at p
    int L=n-s+1;
    vector<ll> M(n);
    deque<int> dq;
    for(int i=0;i<2*n;i++){
        while(!dq.empty()&&F[dq.back()%n]<=F[i%n]) dq.pop_back();
        dq.push_back(i);
        while(dq.front()<=i-L) dq.pop_front();
        int stp=i-L+1;
        if(stp>=0&&stp<n) M[stp]=F[dq.front()%n];
    }
    ll best=LLONG_MIN; int p=0;
    for(int j=0;j<=n-d;j++){
        best=max(best,M[p]);
        p=(p+kk)%n;
    }
    printf("%lld\n",best);
}
