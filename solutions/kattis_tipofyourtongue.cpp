#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
static const u64 MOD=(1ULL<<61)-1;
static u64 mulm(u64 a,u64 b){__uint128_t t=(__uint128_t)a*b;u64 r=(u64)(t&MOD)+(u64)(t>>61);if(r>=MOD)r-=MOD;return r;}
static u64 mix(u64 x){x+=0x9e3779b97f4a7c15ULL;x=(x^(x>>30))*0xbf58476d1ce4e5b9ULL;x=(x^(x>>27))*0x94d049bb133111ebULL;return x^(x>>31);}
int main(){
    int n,q;if(scanf("%d %d",&n,&q)!=2)return 0;
    const u64 B=911382323ULL*1000003ULL%MOD;
    vector<u64> P,S,PS;
    static char buf[1000005],op[8],b2[1000005];
    vector<u64> pw(1000002);pw[0]=1;for(size_t i=1;i<pw.size();i++)pw[i]=mulm(pw[i-1],B);
    vector<u64> pre;
    for(int i=0;i<n;i++){
        scanf("%s",buf);int L=strlen(buf);
        pre.assign(L+1,0);
        for(int j=0;j<L;j++){pre[j+1]=mulm(pre[j],B)+(buf[j]-'a'+1);if(pre[j+1]>=MOD)pre[j+1]-=MOD;}
        for(int len=1;len<=L;len++){
            u64 ph=pre[len];
            u64 sh=pre[L]+MOD-mulm(pre[L-len],pw[len]);if(sh>=MOD)sh-=MOD;
            ph=mix(ph^((u64)len<<52)*3);sh=mix(sh+((u64)len*0x1234567ULL));
            P.push_back(ph);S.push_back(sh);PS.push_back(mix(ph)^(sh*0x9e3779b97f4a7c15ULL));
        }
    }
    sort(P.begin(),P.end());sort(S.begin(),S.end());sort(PS.begin(),PS.end());
    auto cnt=[](vector<u64>&v,u64 x){auto r=equal_range(v.begin(),v.end(),x);return (long long)(r.second-r.first);};
    for(int i=0;i<q;i++){
        scanf("%s %s %s",op,buf,b2);int L=strlen(buf);
        u64 ph=0,sh=0;
        for(int j=0;j<L;j++){ph=mulm(ph,B)+(buf[j]-'a'+1);if(ph>=MOD)ph-=MOD;sh=mulm(sh,B)+(b2[j]-'a'+1);if(sh>=MOD)sh-=MOD;}
        ph=mix(ph^((u64)L<<52)*3);sh=mix(sh+((u64)L*0x1234567ULL));
        long long a=cnt(P,ph),b=cnt(S,sh),c=cnt(PS,mix(ph)^(sh*0x9e3779b97f4a7c15ULL));
        long long r=op[0]=='A'?c:op[0]=='O'?a+b-c:a+b-2*c;
        printf("%lld\n",r);
    }
}
