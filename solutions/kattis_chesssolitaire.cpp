#include <bits/stdc++.h>
using namespace std;
int n,m;string b; // n*n cells, '.' empty
unordered_set<string> bad;
vector<string> mv;
bool can(int r,int c,int r2,int c2){char p=b[r*n+c];int dr=r2-r,dc=c2-c,ar=abs(dr),ac=abs(dc);
 if(p=='N')return (ar==1&&ac==2)||(ar==2&&ac==1);
 if(p=='K')return max(ar,ac)==1;
 bool straight=(dr==0||dc==0),diag=(ar==ac);
 if(p=='R'&&!straight)return false;if(p=='B'&&!diag)return false;if(p=='Q'&&!straight&&!diag)return false;
 int sr=(dr>0)-(dr<0),sc=(dc>0)-(dc<0);int x=r+sr,y=c+sc;
 while(x!=r2||y!=c2){if(b[x*n+y]!='.')return false;x+=sr;y+=sc;}
 return true;}
bool dfs(int left){if(left==1)return true;if(bad.count(b))return false;
 for(int s=0;s<n*n;s++)if(b[s]!='.')for(int t=0;t<n*n;t++)if(t!=s&&b[t]!='.'&&can(s/n,s%n,t/n,t%n)){
   char ps=b[s],pt=b[t];b[t]=ps;b[s]='.';
   string line;line+=ps;line+=": ";line+=char('A'+s/n);line+=char('1'+s%n);line+=" -> ";line+=char('A'+t/n);line+=char('1'+t%n);
   mv.push_back(line);
   if(dfs(left-1))return true;
   mv.pop_back();b[s]=ps;b[t]=pt;}
 bad.insert(b);return false;}
int main(){cin>>n>>m;b.assign(n*n,'.');for(int i=0;i<m;i++){string p,l;cin>>p>>l;b[(l[0]-'A')*n+(l[1]-'1')]=p[0];}
 if(dfs(m)){for(auto&s:mv)cout<<s<<"\n";}else cout<<"No solution\n";}
