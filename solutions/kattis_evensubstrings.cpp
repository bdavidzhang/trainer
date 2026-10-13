#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,N;string s;
vector<array<int,64>> cnt;vector<int> lz;vector<int> P;
void build(int o,int l,int r){if(l==r){cnt[o].fill(0);cnt[o][P[l]]=1;return;}int mid=(l+r)/2;build(o*2,l,mid);build(o*2+1,mid+1,r);for(int v=0;v<64;v++)cnt[o][v]=cnt[o*2][v]+cnt[o*2+1][v];}
void upd(int o,int l,int r,int a,int d){ // xor d on [a, N-1]
    if(a<=l){array<int,64> t;for(int v=0;v<64;v++)t[v^d]=cnt[o][v];cnt[o]=t;lz[o]^=d;return;}
    int mid=(l+r)/2;if(a<=mid)upd(o*2,l,mid,a,d);upd(o*2+1,mid+1,r,a,d);
    int z=lz[o];for(int v=0;v<64;v++)cnt[o][v^z]=cnt[o*2][v]+cnt[o*2+1][v];}
ll acc[64];
void qry(int o,int l,int r,int a,int b,int x){if(a<=l&&r<=b){for(int v=0;v<64;v++)acc[v^x]+=cnt[o][v];return;}
    int mid=(l+r)/2;x^=lz[o];if(a<=mid)qry(o*2,l,mid,a,b,x);if(b>mid)qry(o*2+1,mid+1,r,a,b,x);}
int main(){static char buf[200005];scanf("%s",buf);s=buf;n=s.size();N=n+1;P.assign(N,0);for(int i=0;i<n;i++)P[i+1]=P[i]^(1<<(s[i]-'a'));
    cnt.resize(4*N);lz.assign(4*N,0);build(1,0,N-1);
    int q;scanf("%d",&q);while(q--){int t;scanf("%d",&t);if(t==1){int l,r;scanf("%d %d",&l,&r);memset(acc,0,sizeof acc);qry(1,0,N-1,l-1,r,0);ll res=0;for(int v=0;v<64;v++)res+=acc[v]*(acc[v]-1)/2;printf("%lld\n",res);}
        else{int i;char x;scanf("%d %c",&i,&x);int d=(1<<(s[i-1]-'a'))^(1<<(x-'a'));s[i-1]=x;if(d)upd(1,0,N-1,i,d);}}
}
