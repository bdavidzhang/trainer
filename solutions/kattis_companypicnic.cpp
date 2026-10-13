#include <bits/stdc++.h>
using namespace std;
typedef pair<int,long long> P;
int n;vector<int> ch[1005];long long sp[1005];P d0[1005],d1[1005];
P add(P a,P b){return {a.first+b.first,a.second+b.second};}
P sub(P a,P b){return {a.first-b.first,a.second-b.second};}
void dfs(int v){P s(0,0);for(int c:ch[v]){dfs(c);s=add(s,max(d0[c],d1[c]));}
 d0[v]=s;d1[v]=P(-1000000,0);
 for(int c:ch[v]){P r=add(add(sub(s,max(d0[c],d1[c])),d0[c]),P(1,min(sp[v],sp[c])));d1[v]=max(d1[v],r);}}
int main(){cin>>n;map<string,int>id;vector<string>nm(n),sup(n);
 for(int i=0;i<n;i++){double x;cin>>nm[i]>>x>>sup[i];sp[i]=llround(x*1000);id[nm[i]]=i;}
 int root=-1;for(int i=0;i<n;i++){if(sup[i]=="CEO")root=i;else ch[id[sup[i]]].push_back(i);}
 dfs(root);P r=max(d0[root],d1[root]);
 printf("%d %.8f\n",r.first,r.first?r.second/1000.0/r.first:0.0);}
