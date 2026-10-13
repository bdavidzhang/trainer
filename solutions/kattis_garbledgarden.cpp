#include <bits/stdc++.h>
using namespace std;
int n;
// returns list of position-cycles (one Euler circuit per component of the mismatch graph)
vector<vector<int>> cycles(const vector<int>&t){
  vector<int> s(t);sort(s.begin()+1,s.end());
  vector<vector<int>> out(n+1); // edges (positions) leaving value s_i
  for(int i=1;i<=n;i++)if(s[i]!=t[i])out[s[i]].push_back(i);
  vector<vector<int>> res;
  for(int v=1;v<=n;v++)if(!out[v].empty()){
    vector<int> lst; vector<pair<int,int>> st; st.push_back({v,0});
    while(!st.empty()){int u=st.back().first;
      if(!out[u].empty()){int e=out[u].back();out[u].pop_back();st.push_back({t[e],e});}
      else{if(st.back().second)lst.push_back(st.back().second);st.pop_back();}
    }
    res.push_back(lst); // reversed circuit = required p order
  }
  return res;
}
void doop(vector<int>&t,const vector<int>&p){int m=p.size();int pot=t[p[0]];for(int i=1;i<m;i++)t[p[i-1]]=t[p[i]];t[p[m-1]]=pot;}
int main(){scanf("%d",&n);vector<int> t(n+1);for(int i=1;i<=n;i++)scanf("%d",&t[i]);
 vector<vector<int>> ops;
 auto c=cycles(t);
 if(c.size()>1){vector<int> p;for(auto&x:c)p.push_back(x[0]);ops.push_back(p);doop(t,p);c=cycles(t);}
 if(c.size()==1)ops.push_back(c[0]);
 printf("%d\n",(int)ops.size());
 for(auto&p:ops){printf("%d\n",(int)p.size());for(size_t i=0;i<p.size();i++)printf("%d%c",p[i]," \n"[i+1==p.size()]);}
}
