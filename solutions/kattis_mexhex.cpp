#include <bits/stdc++.h>
using namespace std;
int main(){int n;long long d;scanf("%d %lld",&n,&d);vector<vector<int>>pos(n+1);
 for(int i=1;i<=n;i++){int p;scanf("%d",&p);pos[p].push_back(i);}
 for(int m=0;m<=n;m++){auto&q=pos[m];bool ok=true;long long prevS=LLONG_MIN/4;size_t i=0;
  while(i<q.size()&&ok){size_t j=i;while(j+1<q.size()&&q[j+1]-q[j]<d)j++;
   if(j+1<q.size()&&q[j+1]-q[j]==d){ok=false;break;}
   long long s=max<long long>({(long long)q[j]-d+1,prevS+2*d,1LL});
   if(s>q[i]){ok=false;break;}
   prevS=s;i=j+1;}
  if(ok){printf("%d\n",m);return 0;}}
}
