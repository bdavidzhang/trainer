#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; scanf("%d",&n); long double s=0;
    for(int i=0;i<n;i++){ double c; scanf("%lf",&c); s+=(long double)c*c*c; }
    printf("%.10Lf\n",cbrtl(s));
}
