#include <bits/stdc++.h>
using namespace std;
int h,w;vector<string>g;vector<int>st;
bool check(int k){
 for(int i=0;i<h;i++)for(int j=0;j<w;j++){
  if(g[i][j]!='#'||st[i*w+j]==k)continue;
  if(i+k>h||j+k>w)return false;
  for(int a=i;a<i+k;a++){int*row=&st[a*w];const string&gr=g[a];
   for(int b=j;b<j+k;b++){if(gr[b]!='#'||row[b]==k)return false;row[b]=k;}}
  j+=k-1;
 }
 return true;
}
int main(){cin>>h>>w;g.resize(h);for(auto&s:g)cin>>s;st.assign(h*w,0);
 int G=0;
 for(int i=0;i<h;i++){int run=0;for(int j=0;j<=w;j++){if(j<w&&g[i][j]=='#')run++;else{if(run)G=gcd(G,run);run=0;}}}
 for(int j=0;j<w;j++){int run=0;for(int i=0;i<=h;i++){if(i<h&&g[i][j]=='#')run++;else{if(run)G=gcd(G,run);run=0;}}}
 for(int k=G;k>=1;k--){if(G%k)continue;if(check(k)){printf("%d\n",k);return 0;}}
}
