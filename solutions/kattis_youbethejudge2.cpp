#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    int s=1<<n; long long K=((1LL<<(2*n))-1)/3;
    vector<int> cnt(K+1,0),mnr(K+1,INT_MAX),mxr(K+1,-1),mnc(K+1,INT_MAX),mxc(K+1,-1);
    for(int i=0;i<s;i++)for(int j=0;j<s;j++){
        int x; scanf("%d",&x);
        cnt[x]++; mnr[x]=min(mnr[x],i); mxr[x]=max(mxr[x],i); mnc[x]=min(mnc[x],j); mxc[x]=max(mxc[x],j);
    }
    bool ok = cnt[0]==1;
    for(long long c=1;c<=K&&ok;c++){
        if(cnt[c]!=3||mxr[c]-mnr[c]!=1||mxc[c]-mnc[c]!=1) ok=false;
    }
    puts(ok?"1":"0");
}
