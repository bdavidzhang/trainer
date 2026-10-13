#include <bits/stdc++.h>
using namespace std;
int main(){string line;getline(cin,line);string bits,out;size_t i=0,n=line.size();
 while(i<n){ if(line[i]==' '){i++;continue;} size_t j=i;bool ok=1;string b;
  while(j<n&&line[j]!=' '){char c=line[j];if(c=='u'||c=='m')b+=c;else if(isalnum((unsigned char)c))ok=0;j++;}
  if(ok)bits+=b;i=j;}
 for(size_t k=0;k+7<=bits.size();k+=7){int v=0;for(int t=0;t<7;t++)v=v*2+(bits[k+t]=='u');out+=(char)v;}
 cout<<out<<"\n";}
