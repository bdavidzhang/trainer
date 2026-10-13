#include <bits/stdc++.h>
using namespace std;
int main(){long long n;int t;long long a,b;scanf("%lld %d %lld %lld",&n,&t,&a,&b);
const long long INF=1e18;
// state: direction 0=up,1=down; position: currently "at stop a" => treat as up at segment a (needs s>=a), down at segment a-1 (needs s<=a-1)
long long d[2]={0,0};long long pos[2]={a,a-1};
for(int i=0;i<t;i++){long long s;scanf("%lld",&s);long long nd[2]={INF,INF};
 // to up
 nd[0]=min(d[0]+(s>=pos[0]?0:2),d[1]+1);
 nd[1]=min(d[1]+(s<=pos[1]?0:2),d[0]+1);
 d[0]=nd[0];d[1]=nd[1];pos[0]=pos[1]=s;}
long long ans=min(d[0]+(b>=pos[0]+1?0:1),d[1]+(b<=pos[1]?0:1));
printf("%lld\n",ans);}
