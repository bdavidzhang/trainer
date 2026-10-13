#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
// S sorted, downward closed. returns f aligned with S, f a permutation of S with S[i]&f[i]==0
vector<ull> solve(const vector<ull>& S){
    if(S.size()==1) return {0ULL};
    ull mx=S.back();
    ull bit=1ULL<<(63-__builtin_clzll(mx));
    size_t c=lower_bound(S.begin(),S.end(),bit)-S.begin();
    vector<ull> S0(S.begin(),S.begin()+c), S1(S.begin()+c,S.end());
    for(auto&x:S1)x-=bit;
    vector<ull> f1=solve(S1);
    vector<ull> f0=solve(S0);
    vector<ull> f(S.size());
    for(size_t i=0;i<c;i++){
        ull v=f0[i];
        if(binary_search(S1.begin(),S1.end(),v)) v+=bit;
        f[i]=v;
    }
    for(size_t j=0;j<S1.size();j++) f[c+j]=f1[j];
    return f;
}
int main(){
    int n; scanf("%d",&n);
    vector<ull> a(n); for(auto&x:a)scanf("%llu",&x);
    vector<ull> S=a; sort(S.begin(),S.end());
    vector<ull> f=solve(S);
    for(int i=0;i<n;i++){
        size_t p=lower_bound(S.begin(),S.end(),a[i])-S.begin();
        printf("%llu\n",f[p]);
    }
}
