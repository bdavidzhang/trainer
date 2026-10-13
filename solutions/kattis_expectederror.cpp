#include <bits/stdc++.h>
using namespace std;
int main(){long long n,k,p;cin>>n>>k>>p;
 // units of 0.001s
 long long c=100*(n-k+1)+p*(n+4), b=100*(n-k+2)+(100-p)*(n+4), r=100*(n+4);
 if(c<b&&c<r)puts("continue");else if(b<r)puts("backspace");else puts("restart");}
