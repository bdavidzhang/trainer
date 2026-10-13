#include <bits/stdc++.h>
using namespace std;
int main(){string w;set<string> s;bool ok=true;while(cin>>w){if(!s.insert(w).second)ok=false;}puts(ok?"yes":"no");}
