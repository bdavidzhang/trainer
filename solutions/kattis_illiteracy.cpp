#include <bits/stdc++.h>
using namespace std;
int enc(const int*a){int r=0;for(int i=0;i<8;i++)r=r*6+a[i];return r;}
int main(){string s,t;cin>>s>>t;int a[9],b[9];for(int i=0;i<8;i++){a[i]=s[i]-'A';b[i]=t[i]-'A';}
 int S=enc(a),T=enc(b);const int N=1679616;vector<int>d(N,-1);vector<int>q;q.reserve(N);q.push_back(S);d[S]=0;
 for(size_t h=0;h<q.size();h++){int u=q[h];if(u==T)break;int c[8];{int v=u;for(int i=7;i>=0;i--){c[i]=v%6;v/=6;}}
  for(int i=0;i<8;i++){int n[8];memcpy(n,c,sizeof n);int x=i+1;auto rot=[&](int pos){n[pos-1]=(n[pos-1]+1)%6;};
   switch(c[i]){
    case 0:if(x>1)rot(x-1);if(x<8)rot(x+1);break;
    case 1:if(x>1&&x<8)n[x]=c[x-2];break;
    case 2:rot(9-x);break;
    case 3:if(x<=4){for(int j=1;j<x;j++)rot(j);}else{for(int j=x+1;j<=8;j++)rot(j);}break;
    case 4:if(x>1&&x<8){int y=min(x-1,8-x);rot(x-y);rot(x+y);}break;
    case 5:if(x&1)rot((x+9)/2);else rot(x/2);break;}
   int v=enc(n);if(d[v]<0){d[v]=d[u]+1;q.push_back(v);}}}
 cout<<d[T]<<endl;}
