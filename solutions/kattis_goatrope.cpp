#include <bits/stdc++.h>
using namespace std;
int main(){double x,y,x1,y1,x2,y2;cin>>x>>y>>x1>>y1>>x2>>y2;double dx=max({x1-x,0.0,x-x2}),dy=max({y1-y,0.0,y-y2});printf("%.6f\n",sqrt(dx*dx+dy*dy));}
