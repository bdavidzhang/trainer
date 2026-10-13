#include <bits/stdc++.h>
using namespace std;
bool sim(const string&a,const string&b){ // a!=b
 int n=a.size(),m=b.size();
 if(n==m){int i=0;while(a[i]==b[i])i++;int j=n-1;while(a[j]==b[j])j--;
  if(i==j)return true;
  if(j==i+1&&a[i]==b[j]&&a[j]==b[i])return true;
  return false;}
 if(n>m)return sim(b,a);
 if(m!=n+1)return false;
 int i=0;while(i<n&&a[i]==b[i])i++;
 return a.compare(i,string::npos,b,i+1,string::npos)==0;}
int main(){set<string>st;string line;
 while(getline(cin,line)){while(!line.empty()&&(line.back()=='\r'||line.back()=='\n'))line.pop_back();
  if(line=="***")break;
  string cur;bool any=false;line+=' ';
  for(char ch:line){if(ch==' '||ch=='\r'||ch=='\n'||ch=='\t'){if(!cur.empty())st.insert(cur);cur.clear();}
   else if(isalpha((unsigned char)ch))cur+=tolower(ch);}
 }
 vector<string>v(st.begin(),st.end());int n=v.size();bool pr=false;
 vector<vector<int>>adj(n);
 for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){int d=(int)v[i].size()-(int)v[j].size();if(d<-1||d>1)continue;if(sim(v[i],v[j])){adj[i].push_back(j);adj[j].push_back(i);}}
 for(int i=0;i<n;i++)if(!adj[i].empty()){pr=true;sort(adj[i].begin(),adj[i].end());printf("%s:",v[i].c_str());for(int j:adj[i])printf(" %s",v[j].c_str());puts("");}
 if(!pr)puts("***");}
