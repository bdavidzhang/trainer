#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,k; scanf("%d %d",&n,&k);
    vector<vector<int>> L(n,vector<int>(k)),Hh(n,vector<int>(k));
    for(int i=0;i<n;i++){ for(auto&x:L[i])scanf("%d",&x); for(auto&x:Hh[i])scanf("%d",&x); }
    vector<char> ok(n,0); queue<int> q;
    for(int i=0;i<n;i++){ bool z=true; for(int x:L[i]) if(x) z=false; if(z){ok[i]=1;q.push(i);} }
    int cnt=0;
    while(!q.empty()){
        int u=q.front(); q.pop(); cnt++;
        for(int j=0;j<n;j++) if(!ok[j]){
            bool g=true; for(int d=0;d<k;d++) if(L[j][d]>Hh[u][d]){g=false;break;}
            if(g){ok[j]=1;q.push(j);}
        }
    }
    printf("%d\n",cnt);
}
