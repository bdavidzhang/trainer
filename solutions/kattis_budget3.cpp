#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef __int128 LL;
static char *buf; static size_t pos=0,len=0;
static inline void skipws(){ while(pos<len&&(buf[pos]==' '||buf[pos]=='\n'||buf[pos]=='\r'||buf[pos]=='\t')) pos++; }
// reads a non-negative decimal as integer count of 1e-6 units
static ll readMicro(){
    skipws(); bool neg=false; if(pos<len&&(buf[pos]=='-'||buf[pos]=='+')){neg=buf[pos]=='-';pos++;}
    ll ip=0; while(pos<len&&isdigit((unsigned char)buf[pos])) ip=ip*10+(buf[pos++]-'0');
    ll fp=0; int nd=0;
    if(pos<len&&buf[pos]=='.'){ pos++; while(pos<len&&isdigit((unsigned char)buf[pos])){ if(nd<6){fp=fp*10+(buf[pos]-'0');nd++;} pos++; } }
    while(nd<6){fp*=10;nd++;}
    ll r=ip*1000000+fp;
    if(pos<len&&(buf[pos]=='e'||buf[pos]=='E')){ // unlikely exponent form
        pos++; bool en=false; if(buf[pos]=='-'||buf[pos]=='+'){en=buf[pos]=='-';pos++;}
        int ex=0; while(pos<len&&isdigit((unsigned char)buf[pos])) ex=ex*10+(buf[pos++]-'0');
        double v=(double)r*pow(10.0,en?-ex:ex); r=llround(v);
    }
    return neg?-r:r;
}
static ll readInt(){ skipws(); ll v=0; while(pos<len&&isdigit((unsigned char)buf[pos])) v=v*10+(buf[pos++]-'0'); return v; }
int main(){
    {   size_t cap=1<<26; buf=(char*)malloc(cap);
        size_t r; while((r=fread(buf+len,1,cap-len,stdin))>0){ len+=r; if(len==cap){cap*=2;buf=(char*)realloc(buf,cap);} } }
    int n=readInt();
    vector<ll> sx(n+1,0),sy(n+1,0); vector<LL> sxx(n+1,0),sxy(n+1,0);
    for(int i=1;i<=n;i++){ ll x=readMicro(),y=readMicro();
        sx[i]=sx[i-1]+x; sy[i]=sy[i-1]+y; sxx[i]=sxx[i-1]+(LL)x*x; sxy[i]=sxy[i-1]+(LL)x*y; }
    int m=readInt(); string out; out.reserve((size_t)m*24); char tmp[64];
    const LL M6=1000000;
    while(m--){
        int l=readInt(),r=readInt(); ll lam=readMicro(), X=readMicro();
        LL cnt=r-l+1, SX=sx[r]-sx[l-1], SY=sy[r]-sy[l-1], SXX=sxx[r]-sxx[l-1], SXY=sxy[r]-sxy[l-1];
        // all three share a 1e-18 scale
        LL det=(SXX+(LL)lam*M6)*(cnt*M6+lam)-SX*SX*M6;
        long double res;
        if(det==0){
            // lambda=0 and all x equal: take the minimum-norm fit (limit lambda->0)
            long double x0=(long double)SX/(long double)cnt/1e6L, yb=(long double)SY/(long double)cnt/1e6L;
            long double xq=(long double)X/1e6L;
            res=yb*(x0*xq+1)/(x0*x0+1);
        } else {
            LL Kn=SXY*(cnt*M6+lam)-SX*SY*M6;
            LL Bn=(SXX+(LL)lam*M6)*SY-SX*SXY;
            res=((long double)Kn*((long double)X/1e6L)+(long double)Bn)/(long double)det;
        }
        int k=snprintf(tmp,sizeof tmp,"%.10Lf\n",res); out.append(tmp,k);
    }
    fwrite(out.data(),1,out.size(),stdout);
}
