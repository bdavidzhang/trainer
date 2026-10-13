#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;double best=-1;
 for(int i=0;i<n;i++){double a,b,c,d;cin>>a>>b>>c>>d;
  if((a<0)==(c<0))continue;
  double y=b+(d-b)*(0-a)/(c-a);
  if(y>0&&(best<0||y<best))best=y;}
 if(best<0)printf("-1.0\n");else printf("%.10f\n",best);}
