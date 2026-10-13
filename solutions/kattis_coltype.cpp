#include <bits/stdc++.h>
using namespace std;
typedef unsigned __int128 u128;
int main(){string line,s;getline(cin,line);for(char c:line)if(!isspace((unsigned char)c))s+=c;
 bool ok=!s.empty()&&s.back()=='O';for(size_t i=0;i<s.size();i++){if(s[i]!='E'&&s[i]!='O')ok=false;if(i&&s[i]=='O'&&s[i-1]=='O')ok=false;}
 if(!ok){puts("INVALID");return 0;}
 int L=s.size();
 for(int j=4;j<=76;j+=2){u128 x=(((u128)1<<j)-1)/3;bool g=true;
  for(int i=L-2;i>=0;i--){if(s[i]=='E')x*=2;else{if(x<10||(x-1)%3!=0){g=false;break;}x=(x-1)/3;if(x%2==0||x<=1){g=false;break;}}}
  if(g){string o;while(x>0){o+=char('0'+(int)(x%10));x/=10;}reverse(o.begin(),o.end());cout<<o<<endl;return 0;}}
 puts("INVALID");}
