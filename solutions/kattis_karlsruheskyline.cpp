#include <bits/stdc++.h>
using namespace std;
int main(){int n,a,b;cin>>n>>a>>b;if(a+b>n+1||(a==1&&b==1)){puts("no");return 0;}
 vector<int> r;int s=n-a-b+1; // small hidden values 1..s
 for(int v=n-a+1;v<=n-1;v++)r.push_back(v);
 if(b>=2){r.push_back(n);for(int v=1;v<=s;v++)r.push_back(v);for(int v=n-a;v>=s+1;v--)r.push_back(v);}
 else{for(int v=1;v<=s;v++)r.push_back(v);r.push_back(n);}
 puts("yes");for(int i=0;i<n;i++)printf("%d%c",r[i],i+1<n?' ':'\n');}
