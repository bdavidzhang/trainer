#include <bits/stdc++.h>
using namespace std;
int main(){ int k; cin>>k; int best=INT_MAX; while(k--){int y,a,b;cin>>y>>a>>b; best=min(best,y+a/std::gcd(a,b)*b);} cout<<best<<endl; }
