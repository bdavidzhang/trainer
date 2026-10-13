#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; 
    static char buf[1<<20|16];
    scanf("%d %d",&n,&m);
    vector<array<int,26>> ch; vector<int> par, tab;
    array<int,26> z; z.fill(-1);
    ch.push_back(z); par.push_back(-1); tab.push_back(-1);
    vector<int> path;
    for(int i=0;i<n;i++){
        scanf("%s",buf);
        int u=0; path.clear();
        for(char*p=buf;*p;p++){
            int c=*p-'a';
            if(ch[u][c]<0){ int id=ch.size(); ch[u][c]=id; ch.push_back(z); par.push_back(u); tab.push_back(-1); }
            u=ch[u][c]; path.push_back(u);
        }
        for(int v:path) if(tab[v]<0) tab[v]=u;
    }
    int V=ch.size();
    vector<int> dist(V,-1), q; q.reserve(V);
    dist[0]=0; q.push_back(0);
    for(size_t h=0;h<q.size();h++){
        int u=q[h]; int d=dist[u]+1;
        auto go=[&](int v){ if(v>=0&&dist[v]<0){dist[v]=d;q.push_back(v);} };
        for(int c=0;c<26;c++) go(ch[u][c]);
        go(par[u]);
        if(u) go(tab[u]);
    }
    for(int i=0;i<m;i++){
        scanf("%s",buf);
        int len=strlen(buf);
        int best=len; int u=0;
        for(int k=0;k<len;k++){
            u=ch[u][buf[k]-'a'];
            if(u<0) break;
            best=min(best,dist[u]+len-k-1);
        }
        printf("%d\n",best);
    }
}
