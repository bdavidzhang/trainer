#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;map<string,string>own={{"fishing","alice"},{"golf","bob"},{"hockey","charlie"}};
 while(n--){string a,w,t,pl,b;cin>>a>>w>>t>>pl>>b;
  if(own[b]==a)cout<<a<<" already has "<<b<<"\n"; else {cout<<a<<" borrows "<<b<<" from "<<own[b]<<"\n";own[b]=a;}}}
