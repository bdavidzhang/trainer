#include <bits/stdc++.h>
using namespace std;
int main(){
    vector<string> w; string t; while(cin>>t){ for(auto&c:t)c=tolower(c); w.push_back(t);} 
    int best=0; string ans;
    for(size_t i=0;i<w.size();){ size_t j=i; while(j<w.size()&&w[j]==w[i])j++; if((int)(j-i)>best){best=j-i;ans=w[i];} i=j; }
    cout<<ans<<"\n";
}
