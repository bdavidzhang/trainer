#include <bits/stdc++.h>
using namespace std;
// W half-lengths wide, H layers tall; layer k may hold bricks with right edge x<=W*(H-k-1)/H
long long calc(long long W,long long H,int par){long long c=0;
 for(long long k=0;k<H;k++){long long num=W*(H-k-1); // maxx = num/H
  if(((k&1)^par)==0) c+=num/(2*H);
  else if(num>=H) c+=(num-H)/(2*H);}
 return c;}
int main(){long long a,b;cin>>a>>b;long long r=0;for(int p=0;p<2;p++){r=max(r,calc(a,b,p));r=max(r,calc(b,a,p));}cout<<r<<endl;}
