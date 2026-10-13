#include <bits/stdc++.h>
using namespace std;
int main(){long long a,b,c,d;cin>>a>>b>>c>>d;int N=min(b,d);vector<signed char>mu(N+1,0);vector<bool>comp(N+1,false);vector<int>pr;mu[1]=1;
 for(int i=2;i<=N;i++){if(!comp[i]){pr.push_back(i);mu[i]=-1;}for(int p:pr){long long v=(long long)i*p;if(v>N)break;comp[v]=true;if(i%p==0){mu[v]=0;break;}mu[v]=-mu[i];}}
 long long r=0;for(int k=1;k<=N;k++)if(mu[k])r+=mu[k]*(b/k-(a-1)/k)*(d/k-(c-1)/k);
 cout<<r<<endl;}
