#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);int nx=1;bool ok=true;for(int i=0;i<n;i++){int x;scanf("%d",&x);while(nx<x){printf("%d\n",nx++);ok=false;}nx=x+1;}if(ok)puts("good job");}
