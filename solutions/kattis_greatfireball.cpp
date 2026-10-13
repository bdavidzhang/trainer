#include <bits/stdc++.h>
using namespace std;
int n,K;vector<double> ph,ds;vector<double> S,T;
const double PI=acos(-1.0);
bool check(double r){S.clear();T.clear();
 for(int i=0;i<n;i++){double c=ds[i]/(2*r);if(c>1)continue;double w=acos(c);double s=ph[i]-w,e=ph[i]+w;if(s<0){s+=2*PI;e+=2*PI;}
  S.push_back(s);T.push_back(e);S.push_back(s+2*PI);T.push_back(e+2*PI);}
 if((int)S.size()<2*K)return false;
 sort(S.begin(),S.end());sort(T.begin(),T.end());
 size_t i=0,j=0;int cnt=0;
 while(i<S.size()){if(S[i]<=T[j]){cnt++;i++;if(cnt>=K)return true;}else{cnt--;j++;}}
 return false;}
int main(){scanf("%d %d",&n,&K);ph.resize(n);ds.resize(n);
 for(int i=0;i<n;i++){int x,y;scanf("%d %d",&x,&y);ph[i]=atan2((double)y,(double)x);ds[i]=sqrt((double)x*x+(double)y*y);}
 double lo=0.4,hi=1e10;
 if(!check(hi)){puts("-1");return 0;}
 for(int it=0;it<70;it++){double m=sqrt(lo*hi);if(check(m))hi=m;else lo=m;}
 printf("%.7f\n",hi);}
