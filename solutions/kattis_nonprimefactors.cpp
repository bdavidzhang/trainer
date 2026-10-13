#include <bits/stdc++.h>
using namespace std;
const int MX=2000001;
static int spf[MX], dv[MX], om[MX], ex[MX];
static char buf[1<<25];
int main(){
    vector<int> pr;
    dv[1]=1;
    for(int i=2;i<MX;i++){
        if(!spf[i]){spf[i]=i;pr.push_back(i);dv[i]=2;om[i]=1;ex[i]=1;}
        for(int p:pr){
            long long x=(long long)p*i; if(x>=MX||p>spf[i]) break;
            spf[x]=p;
            if(p==spf[i]){ex[x]=ex[i]+1;dv[x]=dv[i]/(ex[i]+1)*(ex[x]+1);om[x]=om[i];}
            else{ex[x]=1;dv[x]=dv[i]*2;om[x]=om[i]+1;}
        }
    }
    // fast input
    size_t len=0; string in; 
    {
        size_t cap=1<<26; in.resize(cap);
        size_t r;
        while((r=fread(&in[len],1,cap-len,stdin))>0){len+=r; if(len==cap){cap*=2;in.resize(cap);}}
        in.resize(len);
    }
    size_t p=0;
    auto rd=[&]()->int{
        while(p<len&&(in[p]<'0'||in[p]>'9'))p++;
        int x=0; while(p<len&&in[p]>='0'&&in[p]<='9'){x=x*10+in[p]-'0';p++;}
        return x;
    };
    int q=rd();
    string out; out.reserve((size_t)q*5+16);
    while(q--){
        int x=rd(); int v=dv[x]-om[x];
        char t[12]; int n=0; if(v==0)t[n++]='0'; while(v){t[n++]='0'+v%10;v/=10;}
        while(n)out.push_back(t[--n]);
        out.push_back('\n');
    }
    fwrite(out.data(),1,out.size(),stdout);
}
