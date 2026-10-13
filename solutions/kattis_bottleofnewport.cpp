#include <bits/stdc++.h>
using namespace std;
int main(){
    long long d,a,o,da,dd; cin>>d>>a>>o>>da>>dd;
    long long ra=max(0LL,a-d*da), ro=max(0LL,o-d*dd);
    printf("%.12f\n",100.0*(double)ra/((double)ra+(double)ro));
}
