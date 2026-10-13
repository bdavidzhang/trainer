#include <bits/stdc++.h>
using namespace std;
int main(){int T;cin>>T;while(T--){string s;cin>>s;int L=s.size();bool ok=L>=10&&L<=13;vector<int>d;int h=0;
 for(int i=0;i<L&&ok;i++){char c=s[i];if(c=='-'){h++;if(i==0||i==L-1||s[i-1]=='-')ok=false;}
  else if(c=='X'){if(i!=L-1)ok=false;d.push_back(10);}else if(isdigit((unsigned char)c))d.push_back(c-'0');else ok=false;}
 if(ok&&d.size()!=10)ok=false;if(ok&&h>3)ok=false;if(ok&&h==3&&s[L-2]!='-')ok=false;
 if(ok){int S=0;for(int i=0;i<10;i++)S+=(10-i)*d[i];if(S%11)ok=false;}
 if(!ok){puts("invalid");continue;}
 int S=9+21+8;for(int i=0;i<9;i++)S+=d[i]*(i%2==0?3:1);int c=(10-S%10)%10;
 s[L-1]=char('0'+c);cout<<"978-"<<s<<"\n";}}
