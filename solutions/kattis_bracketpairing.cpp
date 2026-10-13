#include <bits/stdc++.h>
using namespace std;
string s;long long f[22][22];bool done[22][22];
long long w(char a,char b){const string O="([{<",C=")]}>";
    if(a=='?'&&b=='?')return 4;
    if(a=='?')return C.find(b)!=string::npos;
    if(b=='?')return O.find(a)!=string::npos;
    size_t i=O.find(a);return i!=string::npos&&C[i]==b;}
long long go(int l,int r){if(l==r)return 1;if(done[l][r])return f[l][r];done[l][r]=1;long long t=0;
    for(int k=l+1;k<r;k+=2){long long x=w(s[l],s[k]);if(x)t+=x*go(l+1,k)*go(k+1,r);}
    return f[l][r]=t;}
int main(){cin>>s;printf("%lld\n",go(0,s.size()));}
