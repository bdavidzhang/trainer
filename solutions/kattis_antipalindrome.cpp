#include <bits/stdc++.h>
using namespace std;
int main(){string l,s;getline(cin,l);for(char ch:l)if(isalpha((unsigned char)ch))s+=tolower(ch);
 bool p=false;for(size_t i=0;i<s.size();i++){if(i+1<s.size()&&s[i]==s[i+1])p=true;if(i+2<s.size()&&s[i]==s[i+2])p=true;}
 puts(p?"Palindrome":"Anti-palindrome");}
