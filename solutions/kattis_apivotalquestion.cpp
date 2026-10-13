#include <bits/stdc++.h>
using namespace std;
int main(){int n;if(scanf("%d",&n)!=1)return 0;vector<int>a(n),sm(n+1,INT_MAX);for(auto&x:a)scanf("%d",&x);
 for(int i=n-1;i>=0;i--)sm[i]=min(sm[i+1],a[i]);
 int mx=0,m=0;vector<int>r;for(int i=0;i<n;i++){if(mx<a[i]&&sm[i+1]>a[i]){m++;if(r.size()<100)r.push_back(a[i]);}mx=max(mx,a[i]);}
 printf("%d",m);for(int x:r)printf(" %d",x);puts("");}
