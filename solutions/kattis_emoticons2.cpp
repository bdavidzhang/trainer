#include <bits/stdc++.h>
using namespace std;
int main(){string s;getline(cin,s);while(!s.empty()&&(s.back()=='\r'||s.back()=='\n'))s.pop_back();
 vector<string>em={":)",":-)",":-(",";-)","xD","^_^","-_-","^o^","^^;","(..)"};
 auto calc=[&](const string&t){int n=t.size(),i=0,c=0;while(i<n){int adv=1;for(auto&e:em)if(t.compare(i,e.size(),e)==0){adv=e.size();break;}i+=adv;c++;}return c;};
 int mn=calc(s),mx=mn;set<char>cs(s.begin(),s.end());
 for(char a:cs)for(int b=32;b<127;b++){string t=s;for(char&ch:t)if(ch==a)ch=(char)b;int c=calc(t);mn=min(mn,c);mx=max(mx,c);}
 printf("%d %d\n",mn,mx);}
