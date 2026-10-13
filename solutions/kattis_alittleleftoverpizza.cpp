#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;long long s[3]={0,0,0};int cap[3]={6,8,12};
for(int i=0;i<n;i++){string t;int l;cin>>t>>l;int k=t=="S"?0:t=="M"?1:2;s[k]+=l;}
long long r=0;for(int k=0;k<3;k++)r+=(s[k]+cap[k]-1)/cap[k];cout<<r<<"\n";}
