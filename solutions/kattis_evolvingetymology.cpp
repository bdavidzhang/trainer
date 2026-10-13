#include <bits/stdc++.h>
using namespace std;
int main(){
    long long n; unsigned long long k; string s;
    cin>>n>>k>>s;
    long long r=1%n, b=2%n;
    while(k){ if(k&1) r=r*b%n; b=b*b%n; k>>=1; }
    string t(n,' ');
    for(long long i=0;i<n;i++) t[i]=s[(i*r)%n];
    cout<<t<<"\n";
}
