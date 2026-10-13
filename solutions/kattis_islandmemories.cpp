#include <bits/stdc++.h>
using namespace std;
typedef bitset<1024> B;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    B all; for(int i=1;i<=n;i++) all[i]=1;
    vector<B> v;
    for(int i=0;i<m;i++){
        int k; scanf("%d",&k); B b;
        for(int j=0;j<k;j++){int x; scanf("%d",&x); b[x]=1;}
        if(b[n]) b=all&~b;
        v.push_back(b);
    }
    sort(v.begin(),v.end(),[](const B&x,const B&y){ size_t cx=x.count(),cy=y.count(); if(cx!=cy) return cx<cy; for(int i=0;i<1024;i++) if(x[i]!=y[i]) return (bool)y[i]; return false; });
    v.erase(unique(v.begin(),v.end(),[](const B&x,const B&y){return x==y;}),v.end());
    int k=v.size();
    for(int i=0;i<k;i++){
        B un;
        for(int j=0;j<i;j++){
            B in=v[i]&v[j];
            if(in.none()) continue;
            if(in!=v[j]){puts("0");return 0;}
            un|=v[j];
        }
        if(un==v[i]){puts("0");return 0;}
    }
    puts("1");
}
