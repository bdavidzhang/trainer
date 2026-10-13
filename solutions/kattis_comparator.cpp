#include <bits/stdc++.h>
using namespace std;
typedef bitset<1024> B;
static char buf[1100000];
int prec(char c){ if(c=='=')return 3; if(c=='&')return 2; if(c=='|')return 1; return 0; }
int apply(char op,int a,int b){
    if(op=='=') return (~(a^b))&15; if(op=='&') return a&b; if(op=='|') return a|b; return a^b;
}
int parse(const char*e){
    vector<int> vals; vector<char> ops;
    auto afterVal=[&](){ while(!ops.empty()&&ops.back()=='!'){ops.pop_back(); vals.back()=(~vals.back())&15;} };
    auto red=[&](){ char op=ops.back(); ops.pop_back(); int b=vals.back(); vals.pop_back(); int a=vals.back(); vals.back()=apply(op,a,b); };
    for(const char*p=e;*p;p++){
        char c=*p;
        if(c=='x'){vals.push_back(12);afterVal();}
        else if(c=='y'){vals.push_back(10);afterVal();}
        else if(c=='0'){vals.push_back(0);afterVal();}
        else if(c=='1'){vals.push_back(15);afterVal();}
        else if(c=='('||c=='!') ops.push_back(c);
        else if(c==')'){ while(ops.back()!='(') red(); ops.pop_back(); afterVal(); }
        else { while(!ops.empty()&&ops.back()!='('&&ops.back()!='!'&&prec(ops.back())>=prec(c)) red(); ops.push_back(c); }
    }
    while(!ops.empty()) red();
    return vals.back();
}
int main(){
    int n,k; scanf("%d %d",&n,&k);
    int M=1<<k;
    static B und[1024],f[1024],mb[10][2];
    for(int u=0;u<M;u++) for(int v=0;v<M;v++) und[u][v]=1;
    for(int b=0;b<k;b++) for(int v=0;v<M;v++) mb[b][(v>>b)&1][v]=1;
    static bool seen[10][10][4];
    for(int i=0;i<n;i++){
        int a,b,r; scanf("%d %d %s %d",&a,&b,buf,&r); a--;b--;
        int tt=parse(buf);
        for(int xy=0;xy<4;xy++) if((tt>>xy&1)&&!seen[a][b][xy]){
            seen[a][b][xy]=true; int x=xy>>1,y=xy&1;
            for(int u=0;u<M;u++) if(((u>>a)&1)==x){
                B rw=und[u]&mb[b][y];
                if(r) f[u]|=rw;
                und[u]&=~rw;
            }
        }
    }
    int r; scanf("%d",&r);
    if(r) for(int u=0;u<M;u++) f[u]|=und[u];
    long long c1=0,c2=0,c3=0;
    for(int u=0;u<M;u++) if(f[u][u]) c1++;
    for(int u=0;u<M;u++) for(int v=0;v<M;v++) if(f[u][v]&&f[v][u]) c2++;
    for(int u=0;u<M;u++) for(int v=0;v<M;v++) if(f[u][v]) c3+=(f[v]&~f[u]).count();
    printf("%lld %lld %lld\n",c1,c2,c3);
}
