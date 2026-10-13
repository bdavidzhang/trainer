#include <bits/stdc++.h>
using namespace std;

int main(){int k;cin>>k;int prev=1000,ans=0;for(int i=0;i<k;i++){int x;cin>>x;if(i==0||x<prev)ans++;prev=x;}cout<<ans<<"\n";}
