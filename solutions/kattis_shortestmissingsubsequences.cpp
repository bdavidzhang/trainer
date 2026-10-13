#include <bits/stdc++.h>
using namespace std;
static char buf[1000005];
int main(){string v;{scanf("%s",buf);v=buf;}scanf("%s",buf);string s=buf;int m=v.size(),L=s.size();
 int k=0;{vector<char>seen(26,0);int cnt=0;for(char c:s){if(!seen[c-'a']){seen[c-'a']=1;if(++cnt==m){k++;cnt=0;fill(seen.begin(),seen.end(),0);}}}}
 vector<vector<int>>pos(26);for(int i=0;i<L;i++)pos[s[i]-'a'].push_back(i);
 int n;scanf("%d",&n);string out;out.reserve(2*n);
 while(n--){scanf("%s",buf);int len=strlen(buf);char r='0';
  if(len==k+1){int cur=0;bool sub=true;for(int i=0;i<len;i++){auto&P=pos[buf[i]-'a'];auto it=lower_bound(P.begin(),P.end(),cur);if(it==P.end()){sub=false;break;}cur=*it+1;}
   if(!sub)r='1';}
  out+=r;out+='\n';}
 fputs(out.c_str(),stdout);}
