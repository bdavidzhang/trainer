#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;int n=s.size();
 if(n%2){puts("impossible");return 0;}
 // T[i]: sum of suffix i.., M[i]: min prefix sum of suffix i.. (including empty =0)
 vector<int>T(n+2,0),M(n+2,0);
 for(int i=n-1;i>=0;i--){int v=s[i]=='('?1:-1;T[i]=v+T[i+1];M[i]=min(0,v+M[i+1]);}
 if(T[0]==0&&M[0]>=0){puts("possible");return 0;}
 int pre=0;
 for(int l=0;l<n;l++){
  int b=pre;
  for(int r=l;r<n;r++){
   b+=(s[r]=='('?-1:1);
   if(b<0)break;
   if(b+T[r+1]==0&&b+M[r+1]>=0){puts("possible");return 0;}
  }
  pre+=(s[l]=='('?1:-1);
  if(pre<0)break;
 }
 puts("impossible");
}
