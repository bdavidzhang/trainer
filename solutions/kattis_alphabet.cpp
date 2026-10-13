#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;int n=s.size(),b=0;vector<int>d(n,1);
 for(int i=0;i<n;i++){for(int j=0;j<i;j++)if(s[j]<s[i])d[i]=max(d[i],d[j]+1);b=max(b,d[i]);}
 cout<<26-b<<endl;}
