#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
static inline u64 mix(u64 x){x+=0x9e3779b97f4a7c15ULL;x=(x^(x>>30))*0xbf58476d1ce4e5b9ULL;x=(x^(x>>27))*0x94d049bb133111ebULL;return x^(x>>31);}
static vector<char> buf; static size_t pos=0;
static inline void skipws(){ while(pos<buf.size()&&(unsigned char)buf[pos]<=' ')pos++; }
static int readInt(){ skipws(); int x=0; while(pos<buf.size()&&buf[pos]>='0'&&buf[pos]<='9'){x=x*10+(buf[pos]-'0');pos++;} return x; }
// reads a token; returns true if it is a variable (single letter) and sets ch, otherwise sets hash
static inline bool readTok(int&ch,u64&h){
    skipws(); size_t s=pos; u64 a=1469598103934665603ULL;
    while(pos<buf.size()&&(unsigned char)buf[pos]>' '){ a=(a^(unsigned char)buf[pos])*1099511628211ULL; pos++; }
    if(pos-s==1&&isalpha((unsigned char)buf[s])){ch=(unsigned char)buf[s];return true;}
    h=mix(a^((u64)(pos-s)<<40)); return false;
}
static u64 distCode[2001];
int main(){
    { size_t cap=1<<20,len=0; buf.resize(cap); size_t r;
      while((r=fread(buf.data()+len,1,cap-len,stdin))>0){ len+=r; if(len==cap){cap*=2;buf.resize(cap);} }
      buf.resize(len); }
    for(int d=0;d<=2000;d++) distCode[d]=mix(0xABCDEF0000ULL+d);
    int n=readInt();
    // parameterized encoding: a variable is replaced by the distance to its previous occurrence inside the window (0 if none)
    vector<int> prv(n,-1); vector<u64> th(n,0); vector<char> var(n,0);
    { int last[128]; fill(last,last+128,-1);
      for(int i=0;i<n;i++){ int ch=0; u64 h=0; if(readTok(ch,h)){var[i]=1;prv[i]=last[ch];last[ch]=i;} else th[i]=h; } }
    vector<u64> all; all.reserve((size_t)n*(n+1)/2);
    for(int i=0;i<n;i++){
        u64 h=0x51ed270b0badc0deULL;
        for(int j=i;j<n;j++){
            u64 v = var[j] ? distCode[prv[j]>=i ? j-prv[j] : 0] : th[j];
            h=mix(h^v)+v*3;
            all.push_back(h);
        }
    }
    sort(all.begin(),all.end());
    int q=readInt(); string out;
    while(q--){
        int m=readInt(); int last[128]; fill(last,last+128,-1);
        u64 h=0x51ed270b0badc0deULL;
        for(int j=0;j<m;j++){
            int ch=0; u64 v=0;
            if(readTok(ch,v)){ int p=last[ch]; last[ch]=j; v=distCode[p>=0?j-p:0]; }
            h=mix(h^v)+v*3;
        }
        bool ok = m<=n && binary_search(all.begin(),all.end(),h);
        out += ok?"yes\n":"no\n";
    }
    fputs(out.c_str(),stdout);
}
