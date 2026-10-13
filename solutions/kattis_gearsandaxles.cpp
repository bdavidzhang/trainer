#include <bits/stdc++.h>
using namespace std;
int main(){int n;if(scanf("%d",&n)!=1)n=0;vector<vector<int>> g(100001);
 for(int i=0;i<n;i++){int s,c;scanf("%d %d",&s,&c);g[s].push_back(c);}
 double r=0;
 for(auto&v:g){sort(v.begin(),v.end());int k=v.size();for(int i=0;i<k/2;i++)r+=log((double)v[k-1-i])-log((double)v[i]);}
 printf("%.10f\n",r);}
