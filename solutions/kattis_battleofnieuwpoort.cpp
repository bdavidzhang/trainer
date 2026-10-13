#include <bits/stdc++.h>
using namespace std;
int main(){int y;cin>>y;for(int b=2;b<=16;b++)if(y%(b*b)==0){string s;int v=y;while(v){s+="0123456789abcdef"[v%b];v/=b;}
reverse(s.begin(),s.end());cout<<b<<" "<<s<<"\n";return 0;}cout<<"impossible\n";}
