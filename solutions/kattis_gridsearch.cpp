#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
static const u64 MOD=(1ULL<<61)-1;
static inline u64 mul(u64 a,u64 b){unsigned __int128 t=(unsigned __int128)a*b;u64 lo=(u64)(t&MOD),hi=(u64)(t>>61);u64 r=lo+hi;if(r>=MOD)r-=MOD;return r;}
static inline u64 add(u64 a,u64 b){u64 r=a+b;if(r>=MOD)r-=MOD;return r;}
static inline u64 sub(u64 a,u64 b){return a>=b?a-b:a+MOD-b;}
static char buf[2100];
int main(){
    int rk,ck;scanf("%d %d",&rk,&ck);
    vector<string> K(rk);for(auto&s:K){scanf("%s",buf);s=buf;}
    int rh,ch;scanf("%d %d",&rh,&ch);
    vector<string> H(rh);for(auto&s:H){scanf("%s",buf);s=buf;}
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()^0x9e3779b97f4a7c15ULL);
    u64 B1=rng()%(MOD-1000)+500,B2=rng()%(MOD-1000)+500;
    u64 p1=1;for(int i=0;i<ck;i++)p1=mul(p1,B1);
    u64 p2=1;for(int i=0;i<rk;i++)p2=mul(p2,B2);
    // key hash
    u64 kh=0;
    for(int i=0;i<rk;i++){u64 h=0;for(int j=0;j<ck;j++)h=add(mul(h,B1),(u64)(unsigned char)K[i][j]+1);kh=add(mul(kh,B2),h);}
    int W=ch-ck+1,Hh=rh-rk+1;
    vector<u64> R((size_t)rh*W);
    for(int i=0;i<rh;i++){u64 h=0;const string&s=H[i];
        for(int j=0;j<ch;j++){h=add(mul(h,B1),(u64)(unsigned char)s[j]+1);
            if(j>=ck)h=sub(h,mul(p1,(u64)(unsigned char)s[j-ck]+1));
            if(j>=ck-1)R[(size_t)i*W+(j-ck+1)]=h;}}
    vector<int> D((size_t)(rh+1)*(ch+1),0);
    vector<u64> col(W,0);
    for(int i=0;i<rh;i++){
        for(int j=0;j<W;j++){u64 h=add(mul(col[j],B2),R[(size_t)i*W+j]);
            if(i>=rk)h=sub(h,mul(p2,R[(size_t)(i-rk)*W+j]));
            col[j]=h;
            if(i>=rk-1&&h==kh){int r0=i-rk+1;
                D[(size_t)r0*(ch+1)+j]++;D[(size_t)r0*(ch+1)+j+ck]--;D[(size_t)(r0+rk)*(ch+1)+j]--;D[(size_t)(r0+rk)*(ch+1)+j+ck]++;}}
    }
    (void)Hh;
    string out;out.reserve((size_t)rh*(ch+1));
    vector<int> prev(ch+1,0),cur(ch+1,0);
    for(int i=0;i<rh;i++){int run=0;
        for(int j=0;j<ch;j++){run+=D[(size_t)i*(ch+1)+j];cur[j]=prev[j]+run;out+=cur[j]>0?H[i][j]:'.';}
        swap(prev,cur);out+='\n';}
    fputs(out.c_str(),stdout);
}
