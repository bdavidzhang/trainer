#include <bits/stdc++.h>
using namespace std;
int main(){int P,D;scanf("%d %d",&P,&D);vector<long long>a(D+1),b(D+1);for(int i=0;i<P;i++){int d,x,y;scanf("%d %d %d",&d,&x,&y);a[d]+=x;b[d]+=y;}
 long long V=0,wa=0,wb=0;for(int d=1;d<=D;d++){long long t=a[d]+b[d],need=t/2+1,x,y;V+=t;if(a[d]>b[d]){x=a[d]-need;y=b[d];printf("A %lld %lld\n",x,y);}else{x=a[d];y=b[d]-need;printf("B %lld %lld\n",x,y);}wa+=x;wb+=y;}
 printf("%.10f\n",(double)llabs(wa-wb)/V);}
