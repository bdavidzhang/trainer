#include <bits/stdc++.h>
using namespace std;
int main(){int T;scanf("%d",&T);while(T--){int n;scanf("%d",&n);int r=(int)sqrt((double)n);while(r*r>n)r--;while((r+1)*(r+1)<=n)r++;
bool o=n&1,s=r*r==n;puts(o&&s?"OS":o?"O":s?"S":"EMPTY");}}
