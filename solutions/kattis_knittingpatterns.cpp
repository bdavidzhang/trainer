#include <bits/stdc++.h>
using namespace std;

int main(){
    long long a,b,c; cin>>a>>b>>c;
    string w,p; cin>>w>>p;
    vector<long long> cost(26,0); vector<int> last(26,-1);
    for(int i=0;i<(int)p.size();i++){
        int ch=p[i]-'a';
        if(last[ch]<0) cost[ch]+=2*c; // one start and one final stop
        else cost[ch]+=min(a*(i-last[ch]-1),2*c); // strand through the gap, or cut and restart
        cost[ch]+=b; last[ch]=i;
    }
    for(char ch:w) cout<<cost[ch-'a']<<"\n";
}
