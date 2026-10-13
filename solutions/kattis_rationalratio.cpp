#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){string s;int r;cin>>s>>r;size_t d=s.find('.');string ip=s.substr(0,d),fp=s.substr(d+1);int n=fp.size();
string all=ip+fp;ll A=stoll(all);ll B=stoll(all.substr(0,all.size()-r));
ll p10r=1;for(int i=0;i<r;i++)p10r*=10;ll p=1;for(int i=0;i<n-r;i++)p*=10;
ll num=A-B,den=p*(p10r-1);ll g=std::gcd(num,den);printf("%lld/%lld\n",num/g,den/g);}
