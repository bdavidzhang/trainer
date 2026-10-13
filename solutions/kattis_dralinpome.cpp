#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;int c[26]={0};for(char ch:s)c[ch-'a']++;int o=0;for(int i=0;i<26;i++)o+=c[i]&1;puts(o<=1?"yes":"no");}
