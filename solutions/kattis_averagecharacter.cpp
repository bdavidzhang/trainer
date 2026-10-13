#include <bits/stdc++.h>
using namespace std;
int main(){string s;getline(cin,s);while(!s.empty()&&(s.back()=='\n'||s.back()=='\r'))s.pop_back();long long t=0;for(char c:s)t+=(unsigned char)c;putchar((char)(t/(long long)s.size()));putchar('\n');}
