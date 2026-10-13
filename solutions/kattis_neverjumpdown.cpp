#include <bits/stdc++.h>
using namespace std;
static const int MOD=11092019;
static const int SZ=1<<20;
static int tl[2*SZ], tc[2*SZ]; // max length, count
static char buf[1<<25];
static size_t bl=0,bp=0;
static inline int gc(){ if(bp==bl){bl=fread(buf,1,sizeof(buf),stdin);bp=0;if(!bl)return -1;} return buf[bp++]; }
static inline int rd(){int c=gc();while(c!='-'&&(c<'0'||c>'9'))c=gc();int x=0;while(c>='0'&&c<='9'){x=x*10+c-'0';c=gc();}return x;}
static inline void setleaf(int pos,int l,int c){
    int i=pos+SZ; tl[i]=l;tc[i]=c;
    for(i>>=1;i;i>>=1){
        int a=2*i,b=2*i+1;
        if(tl[a]>tl[b]){tl[i]=tl[a];tc[i]=tc[a];}
        else if(tl[a]<tl[b]){tl[i]=tl[b];tc[i]=tc[b];}
        else {tl[i]=tl[a]; int s=tc[a]+tc[b]; if(s>=MOD)s-=MOD; tc[i]=s;}
    }
}
static inline void query(int r,int&L,int&Cn){ // [0,r]
    L=0;Cn=0;
    int lo=SZ, hi=r+SZ+1;
    auto add=[&](int i){ if(tl[i]>L){L=tl[i];Cn=tc[i];} else if(tl[i]==L&&L>0){Cn+=tc[i]; if(Cn>=MOD)Cn-=MOD;} };
    for(;lo<hi;lo>>=1,hi>>=1){ if(lo&1)add(lo++); if(hi&1)add(--hi); }
}
int main(){
    int n=rd();
    vector<int> u(n+1),head(n+1,0),nxt(n+1,0);
    for(int i=1;i<=n;i++)u[i]=rd();
    for(int i=2;i<=n;i++){int p=rd(); nxt[i]=head[p]; head[p]=i;}
    vector<int> stk, ol(n+1), oc(n+1); vector<char> state(n+1,0);
    stk.reserve(n); stk.push_back(1);
    int bestL=0; long long bestC=0;
    while(!stk.empty()){
        int v=stk.back();
        if(!state[v]){
            state[v]=1;
            int L,Cn; query(u[v],L,Cn);
            if(L==0){L=1;Cn=1;} else L++;
            if(L>bestL){bestL=L;bestC=Cn;} else if(L==bestL){bestC=(bestC+Cn)%MOD;}
            ol[v]=tl[u[v]+SZ]; oc[v]=tc[u[v]+SZ];
            setleaf(u[v],L,Cn);
            for(int ch=head[v];ch;ch=nxt[ch]) stk.push_back(ch);
        } else {
            stk.pop_back();
            setleaf(u[v],ol[v],oc[v]);
        }
    }
    printf("%d %lld\n",bestL,bestC%MOD);
}
