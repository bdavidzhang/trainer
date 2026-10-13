#include <bits/stdc++.h>
using namespace std;
int hv(char c){if(c>='0'&&c<='9')return c-'0';if(c>='a'&&c<='f')return c-'a'+10;if(c>='A'&&c<='F')return c-'A'+10;return -1;}
// 0 boring, 1 cool, 2 artistic
int classify(const string&s){if(s.size()%2)return 2;vector<int> b;for(size_t i=0;i<s.size();i+=2){int x=hv(s[i]),y=hv(s[i+1]);if(x<0||y<0)return 2;b.push_back(x*16+y);}
 bool multi=false;size_t i=0;
 while(i<b.size()){int c=b[i];if(c<0x80){i++;continue;}
  int l;long cp;if((c&0xE0)==0xC0){l=2;cp=c&0x1F;}else if((c&0xF0)==0xE0){l=3;cp=c&0x0F;}else if((c&0xF8)==0xF0){l=4;cp=c&0x07;}else return 2;
  if(i+l>b.size())return 2;
  for(int k=1;k<l;k++){if((b[i+k]&0xC0)!=0x80)return 2;cp=cp<<6|(b[i+k]&0x3F);}
  long mn=l==2?0x80:l==3?0x800:0x10000;
  if(cp<mn||cp>0x10FFFF)return 2;
  if(cp>=0xD800&&cp<=0xDFFF)return 2;
  if(cp>=0xFDD0&&cp<=0xFDEF)return 2;
  if((cp&0xFFFE)==0xFFFE)return 2;
  multi=true;i+=l;}
 return multi?1:0;}
int main(){string line;getline(cin,line);int n=atoi(line.c_str());int cnt[3]={0,0,0};
 for(int i=0;i<n;i++){line.clear();getline(cin,line);string t;for(char c:line)if(!isspace((unsigned char)c))t+=c;cnt[classify(t)]++;}
 printf("%d %d %d\n",cnt[0],cnt[1],cnt[2]);}
