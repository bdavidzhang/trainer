#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;int n=s.size();vector<int>r;
 for(int k=1;k<=n;k++){int a=0,b=0,wa=0,wb=0;for(char c:s){if(c=='A')a++;else b++;if(a==k){wa++;a=b=0;}else if(b==k){wb++;a=b=0;}}if(wa>wb)r.push_back(k);}
 printf("%d\n",(int)r.size());for(size_t i=0;i<r.size();i++)printf("%d%c",r[i],i+1<r.size()?' ':'\n');}
