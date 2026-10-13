#include <bits/stdc++.h>
using namespace std;
int main(){int n,m,k;scanf("%d %d %d",&n,&m,&k);vector<int>st(m+1,0);vector<long long>c(m+1,0);
 while(k--){int p,x;scanf("%d %d",&p,&x);if(!st[x])st[x]=p;else{c[x]+=st[x]==p?100:abs(st[x]-p);st[x]=0;}}
 for(int i=1;i<=m;i++){if(st[i])c[i]+=100;printf("%lld%c",c[i],i==m?'\n':' ');}}
