#include <bits/stdc++.h>
using namespace std;
int n; vector<int> bit;
void upd(int i){for(++i;i<=n;i+=i&-i)bit[i]++;}
int qry(int i){int s=0;for(;i>0;i-=i&-i)s+=bit[i];return s;} // count of ranks < i
int main(){
    scanf("%d",&n); vector<int> a(n),s; for(auto&x:a)scanf("%d",&x); s=a; sort(s.begin(),s.end());
    bit.assign(n+1,0); long long ans=0;
    for(int i=0;i<n;i++){
        int r=lower_bound(s.begin(),s.end(),a[i])-s.begin();
        long long L=i-qry(r+1)+0; // larger elements to the left
        long long tot=n-1-r; ans+=min(L,tot-L); upd(r);
    }
    printf("%lld\n",ans);
}
