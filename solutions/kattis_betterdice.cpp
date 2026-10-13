#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<int>a(n),b(n);for(auto&x:a)scanf("%d",&x);for(auto&x:b)scanf("%d",&x);
long long f=0,s=0;for(int x:a)for(int y:b){if(x>y)f++;else if(y>x)s++;}
puts(f>s?"first":s>f?"second":"tie");}
