#include <bits/stdc++.h>
using namespace std;
int main(){int n,m,s,p,q;cin>>n>>m>>s>>p>>q;vector<int>a(n,0),b(n,0);
 for(int i=0;i<p;i++){int x;cin>>x;a[x-1]=1;}
 for(int i=0;i<q;i++){int x;cin>>x;b[x-1]=1;}
 int pages=(n+m-1)/m;long long tot=0;int L=-1,R=-1;
 for(int g=0;g<pages;g++){int d=0,w=0,sz=0;
  for(int i=g*m;i<min(n,(g+1)*m);i++){sz++;d+=a[i]!=b[i];w+=b[i];}
  int c=min(d,1+min(w,sz-w));
  if(c>0){tot+=c;if(L<0)L=g+1;R=g+1;}}
 if(L>0)tot+=R-L+min(abs(s-L),abs(s-R));
 cout<<tot<<endl;}
