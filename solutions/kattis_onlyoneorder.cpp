#include <bits/stdc++.h>
using namespace std;
int main(){int t;scanf("%d",&t);while(t--){int n,m;scanf("%d %d",&n,&m);bool bad=false;int have=0;for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);if(a>b)bad=true;else if(b==a+1)have++;}
// constraints are distinct, so each adjacent pair is counted at most once
printf("%d\n",bad?-1:n-1-have);}}
