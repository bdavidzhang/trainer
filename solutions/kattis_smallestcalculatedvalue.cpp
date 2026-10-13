#include <bits/stdc++.h>
using namespace std;
bool ap(long long x,long long y,int op,long long&r){
    if(op==0)r=x+y;else if(op==1)r=x-y;else if(op==2)r=x*y;
    else{ if(y==0||x%y!=0)return false; r=x/y;}
    return true;}
int main(){long long a,b,c;cin>>a>>b>>c;long long best=LLONG_MAX;
 for(int i=0;i<4;i++)for(int j=0;j<4;j++){long long r,s;
  if(!ap(a,b,i,r))continue; if(!ap(r,c,j,s))continue; if(s>=0)best=min(best,s);}
 cout<<best<<"\n";}
