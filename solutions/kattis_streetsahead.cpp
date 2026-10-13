#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,q;cin>>n>>q;unordered_map<string,int>p;p.reserve(2*n);
 for(int i=0;i<n;i++){string s;cin>>s;p[s]=i;}
 while(q--){string a,b;cin>>a>>b;cout<<abs(p[a]-p[b])-1<<"\n";}}
