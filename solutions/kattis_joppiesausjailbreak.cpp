#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){int n;ll f;scanf("%d %lld",&n,&f);map<int,int> cnt;for(int i=0;i<n;i++){int l;scanf("%d",&l);cnt[l]++;}
 ll S=0;vector<pair<double,int>> ev;
 for(auto&pr:cnt){ll l=pr.first,c=pr.second;S+=c*((l*f+999)/1000);
  ll km=(l*f-1)/1000; // frame time l/(1000k) strictly above 1/f
  for(ll k=1;k<=km;k++)ev.push_back({(double)l/(1000.0*k),(int)c});}
 sort(ev.begin(),ev.end());
 double best=(double)S/f;
 for(size_t i=0;i<ev.size();){size_t j=i;while(j<ev.size()&&ev[j].first==ev[i].first){S-=ev[j].second;j++;}
  best=min(best,ev[i].first*S);i=j;}
 printf("%.9f\n",best);}
