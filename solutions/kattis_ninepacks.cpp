#include <bits/stdc++.h>
using namespace std;
const int M=100001,INF=1e9;
vector<int> go(){int k;scanf("%d",&k);vector<int>d(M,INF);d[0]=0;for(int i=0;i<k;i++){int x;scanf("%d",&x);for(int s=M-1;s>=x;s--)if(d[s-x]+1<d[s])d[s]=d[s-x]+1;}return d;}
int main(){auto a=go(),b=go();int best=INF;for(int s=1;s<M;s++)if(a[s]<INF&&b[s]<INF)best=min(best,a[s]+b[s]);if(best>=INF)puts("impossible");else printf("%d\n",best);}
