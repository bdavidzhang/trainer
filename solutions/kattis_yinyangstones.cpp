#include <bits/stdc++.h>
using namespace std;
int main(){string s;cin>>s;int b=0,w=0;for(char c:s){if(c=='B')b++;else if(c=='W')w++;}puts(b==w?"1":"0");}
