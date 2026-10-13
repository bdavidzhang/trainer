#include <bits/stdc++.h>
using namespace std;
int main(){
    double R,S;
    while(scanf("%lf %lf",&R,&S)==2) printf("%lld\n",llround(sqrt(R*(S+0.16)/0.067)));
}
