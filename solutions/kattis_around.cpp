#include <bits/stdc++.h>
using namespace std;
static bool gl(string&l){while(getline(cin,l)){if(l.find_first_not_of(" \t\r\n")!=string::npos)return true;}l.clear();return false;}
int main(){int L,D;string line;gl(line);{stringstream ss(line);ss>>L>>D;}
 vector<vector<string>> syl(L);vector<vector<int>> dur(L);
 vector<pair<int,string>> all; // start time (voice 1), syllable
 vector<int> st(L),en(L);int t=0;
 for(int i=0;i<L;i++){
  gl(line);{stringstream ss(line);string w;while(ss>>w)syl[i].push_back(w);}
  gl(line);{stringstream ss(line);int w;while(ss>>w)dur[i].push_back(w);}
  st[i]=t;
  for(size_t j=0;j<syl[i].size();j++){all.push_back({t,syl[i][j]});t+=dur[i][j];}
  en[i]=t;
 }
 for(int i=0;i<L;i++){
  // events: (time, voice, text)
  vector<pair<int,string>> v1,v2;
  int tt=st[i];
  for(size_t j=0;j<syl[i].size();j++){v1.push_back({tt,syl[i][j]});tt+=dur[i][j];}
  for(auto&e:all){int x=e.first+D;if(x>=st[i]&&x<en[i])v2.push_back({x,e.second});}
  string a,b;
  size_t i1=0,i2=0;int lastT=-1,lastC=0;int e1=-1,e2=-1; // min next col per voice (end+1)
  while(i1<v1.size()||i2<v2.size()){
   int tm=INT_MAX;
   if(i1<v1.size())tm=min(tm,v1[i1].first);
   if(i2<v2.size())tm=min(tm,v2[i2].first);
   bool u1=i1<v1.size()&&v1[i1].first==tm,u2=i2<v2.size()&&v2[i2].first==tm;
   int col=0;
   if(lastT>=0)col=lastC+(tm-lastT);
   if(u1&&e1>=0)col=max(col,e1);
   if(u2&&e2>=0)col=max(col,e2);
   if(u1){a.resize(col,'_');a+=v1[i1].second;e1=a.size()+1;i1++;}
   if(u2){b.resize(col,'_');b+=v2[i2].second;e2=b.size()+1;i2++;}
   lastT=tm;lastC=col;
  }
  cout<<a<<"\n"<<(b.empty()?"/":b)<<"\n";
 }
}
