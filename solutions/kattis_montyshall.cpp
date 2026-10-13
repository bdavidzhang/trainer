#include <bits/stdc++.h>
using namespace std;
int main(){ double d,s,e; cin>>d>>s>>e; double o=d-s-e; double k=min(s,o);
    double ans=k*(d-s)/(d*o)+(s-k)/d; printf("%.10f\n",ans); }
