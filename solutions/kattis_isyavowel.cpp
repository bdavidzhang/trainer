#include <bits/stdc++.h>
using namespace std;
int main(){ string s; cin>>s; int a=0,b=0; for(char c:s){ if(strchr("aeiou",c)) a++; if(c=='y') b++; } printf("%d %d\n",a,a+b); }
