#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;scanf("%d %d",&n,&m);vector<int>p(n+1);iota(p.begin(),p.end(),0);
 while(m--){int a;scanf("%d",&a);swap(p[a],p[a+1]);}
 for(int i=1;i<=n;i++)printf("%d\n",p[i]);}
