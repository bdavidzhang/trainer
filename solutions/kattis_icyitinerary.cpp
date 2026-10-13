#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<long long> E;
bool road(int u,int v){ if(u>v) swap(u,v); return binary_search(E.begin(),E.end(),(long long)u*(n+1)+v); }
int main(){
    scanf("%d %d",&n,&m);
    E.resize(m);
    for(int i=0;i<m;i++){int u,v;scanf("%d %d",&u,&v); if(u>v) swap(u,v); E[i]=(long long)u*(n+1)+v;}
    sort(E.begin(),E.end());
    vector<int> nx(n+1,0),pv(n+1,0);
    int tail=1,J=1; bool A=false; // edges before junction J have colour A (road?), after: !A
    for(int v=2;v<=n;v++){
        if(J==1){ // no A edges: reinterpret as all-A' with junction at tail
            A=!A; J=tail;
            if(tail==1) A=road(1,v);
        }
        if(road(J,v)==A){
            int w=nx[J];
            nx[J]=v; pv[v]=J; nx[v]=w;
            if(w){ pv[w]=v; J=(road(v,w)==A)?w:v; }
            else { tail=v; J=v; }
        } else {
            int p=pv[J]; // exists since J!=1
            nx[p]=v; pv[v]=p; nx[v]=J; pv[J]=v;
            J=(road(p,v)==A)?v:p;
        }
    }
    string out;
    for(int v=1;v;v=nx[v]){ out+=to_string(v); out+=' '; }
    out.back()='\n';
    fputs(out.c_str(),stdout);
}
