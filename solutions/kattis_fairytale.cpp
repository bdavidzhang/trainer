#include <bits/stdc++.h>
using namespace std;
int main(){int t;scanf("%d",&t);while(t--){int n;scanf("%d",&n);int m=0;while(n--){int p;scanf("%d",&p);m|=1<<((p-1)/10);}printf("%d\n",__builtin_popcount(m));}}
