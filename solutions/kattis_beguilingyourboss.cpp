#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
static inline int rd(){int c=getchar_unlocked();while(c<'0')c=getchar_unlocked();int x=0;while(c>='0'){x=x*10+c-'0';c=getchar_unlocked();}return x;}
int main(){
    int n=rd(),k=rd();
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()^0x9e3779b97f4a7c15ULL);
    vector<u64> A(k+1),B(k+1);
    vector<int> arr(k+1);
    for(int i=1;i<=k;i++){A[i]=rng()|1;B[i]=rng();arr[i]=i;}
    vector<u64> h(n+1);
    u64 H=0; // relative hash: only track differences from the identity
    h[0]=0;
    for(int i=1;i<=n;i++){
        int a=rd(),b=rd();
        H-=A[a]*B[arr[a]]+A[b]*B[arr[b]];
        swap(arr[a],arr[b]);
        H+=A[a]*B[arr[a]]+A[b]*B[arr[b]];
        h[i]=H;
    }
    sort(h.begin(),h.end());
    long long ans=0;
    for(int i=0;i<=n;){
        int j=i;while(j<=n&&h[j]==h[i])j++;
        long long c=j-i;ans+=c*(c-1)/2;i=j;
    }
    printf("%lld\n",ans);
}
