#include <bits/stdc++.h>
using namespace std;
int main(){
    int t; scanf("%d",&t);
    while(t--){
        int n; scanf("%d",&n);
        vector<int> v(n);
        for(auto&x:v){ long long s; scanf("%lld",&s); int c=0; while(s%2==0){s/=2;c++;} x=c; }
        bool win;
        if(n%2==0){ win=false; for(int x:v) if(x>0) win=true; }
        else { win=false; for(int x:v) if(x!=v[0]) win=true; }
        puts(win?"1":"0");
    }
}
