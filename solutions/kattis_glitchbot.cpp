#include <bits/stdc++.h>
using namespace std;
int main(){int x,y,n;cin>>x>>y>>n;vector<string>a(n);for(auto&s:a)cin>>s;
 const char* opt[3]={"Left","Right","Forward"};
 int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
 for(int i=0;i<n;i++)for(int k=0;k<3;k++){if(a[i]==opt[k])continue;string old=a[i];a[i]=opt[k];
  int px=0,py=0,d=0;for(auto&s:a){if(s[0]=='L')d=(d+3)%4;else if(s[0]=='R')d=(d+1)%4;else{px+=dx[d];py+=dy[d];}}
  a[i]=old;if(px==x&&py==y){cout<<i+1<<" "<<opt[k]<<"\n";return 0;}}
}
