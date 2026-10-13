#include <bits/stdc++.h>
using namespace std;
int main(){int n,k;scanf("%d %d",&n,&k);string s(k,'a');for(int i=0;(int)s.size()<n;i++)s+="bcd"[i%3];puts(s.c_str());}
