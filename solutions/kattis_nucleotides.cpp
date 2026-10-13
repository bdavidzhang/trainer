#include <bits/stdc++.h>
using namespace std;
int main(){string s;int m;cin>>s>>m;int n=s.size();const string L="ATGC";
 vector<array<int,4>> p(n+1);p[0]={0,0,0,0};
 for(int i=0;i<n;i++){p[i+1]=p[i];p[i+1][L.find(s[i])]++;}
 while(m--){int a,b;scanf("%d %d",&a,&b);int c[4];for(int k=0;k<4;k++)c[k]=p[b][k]-p[a-1][k];
  int id[4]={0,1,2,3};stable_sort(id,id+4,[&](int x,int y){return c[x]>c[y];});
  char o[5]={L[id[0]],L[id[1]],L[id[2]],L[id[3]],0};puts(o);}
}
