#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n; ll K;
vector<ll> d,w;
ll ans=0;
vector<ll> sm,mx,vals; vector<int> bit;
void upd(int i){for(i++;i<=(int)vals.size();i+=i&-i)bit[i]++;}
int qry(int i){int s=0;for(;i>0;i-=i&-i)s+=bit[i];return s;} // count of idx < i
void solve(int l,int r){
    if(l==r){ if(d[l]==0)ans++; return;}
    int m=(l+r)/2;
    solve(l,m);solve(m+1,r);
    // sm,mx indexed by position
    ll s=0,x=0;
    for(int i=m;i>=l;i--){s+=w[i];x=max(x,d[i]);sm[i]=s;mx[i]=x;}
    s=0;x=0;
    for(int j=m+1;j<=r;j++){s+=w[j];x=max(x,d[j]);sm[j]=s;mx[j]=x;}
    // Case A: maxL >= maxR
    vals.assign(sm.begin()+m+1,sm.begin()+r+1);
    sort(vals.begin(),vals.end());
    bit.assign(vals.size()+1,0);
    int p=m+1,cnt=0;
    for(int i=m;i>=l;i--){
        while(p<=r&&mx[p]<=mx[i]){upd(lower_bound(vals.begin(),vals.end(),sm[p])-vals.begin());p++;cnt++;}
        ll thr=(K+1)*mx[i]-sm[i];
        int idx=lower_bound(vals.begin(),vals.end(),thr)-vals.begin();
        ans+=cnt-qry(idx);
    }
    // Case B: maxR > maxL
    vals.assign(sm.begin()+l,sm.begin()+m+1);
    sort(vals.begin(),vals.end());
    bit.assign(vals.size()+1,0);
    p=m;cnt=0;
    for(int j=m+1;j<=r;j++){
        while(p>=l&&mx[p]<mx[j]){upd(lower_bound(vals.begin(),vals.end(),sm[p])-vals.begin());p--;cnt++;}
        ll thr=(K+1)*mx[j]-sm[j];
        int idx=lower_bound(vals.begin(),vals.end(),thr)-vals.begin();
        ans+=cnt-qry(idx);
    }
}
int main(){
    scanf("%d %lld",&n,&K);
    vector<ll> h(n),a(n);
    for(auto&v:h)scanf("%lld",&v);
    for(auto&v:a)scanf("%lld",&v);
    d.resize(n);w.resize(n);sm.resize(n);mx.resize(n);
    for(int i=0;i<n;i++){ll t=h[i]-a[i]; w[i]=t>=0?t:K*t; d[i]=max(t,0LL);}
    // single-element case uses d==0 meaning t<=0; fix: need t==0
    // handle by marking negatives
    vector<char> neg(n);
    for(int i=0;i<n;i++)neg[i]=(h[i]<a[i]);
    solve(0,n-1);
    for(int i=0;i<n;i++)if(neg[i])ans--;
    printf("%lld\n",ans);
}
