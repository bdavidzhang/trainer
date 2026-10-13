#include <bits/stdc++.h>
using namespace std;
int w,h,q,sz;
vector<array<unsigned char,20>> t;
int main(){scanf("%d %d %d",&w,&h,&q);sz=1;while(sz<h)sz<<=1;
 array<unsigned char,20> id;for(int i=0;i<20;i++)id[i]=i;
 t.assign(2*sz,id);
 while(q--){int y,a,b;scanf("%d %d %d",&y,&a,&b);a--;b--;y--;
  int p=y+sz;
  if(t[p][a]==a){t[p][a]=b;t[p][b]=a;}else{t[p][a]=a;t[p][b]=b;}
  for(p>>=1;p>=1;p>>=1){auto&L=t[2*p];auto&R=t[2*p+1];auto&T=t[p];for(int i=0;i<w;i++)T[i]=R[L[i]];}
  auto&T=t[1];int cyc=0;bool vis[20]={};
  for(int i=0;i<w;i++)if(!vis[i]){cyc++;for(int j=i;!vis[j];j=T[j])vis[j]=1;}
  printf("%d\n",w-cyc);}
}
