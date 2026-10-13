#include <bits/stdc++.h>
using namespace std;
int n;int v[102][102];bool k[102][102];
int main(){scanf("%d",&n);bool bad=false;
 for(int i=0;i<n;i++)for(int j=0;j<=i;j++){scanf("%d",&v[i][j]);k[i][j]=v[i][j]!=100;}
 // triple (i,j): v[i][j]=v[i+1][j]+v[i+1][j+1]
 bool ch=true;
 auto setv=[&](int i,int j,int x){v[i][j]=x;k[i][j]=true;ch=true;if(x<-99||x>99)bad=true;};
 while(ch&&!bad){ch=false;
  for(int i=0;i<n-1&&!bad;i++)for(int j=0;j<=i&&!bad;j++){
    int c=k[i][j]+k[i+1][j]+k[i+1][j+1];
    if(c==3){if(v[i][j]!=v[i+1][j]+v[i+1][j+1])bad=true;}
    else if(c==2){if(!k[i][j])setv(i,j,v[i+1][j]+v[i+1][j+1]);else if(!k[i+1][j])setv(i+1,j,v[i][j]-v[i+1][j+1]);else setv(i+1,j+1,v[i][j]-v[i+1][j]);}
  }}
 if(!bad)for(int i=0;i<n-1;i++)for(int j=0;j<=i;j++)if(k[i][j]&&k[i+1][j]&&k[i+1][j+1]&&v[i][j]!=v[i+1][j]+v[i+1][j+1])bad=true;
 if(bad){puts("no solution");return 0;}
 for(int i=0;i<n;i++)for(int j=0;j<=i;j++)if(!k[i][j]){puts("ambiguous");return 0;}
 puts("solvable");for(int i=0;i<n;i++){for(int j=0;j<=i;j++)printf("%d ",v[i][j]);puts("");}}
