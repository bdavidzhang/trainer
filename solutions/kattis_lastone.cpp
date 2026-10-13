#include <bits/stdc++.h>
using namespace std;
int main(){long long h1,d1,t1,h2,d2,t2;cin>>h1>>d1>>t1>>h2>>d2>>t2;
 long long k1=((h2+d1-1)/d1-1)*t1,k2=((h1+d2-1)/d2-1)*t2;
 puts(k1<k2?"player one":k2<k1?"player two":"draw");}
