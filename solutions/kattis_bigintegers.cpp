#include <bits/stdc++.h>
using namespace std;
static int val(char c){if(c<='9')return c-'0';if(c>='a')return c-'a'+10;return c-'A'+36;}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int t;cin>>t;string a,b;
while(t--){cin>>a>>b;bool lexA=a<b;bool numA;
 if(a.size()!=b.size())numA=a.size()<b.size();
 else{size_t i=0;while(a[i]==b[i])i++;numA=val(a[i])<val(b[i]);}
 puts(lexA==numA?"YES":"NO");}}
