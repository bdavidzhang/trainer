#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int main(){ull n;cin>>n;
    // best k is the largest primorial <= n; g = 1 - prod (p-1)/p
    __int128 q=1,ph=1;
    for(int p=2;;p++){bool pr=true;for(int d=2;d*d<=p;d++)if(p%d==0){pr=false;break;}
        if(!pr)continue;
        if(q*p>(__int128)n)break;
        q*=p;ph*=(p-1);}
    ull Q=(ull)q,P=(ull)(q-ph);
    ull g=std::gcd(P,Q);
    cout<<P/g<<"/"<<Q/g<<"\n";}
