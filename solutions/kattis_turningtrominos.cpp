#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n;scanf("%d",&n);while(n--){ll x,y;scanf("%lld %lld",&x,&y);
// L_k: [0,2h)^2 minus [h,2h)^2, h=2^k. Built from L_{k-1} at origin, at offset (q,q), cw-rotated in top-left, ccw-rotated in bottom-right.
ll h=1LL<<61;int rot=0;
while(h>1){ll q=h/2;
 if(x>=q&&y>=q&&x<3*q&&y<3*q&&!(x>=h&&y>=h)){x-=q;y-=q;}
 else if(x<h&&y<h){}
 else if(y>=h){ll u=x,v=y-h;x=h-1-v;y=u;rot+=1;}
 else {ll u=x-h,v=y;x=v;y=h-1-u;rot+=3;}
 h=q;}
printf("%d\n",rot%4);}}
