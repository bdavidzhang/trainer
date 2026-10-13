#include <bits/stdc++.h>
using namespace std;
int main(){string a,b;cin>>a>>b;int r=1;for(int i=0;i<4;i++)if(a[i]!=b[i])r*=2;printf("%d\n",r);}
