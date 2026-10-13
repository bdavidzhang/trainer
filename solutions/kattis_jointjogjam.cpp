#include <bits/stdc++.h>
using namespace std;
int main(){ double a[8]; for(auto&x:a)cin>>x; double d1=hypot(a[0]-a[2],a[1]-a[3]), d2=hypot(a[4]-a[6],a[5]-a[7]); printf("%.10f\n",max(d1,d2)); }
