#include <bits/stdc++.h>
using namespace std;
map<vector<int>,int> ids;
int getid(vector<int>&v){ // v[0]=label, rest children ids
 sort(v.begin()+1,v.end());auto it=ids.find(v);if(it!=ids.end())return it->second;int k=ids.size();ids[v]=k;return k;}
int parse(const string&s){vector<vector<int>> st;size_t i=0;
 while(i<s.size()){char c=s[i];
  if(isdigit((unsigned char)c)){int v=0;while(i<s.size()&&isdigit((unsigned char)s[i]))v=v*10+(s[i++]-'0');st.push_back({v});continue;}
  if(c==')'){int id=getid(st.back());st.pop_back();st.back().push_back(id);}
  i++;}
 return getid(st.back());}
int main(){string a,b;getline(cin,a);getline(cin,b);puts(parse(a)==parse(b)?"Yes":"No");}
