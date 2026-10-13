#include <bits/stdc++.h>
using namespace std;
int main(){ int t; cin>>t; while(t--){ int a[5],b[5]; for(int&x:a)cin>>x; for(int&x:b)cin>>x; bool ok=false; for(int i=0;i<5;i++)for(int j=0;j<5;j++) if(i!=j&&a[i]==b[j]) ok=true; puts(ok?"YES":"NO"); } }
