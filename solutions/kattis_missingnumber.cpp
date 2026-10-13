#include <bits/stdc++.h>
using namespace std;
int main(){int n;string s;cin>>n>>s;size_t p=0;for(int i=1;i<=n;i++){string t=to_string(i);
if(s.compare(p,t.size(),t)==0)p+=t.size();else{printf("%d\n",i);return 0;}}
printf("%d\n",n);}
