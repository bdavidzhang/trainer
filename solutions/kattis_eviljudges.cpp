#include <bits/stdc++.h>
using namespace std;
int main(){
    string s; long long m;
    cin>>s>>m;
    long long a=0,inv=0;
    for(char c:s){ if(c=='A')a++; else inv+=a; }
    printf("%lld\n", max(0LL, inv-m));
}
