#include <bits/stdc++.h>
using namespace std;
int main(){int h,w,k,i,t;cin>>h>>w>>k>>i>>t;
 string s="KIT"; s+=string(k-1,'K'); s+=string(t-1,'T'); s+=string(i-1,'I');
 for(int r=0;r<h;r++)cout<<s.substr(r*w,w)<<"\n";}
