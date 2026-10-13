#include <bits/stdc++.h>
using namespace std;
int id(char c){if(c==' ')return 26;if(c=='\'')return 27;return c-'A';}
int main(){string s;int n;cin>>n;getline(cin,s);const double PI=acos(-1.0);
 while(n--){getline(cin,s);while(!s.empty()&&(s.back()=='\r'||s.back()=='\n'))s.pop_back();
  int steps=0;for(size_t i=1;i<s.size();i++){int d=abs(id(s[i])-id(s[i-1]));steps+=min(d,28-d);}
  printf("%.10f\n",steps*(60*PI/28)/15+s.size());}}
