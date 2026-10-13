#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){ll ju[10],jr[10],u[10],r[10],s[10];
 for(int i=0;i<10;i++)cin>>ju[i]>>jr[i];
 for(int i=0;i<10;i++)cin>>u[i]>>r[i]>>s[i];
 ll T=0;
 for(int rep=0;rep<3;rep++)for(int i=0;i<10;i++){
  ll start,nxt;
  if(T<s[i]){start=T;nxt=s[i];}
  else{ll p=u[i]+r[i];ll k=(T-s[i])/p;ll cs=s[i]+k*p;
   start=(T<cs+u[i])?cs+u[i]:T;nxt=cs+p;}
  ll en=start+ju[i];
  s[i]=max(nxt,en);
  T=en+jr[i];
  if(rep==2&&i==9){cout<<en<<endl;}
 }
}
