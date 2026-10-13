#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;int m=n-1;vector<pair<double,double>>p(m);for(auto&q:p)cin>>q.first>>q.second;
 sort(p.begin(),p.end(),[](const pair<double,double>&a,const pair<double,double>&b){return atan2(a.second,a.first)<atan2(b.second,b.first);});
 vector<double> w(m,0);double tot=0;
 for(int i=0;i<m;i++){int j=(i+1)%m;double ar=fabs(p[i].first*p[j].second-p[i].second*p[j].first)/2;w[i]+=ar;w[j]+=ar;tot+=ar;}
 w.push_back(tot);vector<double>h(n);for(auto&v:h)cin>>v;
 sort(w.begin(),w.end());sort(h.begin(),h.end());double a=0;for(int i=0;i<n;i++)a+=w[i]*h[i];
 printf("%.6f\n",a/3);}
