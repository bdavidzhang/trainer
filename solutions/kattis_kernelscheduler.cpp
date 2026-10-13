#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;scanf("%d %d",&n,&m);vector<int>f,g;for(int i=1;i<=m;i++){int a,b;scanf("%d %d",&a,&b);(a<b?f:g).push_back(i);}
 if(g.size()>f.size())f.swap(g);printf("YES\n%d\n",(int)f.size());for(size_t i=0;i<f.size();i++)printf("%d%c",f[i],i+1==f.size()?'\n':' ');}
