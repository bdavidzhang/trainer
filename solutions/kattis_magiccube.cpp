#include <bits/stdc++.h>
using namespace std;
int main(){long long n;int m;scanf("%lld %d",&n,&m);
 vector<array<int,3>> ops; // axis, times, k
 for(int i=0;i<m;i++){char c;scanf(" %c",&c);
  if(c=='q'){long long p[3];scanf("%lld %lld %lld",&p[0],&p[1],&p[2]);
   for(int j=(int)ops.size()-1;j>=0;j--){int ax=ops[j][0],t=ops[j][1],k=ops[j][2];
    if(p[ax]<=k)continue;
    // forward 90 about axis ax with (a,b)=(ax+1,ax+2): a'=b, b'=n+1-a ; inverse = 3x forward per step
    int a=(ax+1)%3,b=(ax+2)%3;int inv=(4-t)%4;
    for(int r=0;r<inv;r++){long long na=p[b],nb=n+1-p[a];p[a]=na;p[b]=nb;}
   }
   printf("%lld\n",p[0]+(p[1]-1)*n+(p[2]-1)*n*n);
  } else {int th,k;scanf("%d %d",&th,&k);ops.push_back({c-'x',(th/90)%4,k});}
 }}
