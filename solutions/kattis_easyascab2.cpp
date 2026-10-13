#include <bits/stdc++.h>
using namespace std;
// split a UTF-8 string into characters (kept as byte strings)
static vector<string> split(const string&s){vector<string> r;size_t i=0;while(i<s.size()){unsigned char c=s[i];int l=1;if(c>=0xF0)l=4;else if(c>=0xE0)l=3;else if(c>=0xC0)l=2;if(i+l>s.size())l=s.size()-i;r.push_back(s.substr(i,l));i+=l;}return r;}
int main(){string line;getline(cin,line);int n=atoi(line.c_str());
 unordered_map<string,int> id;vector<string> name;vector<vector<int>> w(n);
 for(int i=0;i<n;i++){getline(cin,line);while(!line.empty()&&(line.back()=='\r'||line.back()=='\n'))line.pop_back();
  for(auto&ch:split(line)){auto it=id.find(ch);int k;if(it==id.end()){k=name.size();id[ch]=k;name.push_back(ch);}else k=it->second;w[i].push_back(k);}}
 int K=name.size();vector<vector<int>> g(K);vector<int> deg(K,0);bool bad=false;
 for(int i=0;i+1<n;i++){auto&a=w[i];auto&b=w[i+1];size_t j=0;while(j<a.size()&&j<b.size()&&a[j]==b[j])j++;
  if(j==b.size()){bad=true;break;} // b is a prefix of a (or equal)
  if(j==a.size())continue;
  g[a[j]].push_back(b[j]);deg[b[j]]++;}
 if(bad){puts("IMPOSSIBLE");return 0;}
 vector<int> q;for(int i=0;i<K;i++)if(!deg[i])q.push_back(i);
 bool amb=false;vector<int> ord;size_t h=0;
 while(h<q.size()){if(q.size()-h>1)amb=true;int u=q[h++];ord.push_back(u);for(int v:g[u])if(--deg[v]==0)q.push_back(v);}
 if((int)ord.size()<K){puts("IMPOSSIBLE");return 0;}
 if(amb){puts("AMBIGUOUS");return 0;}
 string out;for(int u:ord)out+=name[u];puts(out.c_str());}
