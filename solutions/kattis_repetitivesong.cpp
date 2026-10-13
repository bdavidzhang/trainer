#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n;cin>>n;unordered_map<string,int>last;int best=INT_MAX;
 for(int i=0;i<n;i++){string s;cin>>s;auto it=last.find(s);if(it!=last.end()){best=min(best,i-it->second);it->second=i;}else last[s]=i;}
 cout<<(best==INT_MAX?0:n-best)<<"\n";}
