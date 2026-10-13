#include <bits/stdc++.h>
using namespace std;
int main(){
    int k; cin>>k; map<long long,long long> c;
    for(int i=0;i<k;i++){ long long v; cin>>v; c[v]++; }
    long long n; cin>>n; if(n>0) c[0]+=3*n;
    vector<long long> out;
    while(!c.empty()){
        auto it=c.begin(); long long v=it->first,x=it->second; c.erase(it);
        if(x&1) out.push_back(v);
        if(x/2) c[v+1]+=x/2;
    }
    for(size_t i=0;i<out.size();i++) printf("%s%lld",i?" ":"",out[i]);
    puts("");
}
