#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;cin>>n;vector<int> t(n);for(auto&x:t)cin>>x;
    unsigned long long total=1;for(int x:t)total*=x;
    // count valid strings for which every single-digit deletion stays valid
    array<unsigned long long,10> dp{};dp[0]=1; // state: previous digit (D[2i-1]), D[-1]=0
    for(int i=0;i<n;i++){
        array<unsigned long long,10> nd{};
        for(int p=0;p<10;p++)if(dp[p])for(int a=0;a<10;a++)for(int b=0;b<10;b++){
            if(a*10+b<t[i]&&p*10+a<t[i]&&p*10+b<t[i])nd[b]+=dp[p];
        }
        dp=nd;
    }
    unsigned long long good=0;for(auto x:dp)good+=x;
    cout<<total-good<<"\n";
}
