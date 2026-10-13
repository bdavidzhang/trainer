#include <bits/stdc++.h>
using namespace std;
int main(){int t;cin>>t;for(int b=0;b<=t;b++){int w=t-b;if(w>600)continue;if(w<=360||(w<=540&&b>=30)||b>=45){printf("%d\n",b);return 0;}}}
