#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; cin>>n;
    vector<string> nm(n); vector<long long> S(n),E(n);
    for(int i=0;i<n;i++){
        int s; cin>>nm[i]>>s;
        map<string,long long> fin; long long sum=0,mx=0;
        for(int j=0;j<s;j++){
            string a; long long t; int d; cin>>a>>t>>d;
            long long st=0;
            for(int k=0;k<d;k++){ string b; cin>>b; st=max(st,fin[b]); }
            fin[a]=st+t; sum+=t; mx=max(mx,st+t);
        }
        S[i]=sum; E[i]=mx;
    }
    vector<int> id(n); iota(id.begin(),id.end(),0);
    stable_sort(id.begin(),id.end(),[&](int a,int b){ return S[a]*E[b] < S[b]*E[a]; });
    for(int i:id) cout<<nm[i]<<"\n";
}
