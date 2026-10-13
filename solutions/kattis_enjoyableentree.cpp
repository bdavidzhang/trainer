#include <bits/stdc++.h>
using namespace std;
int main(){
    long long n; cin>>n;
    long long m=min(n,(long long)200);
    double a=100,b=0; // a = day i, b = day i+1 (potato share)
    for(long long i=1;i<m;i++){ double c=(a+b)/2; a=b; b=c; }
    printf("%.9f %.9f\n",a,100-a);
}
