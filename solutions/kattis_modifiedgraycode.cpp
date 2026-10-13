#include <bits/stdc++.h>
using namespace std;
int main(){vector<int>v;for(int i=0;i<1024;i++)if(__builtin_popcount(i)%2==0)v.push_back(i);
 int n;scanf("%d",&n);while(n--){int k;scanf("%d",&k);int x=v[k];for(int b=9;b>=0;b--)putchar('0'+(x>>b&1));putchar('\n');}}
