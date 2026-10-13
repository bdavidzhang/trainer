#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);while(n--){int g;scanf("%d",&g);vector<int> a(g);for(auto&x:a)scanf("%d",&x);int ans=0;for(int i=1;i<g;i++)if(a[i]!=a[i-1]+1){ans=i+1;break;}printf("%d\n",ans);}}
