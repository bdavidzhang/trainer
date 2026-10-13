#include <bits/stdc++.h>
using namespace std;
int main(){long long w,s,c,k;cin>>w>>s>>c>>k;long long a=s,b=w+c;long long mn=min(a,b),mx=max(a,b);
bool ok=false;if(mn<k)ok=true;else if(mn==k&&mx<=2*k)ok=true;puts(ok?"YES":"NO");}
