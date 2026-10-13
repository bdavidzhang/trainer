#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);int f=0;for(int i=0;i<n;i++){int x;scanf("%d",&x);if(!f)f=x;else if(x%f==0){printf("%d\n",x);f=0;}}}
