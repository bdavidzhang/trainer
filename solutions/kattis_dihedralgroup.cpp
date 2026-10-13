#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;scanf("%d %d",&n,&m);vector<int> d(n),t(m);for(auto&x:d)scanf("%d",&x);for(auto&x:t)scanf("%d",&x);
 int pos=-1;for(int i=0;i<n;i++)if(d[i]==t[0])pos=i;
 bool a=true,b=true;
 for(int k=0;k<m;k++){if(d[(pos+k)%n]!=t[k])a=false;if(d[((pos-k)%n+n)%n]!=t[k])b=false;}
 printf("%d\n",(a||b)?1:0);}
