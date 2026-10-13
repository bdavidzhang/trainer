#include <bits/stdc++.h>
using namespace std;
int main(){int n;string s;cin>>n>>s;int c=0,a=0;for(char ch:s){if(ch=='1'){a++;c=2;}else if(c>0){c--;a++;}}printf("%d\n",a);}
