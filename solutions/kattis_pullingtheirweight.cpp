#include <bits/stdc++.h>
using namespace std;

int main(){int m;scanf("%d",&m);const int W=20001;vector<long long>s(W+2,0);long long tot=0;for(int i=0;i<m;i++){int w;scanf("%d",&w);s[w]+=w;tot+=w;}
long long lo=0;for(int t=1;t<=W;t++){long long hi=tot-lo-s[t];if(lo==hi){printf("%d\n",t);return 0;}lo+=s[t];}
return 0;}
