#include <bits/stdc++.h>
using namespace std;
int main(){ int t; cin>>t; while(t--){ string a,b; cin>>a>>b; bool ok=true; for(char c:b) if(a.find(c)==string::npos) ok=false; puts(ok?"YES":"NO"); } }
