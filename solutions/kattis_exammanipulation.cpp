#include <bits/stdc++.h>
using namespace std;
int main(){int n,k;cin>>n>>k;vector<int>a(n);for(auto&x:a){string s;cin>>s;x=0;for(int j=0;j<k;j++)if(s[j]=='T')x|=1<<j;}
int best=0;for(int m=0;m<(1<<k);m++){int lo=k;for(int x:a){int c=k-__builtin_popcount(x^m);if(c<lo){lo=c;if(lo<=best)break;}}best=max(best,lo);}
printf("%d\n",best);}
