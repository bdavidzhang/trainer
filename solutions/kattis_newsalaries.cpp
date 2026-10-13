#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
int main(){int n;scanf("%d",&n);vector<ld>L(n),R(n);
// events: (x, type, value): slope change or jump
vector<pair<ld,pair<int,ld>>> ev;ld sub=0;
for(int i=0;i<n;i++){double l,r;scanf("%lf %lf",&l,&r);L[i]=l;R[i]=r;
 if(r>l){ld sl=1.0L/(R[i]-L[i]);ev.push_back({L[i],{1,sl}});ev.push_back({R[i],{1,-sl}});sub+=(R[i]-L[i])/6;}
 else ev.push_back({L[i],{0,1}});}
sort(ev.begin(),ev.end(),[](const pair<ld,pair<int,ld>>&a,const pair<ld,pair<int,ld>>&b){return a.first<b.first;});
ld S=0,slope=0,tot=0;ld N=n;size_t i=0;ld prev=0;bool first=true;int active=0;
auto g=[&](ld s){if(s<0)s=0;if(s>N)s=N;return s*(N-s);};
while(i<ev.size()){ld x=ev[i].first;
 if(!first){ld d=x-prev;ld s1=S+slope*d;ld sm=S+slope*d/2;tot+=d*(g(S)+4*g(sm)+g(s1))/6;S=s1;}
 first=false;
 while(i<ev.size()&&ev[i].first==x){if(ev[i].second.first==0)S+=1;else{slope+=ev[i].second.second;active+=ev[i].second.second>0?1:-1;}i++;}
 if(active==0)slope=0;
 prev=x;}
ld ans=(tot-sub)/(N*N);printf("%.9Lf\n",ans);}
