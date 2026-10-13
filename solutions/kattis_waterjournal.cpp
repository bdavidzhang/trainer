#include <bits/stdc++.h>
using namespace std;
int main(){int n,a,b;cin>>n>>a>>b;bool ha=false,hb=false;for(int i=0;i<n-1;i++){int w;cin>>w;if(w==a)ha=true;if(w==b)hb=true;}
 if(ha&&hb){for(int i=a;i<=b;i++)cout<<i<<"\n";}
 else if(ha)cout<<b<<"\n";
 else if(hb)cout<<a<<"\n";
 else if(a==b)cout<<a<<"\n";
 else cout<<-1<<"\n";}
