#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);int mn=INT_MAX,mx=0;for(int i=0;i<n;i++){int p;scanf("%d",&p);mn=min(mn,p);mx=max(mx,p);}printf("%d\n",max(0,mn-mx/2));}
