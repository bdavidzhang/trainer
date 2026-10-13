#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef __int128 LL;
int main(){int n;scanf("%d",&n);
 vector<pair<ll,ll>> A(n),B(n);ll sax=0,say=0,sbx=0,sby=0;
 for(auto&p:A){scanf("%lld %lld",&p.first,&p.second);sax+=p.first;say+=p.second;}
 for(auto&p:B){scanf("%lld %lld",&p.first,&p.second);sbx+=p.first;sby+=p.second;}
 ll dx=sbx-sax,dy=sby-say;
 if(dx==0&&dy==0){puts("impossible");return 0;}
 ll g=std::gcd(llabs(dx),llabs(dy));dx/=g;dy/=g; // direction A->B, primitive
 sort(B.begin(),B.end());
 // mirror: (P-M).d=0, M=(SA+SB)/(2n). num = 2n*P.d - (SA+SB).d ; (P-M).d = num/(2n)
 LL c=(LL)(sax+sbx)*dx+(LL)(say+sby)*dy; LL dd=(LL)dx*dx+(LL)dy*dy;
 for(auto&p:A){
   LL num=(LL)2*n*((LL)p.first*dx+(LL)p.second*dy)-c;
   if(num>=0){puts("impossible");return 0;}
   // P' = P - 2*(num/(2n))/dd * d = P - num*d/(n*dd)
   LL den=(LL)n*dd; LL ax=num*dx, ay=num*dy;
   if(ax%den!=0||ay%den!=0){puts("impossible");return 0;}
   ll rx=(ll)(p.first-ax/den), ry=(ll)(p.second-ay/den);
   if(!binary_search(B.begin(),B.end(),make_pair(rx,ry))){puts("impossible");return 0;}
 }
 puts("possible");
}
