#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m;scanf("%d %d",&n,&m);
    vector<int>x(n+1),y(n+1);for(int i=1;i<=n;i++)scanf("%d %d",&x[i],&y[i]);
    // nb[0]=W,1=E (row), 2=S,3=N (column)
    vector<array<int,4>> nb(n+1,{0,0,0,0});
    vector<int> o(n);iota(o.begin(),o.end(),1);
    sort(o.begin(),o.end(),[&](int a,int b){return y[a]!=y[b]?y[a]<y[b]:x[a]<x[b];});
    for(int i=0;i+1<n;i++)if(y[o[i]]==y[o[i+1]]){nb[o[i]][1]=o[i+1];nb[o[i+1]][0]=o[i];}
    sort(o.begin(),o.end(),[&](int a,int b){return x[a]!=x[b]?x[a]<x[b]:y[a]<y[b];});
    for(int i=0;i+1<n;i++)if(x[o[i]]==x[o[i+1]]){nb[o[i]][3]=o[i+1];nb[o[i+1]][2]=o[i];}
    vector<char> dead(n+1,0);
    string out;vector<int> lst;
    for(int q=0;q<m;q++){
        int t;char ch;scanf("%d %c",&t,&ch);
        if(dead[t]){out+="ignore\n";continue;}
        int d=ch=='W'?0:ch=='E'?1:ch=='S'?2:3;
        lst.clear();
        int v=nb[t][d];
        while(v){
            int nx=nb[v][d];
            dead[v]=1;lst.push_back(v);
            for(int a=0;a<4;a+=2){
                int l=nb[v][a],r=nb[v][a+1];
                if(l)nb[l][a+1]=r;
                if(r)nb[r][a]=l;
            }
            v=nx;
        }
        out+=to_string(lst.size());
        for(int u:lst){out+=' ';out+=to_string(u);}
        out+='\n';
    }
    fputs(out.c_str(),stdout);
}
