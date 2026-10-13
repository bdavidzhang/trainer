#include <bits/stdc++.h>
using namespace std;
typedef __int128 LL;
const long long MOD=998244353;
string S; int n;
LL best; bool has;
LL p10[40];
string toS(LL x){ string r; if(x==0) return "0"; while(x>0){r+=char('0'+(int)(x%10));x/=10;} reverse(r.begin(),r.end()); return r; }
LL idxOf(LL x,int L,int o){
    LL r=1;
    for(int l=1;l<L;l++) r+=9*p10[l-1]*l;
    r+=(x-p10[L-1])*L+o;
    return r;
}
void cand(LL x,int L,int o){ LL v=idxOf(x,L,o); if(!has||v<best){best=v;has=true;} }
void direct(LL x){
    string t=toS(x); int L=t.size(); LL y=x;
    while((int)t.size()<L+n){ y++; t+=toS(y); }
    for(int o=0;o<L;o++){
        bool ok=true;
        for(int i=0;i<n&&ok;i++) if(S[i]!='?'&&S[i]!=t[o+i]) ok=false;
        if(ok){cand(x,L,o);return;}
    }
}
int main(){
    p10[0]=1; for(int i=1;i<40;i++) p10[i]=p10[i-1]*10;
    int T; cin>>T;
    while(T--){
        cin>>S; n=S.size(); has=false;
        for(long long x=1;x<=20000;x++) direct(x);
        for(int L=3;L<=27;L++){
            for(int q=1;q<=10;q++) direct(p10[L]-q);
            for(int o=0;o<L;o++){
                int m=(o+n-1)/L;
                for(int d=0;d<10;d++){
                    bool cross=(d+m>=10);
                    int tlo=cross?0:-1, thi=cross?L-2:-1;
                    for(int t=tlo;t<=thi;t++){
                        int pv=cross?L-2-t:-1;
                        int mask[40];
                        for(int i=0;i<L-1;i++) mask[i]=1023;
                        mask[0]&=~1;
                        if(cross) mask[pv]&=511;
                        bool ok=true;
                        for(int i=0;i<n&&ok;i++){
                            if(S[i]=='?') continue;
                            int v=S[i]-'0'; int g=o+i,j=g/L,pos=g%L;
                            if(pos==L-1){ if((d+j)%10!=v) ok=false; continue; }
                            bool cr=(d+j>=10);
                            if(cross&&pos>pv){ if(v!=(cr?0:9)) ok=false; }
                            else if(cross&&pos==pv){ if(cr){ if(v==0) ok=false; else mask[pv]&=1<<(v-1);} else mask[pv]&=1<<v; }
                            else mask[pos]&=1<<v;
                        }
                        if(!ok) continue;
                        LL x=0;
                        for(int i=0;i<L-1&&ok;i++){
                            int dg;
                            if(cross&&i>pv) dg=9;
                            else { if(!mask[i]){ok=false;break;} dg=__builtin_ctz(mask[i]); }
                            x=x*10+dg;
                        }
                        if(!ok) continue;
                        x=x*10+d;
                        cand(x,L,o);
                    }
                }
            }
        }
        printf("%lld\n",(long long)(best%MOD));
    }
}
