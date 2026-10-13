#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<int> c(n); long long P=0; map<int,int> mult;
    for(auto&x:c){scanf("%d",&x);P+=x;mult[x]++;}
    // ln b = ln(365!/(365-n)!) - sum ln(m_k!) + ln(P!) - sum ln(c_i!) - P ln 365
    double r = lgamma(366.0)-lgamma(366.0-n)+lgamma(P+1.0)-P*log(365.0);
    for(auto&kv:mult) r-=lgamma(kv.second+1.0);
    for(int x:c) r-=lgamma(x+1.0);
    printf("%.12f\n", r/log(10.0));
}
