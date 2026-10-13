#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(0);string s;set<string>img;unordered_set<string>used;vector<string>orph;
 auto clean=[&](string&t){while(!t.empty()&&(t.back()=='\r'||t.back()==' '))t.pop_back();};
 while(getline(cin,s)){clean(s);if(s.empty())break;img.insert(s);}
 while(getline(cin,s)){clean(s);if(s.empty())continue;
  size_t p=s.rfind('_');size_t q=(p==string::npos||p==0)?string::npos:s.rfind('_',p-1);
  string nm=q==string::npos?s:s.substr(0,q);
  if(img.count(nm))used.insert(nm);else orph.push_back(s);}
 sort(orph.begin(),orph.end());string out;bool any=false;
 for(auto&o:orph){out+="F "+o+"\n";any=true;}
 for(auto&i:img)if(!used.count(i)){out+="I "+i+"\n";any=true;}
 if(!any)out="No mismatches.\n";
 cout<<out;}
