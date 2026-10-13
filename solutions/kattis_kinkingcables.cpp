#include <bits/stdc++.h>
using namespace std;
int main(){int n,m;double L;scanf("%d %d %lf",&n,&m,&L);
 // snake: rows y=0..R, alternating direction, ends at (n,m)
 vector<pair<double,double>>S;int R=(m%2==0)?m:m-1;
 for(int y=0;y<=R;y++){if(y%2==0){S.push_back({0,y});S.push_back({n,y});}else{S.push_back({n,y});S.push_back({0,y});}}
 if(R<m)S.push_back({n,m});
 int k=S.size();vector<double>pre(k,0);for(int i=1;i<k;i++)pre[i]=pre[i-1]+hypot(S[i].first-S[i-1].first,S[i].second-S[i-1].second);
 auto pt=[&](double s,int&idx){idx=int(upper_bound(pre.begin(),pre.end(),s)-pre.begin())-1;if(idx>=k-1){idx=k-1;return S[k-1];}
  double t=(s-pre[idx])/(pre[idx+1]-pre[idx]);return make_pair(S[idx].first+t*(S[idx+1].first-S[idx].first),S[idx].second+t*(S[idx+1].second-S[idx].second));};
 auto f=[&](double s){int idx;auto p=pt(s,idx);return s+hypot(n-p.first,m-p.second);};
 double lo=0,hi=pre[k-1];for(int it=0;it<200;it++){double mid=(lo+hi)/2;if(f(mid)<L)lo=mid;else hi=mid;}
 int idx;auto X=pt(hi,idx);vector<pair<double,double>>P;
 for(int i=0;i<=idx;i++)P.push_back(S[i]);
 auto far=[&](pair<double,double>a,pair<double,double>b){return hypot(a.first-b.first,a.second-b.second)>1e-7;};
 if(far(X,P.back())){ if(idx+1<k&&!far(X,S[idx+1]))P.push_back(S[idx+1]);else P.push_back(X);}
 if(far(P.back(),{(double)n,(double)m}))P.push_back({n,m});
 printf("%d\n",(int)P.size());for(auto&p:P)printf("%.10f %.10f\n",p.first,p.second);}
