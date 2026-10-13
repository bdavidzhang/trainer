#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);bool g=true;for(int i=0;i<3;i++){bool h=false;for(int j=0;j<n;j++){int x;scanf("%d",&x);if(x==7)h=true;}g&=h;}puts(g?"777":"0");}
