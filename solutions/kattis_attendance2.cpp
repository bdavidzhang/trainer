#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;vector<string>s(n);for(auto&x:s)cin>>x;bool any=false;
for(int i=0;i<n;i++){if(s[i]=="Present!")continue;if(i+1<n&&s[i+1]=="Present!")continue;cout<<s[i]<<"\n";any=true;}
if(!any)cout<<"No Absences\n";}
