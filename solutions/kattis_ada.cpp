#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; cin>>n; vector<long long> v(n); for(auto&x:v)cin>>x;
    long long sum=0; int d=0;
    while(true){
        sum+=v.back();
        bool same=true; for(size_t i=1;i<v.size();i++)if(v[i]!=v[0])same=false;
        if(same)break;
        for(size_t i=0;i+1<v.size();i++)v[i]=v[i+1]-v[i];
        v.pop_back(); d++;
    }
    cout<<d<<" "<<sum<<endl;
}
