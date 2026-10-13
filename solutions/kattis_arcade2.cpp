#include <bits/stdc++.h>
using namespace std;
int main(){ unsigned long long n; cin>>n; unsigned long long m=n-1; int pc=__builtin_popcountll(m);
    if(m==0||pc==1) puts("1");
    else if(pc==2) cout<<1+(m&(~m+1))<<"\n";
    else puts("impossible"); }
