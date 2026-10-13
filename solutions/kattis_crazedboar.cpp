#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
int main(){int n;scanf("%d",&n);vector<array<long long,3>>t(n);for(auto&e:t)scanf("%lld %lld %lld",&e[0],&e[1],&e[2]);long long b,d;scanf("%lld %lld",&b,&d);
 const ld PI=acosl(-1.0L);vector<pair<ld,ld>>iv;
 for(auto&e:t){long long R=e[2]+b;long long D2=e[0]*e[0]+e[1]*e[1];ld D=sqrtl((ld)D2);
  if(d==0)continue;   if((__int128)(d+R)*(d+R)<=(__int128)D2)continue;
  ld h;long long tan2=D2-R*R; if(d*d>=tan2)h=asinl(min((ld)1,R/D));else{ld c=((ld)d*d+(ld)tan2)/(2*(ld)d*D);c=max((ld)-1,min((ld)1,c));h=acosl(c);}
  ld a=atan2l((ld)e[1],(ld)e[0]);ld lo=a-h,hi=a+h;
  if(lo<-PI){iv.push_back({lo+2*PI,PI});iv.push_back({-PI,hi});}else if(hi>PI){iv.push_back({lo,PI});iv.push_back({-PI,hi-2*PI});}else iv.push_back({lo,hi});}
 sort(iv.begin(),iv.end());ld tot=0,cs=0,ce=0;bool has=false;for(auto&p:iv){if(!has){cs=p.first;ce=p.second;has=true;}else if(p.first<=ce)ce=max(ce,p.second);else{tot+=ce-cs;cs=p.first;ce=p.second;}}
 if(has)tot+=ce-cs;printf("%.10Lf\n",max((ld)0,1-tot/(2*PI)));}
