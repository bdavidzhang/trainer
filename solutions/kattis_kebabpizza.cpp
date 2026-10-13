#include <bits/stdc++.h>
using namespace std;
int p[100005];
int fnd(int x){ while(p[x]!=x) x=p[x]=p[p[x]]; return x; }
int main(){
    int n,k; scanf("%d %d",&n,&k);
    vector<pair<int,int>> es; vector<char> loop(k+1,0),used(k+1,0);
    for(int i=0;i<n;i++){int a,b;scanf("%d %d",&a,&b);used[a]=used[b]=1; if(a==b) loop[a]=1; else es.push_back({min(a,b),max(a,b)});}
    sort(es.begin(),es.end()); es.erase(unique(es.begin(),es.end()),es.end());
    vector<int> deg(k+1,0);
    for(int i=1;i<=k;i++) p[i]=i;
    for(auto&e:es){deg[e.first]++;deg[e.second]++;p[fnd(e.first)]=fnd(e.second);}
    vector<char> core(k+1,0);
    for(int i=1;i<=k;i++) core[i]= used[i] && (loop[i]||deg[i]>=2);
    vector<int> cdeg(k+1,0), cv(k+1,0), ce(k+1,0);
    for(auto&e:es) if(core[e.first]&&core[e.second]){cdeg[e.first]++;cdeg[e.second]++;ce[fnd(e.first)]++;}
    int comps=0; bool ok=true, cyc=false;
    for(int i=1;i<=k;i++) if(used[i]){ if(fnd(i)==i) comps++; if(core[i]) cv[fnd(i)]++; if(cdeg[i]>2) ok=false; }
    for(int i=1;i<=k;i++) if(used[i]&&fnd(i)==i&&cv[i]>0&&ce[i]>=cv[i]) cyc=true;
    if(cyc&&comps>1) ok=false;
    puts(ok?"possible":"impossible");
}
