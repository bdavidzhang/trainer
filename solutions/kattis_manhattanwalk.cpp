#include <bits/stdc++.h>
using namespace std;
int main(){int r,c;double p;cin>>r>>c>>p;vector<vector<double>> E(r,vector<double>(c,0));
 for(int i=r-1;i>=0;i--)for(int j=c-1;j>=0;j--){
  if(i==r-1&&j==c-1)continue;
  if(i==r-1){E[i][j]=E[i][j+1]+p/4;continue;}
  if(j==c-1){E[i][j]=E[i+1][j]+p/4;continue;}
  double A=min(E[i+1][j],E[i][j+1]),B=max(E[i+1][j],E[i][j+1]),d=B-A;
  double w=d>=p?p/2:(d*d/2+d*(p-d))/p;
  E[i][j]=A+w/2;}
 printf("%.9f\n",E[0][0]);}
