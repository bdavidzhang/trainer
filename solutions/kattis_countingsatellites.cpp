#include <bits/stdc++.h>
using namespace std;
typedef unsigned __int128 u128;
int main(){
    unsigned long long k; cin>>k;
    // Z: blocks A^p T^p E^p L^2p I^p T^p E^p for p = 128,64,...,1
    string Z;
    for(int p=128;p>=1;p/=2){
        Z+=string(p,'A')+string(p,'T')+string(p,'E')+string(2*p,'L')+string(p,'I')+string(p,'T')+string(p,'E');
    }
    const string W="ATELLITE";
    int n=Z.size();
    vector<u128> f(n,0); // number of "ATELLITE" subsequences in Z[i..]
    u128 suf[9]; for(int j=0;j<9;j++)suf[j]=0; suf[8]=1;
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<8;j++) if(W[j]==Z[i]) suf[j]+=suf[j+1];
        f[i]=suf[0];
    }
    string out; u128 rem=k;
    for(int i=0;i<n;i++){
        if(Z[i]=='A'){ u128 c=rem/f[i]; rem-=c*f[i]; out+=string((size_t)c,'S'); }
        out+=Z[i];
    }
    cout<<out<<endl;
}
