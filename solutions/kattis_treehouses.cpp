#include <bits/stdc++.h>
using namespace std;
int p[1005];int f(int x){return p[x]==x?x:p[x]=f(p[x]);}
int main(){int n,e,q;scanf("%d %d %d",&n,&e,&q);vector<double>x(n),y(n);for(int i=0;i<n;i++){scanf("%lf %lf",&x[i],&y[i]);p[i]=i;}
 for(int i=1;i<e;i++)p[f(i)]=f(0);
 for(int i=0;i<q;i++){int a,b;scanf("%d %d",&a,&b);p[f(a-1)]=f(b-1);}
 vector<tuple<double,int,int>>ed;ed.reserve(n*(n-1)/2);
 for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)ed.emplace_back((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]),i,j);
 sort(ed.begin(),ed.end());double r=0;
 for(auto&[d,a,b]:ed){int u=f(a),v=f(b);if(u!=v){p[u]=v;r+=sqrt(d);}}
 printf("%.6f\n",r);}
