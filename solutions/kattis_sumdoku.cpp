#include <bits/stdc++.h>
using namespace std;
// Constraint propagation (peer elimination + arc consistency on sum constraints + hidden singles) with MRV search.
typedef array<int,81> St;
vector<array<int,3>> cons;        // (cellA, cellB, type 0:<,1:=,2:>)
int sup[3][10];                   // sup[t][v] = mask of w != v with v+w satisfying t
vector<int> peers[81]; vector<array<int,9>> units;
bool propagate(St&d){
    bool ch=true;
    while(ch){
        ch=false;
        for(int i=0;i<81;i++){
            if(!d[i]) return false;
            if(!(d[i]&(d[i]-1))) for(int p:peers[i]) if(d[p]&d[i]){ d[p]&=~d[i]; if(!d[p]) return false; ch=true; }
        }
        for(auto&c:cons){
            for(int s=0;s<2;s++){
                int a=c[s],b=c[1-s],na=0;
                for(int v=1;v<=9;v++) if((d[a]>>v&1)&&(sup[c[2]][v]&d[b])) na|=1<<v;
                if(na!=d[a]){ d[a]=na; if(!na) return false; ch=true; }
            }
        }
        for(auto&u:units) for(int v=1;v<=9;v++){
            int cnt=0,last=-1;
            for(int x:u) if(d[x]>>v&1){cnt++;last=x;}
            if(!cnt) return false;
            if(cnt==1&&d[last]!=(1<<v)){ d[last]=1<<v; ch=true; }
        }
    }
    return true;
}
bool solve(St&d){
    if(!propagate(d)) return false;
    int best=-1,bc=100;
    for(int i=0;i<81;i++){int k=__builtin_popcount(d[i]); if(k>1&&k<bc){bc=k;best=i;}}
    if(best<0) return true;
    for(int v=1;v<=9;v++) if(d[best]>>v&1){
        St e=d; e[best]=1<<v;
        if(solve(e)){ d=e; return true; }
    }
    return false;
}
int main(){
    auto ty=[](char ch){return ch=='<'?0:ch=='='?1:2;};
    for(int v=1;v<=9;v++)for(int w=1;w<=9;w++) if(v!=w){
        int s=v+w; sup[s<10?0:s==10?1:2][v]|=1<<w;
    }
    for(int li=0;li<15;li++){
        string s; cin>>s;
        int band=li/5,k=li%5,r=band*3+k/2;
        if(k%2==0){ for(int t=0;t<6;t++){int c=(t/2)*3+t%2; cons.push_back({r*9+c,r*9+c+1,ty(s[t])});} }
        else { for(int c=0;c<9;c++) cons.push_back({r*9+c,(r+1)*9+c,ty(s[c])}); }
    }
    for(int i=0;i<9;i++){
        array<int,9> a,b,c;
        for(int j=0;j<9;j++){a[j]=i*9+j;b[j]=j*9+i;c[j]=(i/3*3+j/3)*9+(i%3*3+j%3);}
        units.push_back(a);units.push_back(b);units.push_back(c);
    }
    for(int i=0;i<81;i++)for(int j=0;j<81;j++) if(i!=j){
        int r1=i/9,c1=i%9,r2=j/9,c2=j%9;
        if(r1==r2||c1==c2||(r1/3==r2/3&&c1/3==c2/3)) peers[i].push_back(j);
    }
    St d; d.fill(1022);
    solve(d);
    for(int r=0;r<9;r++){ for(int c=0;c<9;c++) printf("%d%c",__builtin_ctz(d[r*9+c]),c==8?'\n':' '); }
}
