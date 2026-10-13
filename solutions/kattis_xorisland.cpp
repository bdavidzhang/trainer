#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<int>a(n);for(auto&x:a)scanf("%d",&x);
 static int partner[25][25];
 for(int h=0;h<n;h++)for(int i=0;i<n;i++){int m=0;if(i!=h)for(int j=0;j<n;j++)if(j!=h&&j!=i&&(a[h]^a[i])==a[j])m|=1<<j;partner[h][i]=m;}
 vector<uint64_t>ok(((size_t)1<<n)/64+1,0);ok[0]|=1;int best=0;
 for(int h=0;h<n;h++){unsigned lo=1u<<h;for(unsigned rest=0;rest<lo;rest++){if(!(ok[rest>>6]>>(rest&63)&1))continue;
   bool good=true;unsigned m=rest;while(m){int i=__builtin_ctz(m);m&=m-1;if(partner[h][i]&rest){good=false;break;}}
   if(good){unsigned S=rest|lo;ok[S>>6]|=1ULL<<(S&63);int c=__builtin_popcount(S);if(c>best)best=c;}}}
 printf("%d\n",n-best);}
