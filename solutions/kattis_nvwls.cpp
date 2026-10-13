#include <bits/stdc++.h>
using namespace std;
static int ch[100005][26],fail_[100005],outl[100005],wid[100005],dep[100005];
int main(){int n;if(scanf("%d",&n)!=1)return 0;vector<string> w(n);vector<int> vc(n);
 static char buf[300005];int cnt=1;
 memset(wid,-1,sizeof(wid));
 auto isv=[](char c){return c=='A'||c=='E'||c=='I'||c=='O'||c=='U';};
 for(int i=0;i<n;i++){scanf("%s",buf);w[i]=buf;int u=0,v=0;
  for(char c:w[i]){if(isv(c)){v++;continue;}int x=c-'A';if(!ch[u][x]){dep[cnt]=dep[u]+1;ch[u][x]=cnt++;}u=ch[u][x];}
  vc[i]=v;if(wid[u]<0||vc[wid[u]]<v)wid[u]=i;}
 // BFS
 vector<int> q;q.reserve(cnt);
 for(int x=0;x<26;x++)if(ch[0][x])q.push_back(ch[0][x]);
 for(size_t h=0;h<q.size();h++){int u=q[h];int f=fail_[u];outl[u]=wid[f]>=0?f:outl[f];
  for(int x=0;x<26;x++){int v=ch[u][x];if(v){fail_[v]=ch[f][x];q.push_back(v);}else ch[u][x]=ch[f][x];}}
 scanf("%s",buf);int L=strlen(buf);
 vector<int> dp(L+1,-1),from(L+1,-1);dp[0]=0;int u=0;
 for(int i=1;i<=L;i++){u=ch[u][buf[i-1]-'A'];
  for(int s=(wid[u]>=0?u:outl[u]);s;s=outl[s]){int j=i-dep[s];if(dp[j]<0)continue;int v=dp[j]+vc[wid[s]];if(v>dp[i]){dp[i]=v;from[i]=wid[s];}}}
 vector<int> seq;int i=L;
 while(i>0){int id=from[i];seq.push_back(id);i-=(int)w[id].size()-vc[id];}
 reverse(seq.begin(),seq.end());
 string out;for(size_t k=0;k<seq.size();k++){if(k)out+=' ';out+=w[seq[k]];}
 out+='\n';fwrite(out.data(),1,out.size(),stdout);}
