#include <bits/stdc++.h>
using namespace std;
int n,m,c[105];int cap[205];int memo[105][105];
int f(int i,int k){if(i>=n)return 0;int&r=memo[i][k];if(r>=0)return r;
 r=min(c[i],cap[k])+f(i+1,k+1);
 // skip one, then eat at i+1
 if(i+1<n){int k2=max(k-1,0);r=max(r,min(c[i+1],cap[k2])+f(i+2,k2+1));}
 r=max(r,f(i+2,0));
 return r;}
int main(){cin>>n>>m;for(int i=0;i<n;i++)cin>>c[i];cap[0]=m;for(int i=1;i<205;i++)cap[i]=cap[i-1]*2/3;
 memset(memo,-1,sizeof memo);cout<<f(0,0)<<endl;}
