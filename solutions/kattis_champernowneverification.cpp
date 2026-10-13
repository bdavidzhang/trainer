#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;string t;for(int k=1;k<=12;k++){t+=to_string(k);if(t==s){printf("%d\n",k);return 0;}}puts("-1");}
