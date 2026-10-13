#include <bits/stdc++.h>
using namespace std;
map<array<int,3>,double> memo;
double E(int a,int b,int c){ if(a<b)swap(a,b); if(b<c)swap(b,c); if(a<b)swap(a,b);
 if(c==0) return 3.0*b;
 array<int,3>k={a,b,c}; auto it=memo.find(k); if(it!=memo.end())return it->second;
 double r=1.5+0.5*(E(a+1,b,c-1)+E(a,b+1,c-1)); memo[k]=r; return r;}
int main(){int n;string s;cin>>n>>s;int c[3]={0,0,0};for(char ch:s)c[ch=='r'?0:ch=='g'?1:2]++;
 printf("%.9f\n",E(c[0],c[1],c[2]));}
