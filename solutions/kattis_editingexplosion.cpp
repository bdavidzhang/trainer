#include <bits/stdc++.h>
using namespace std;
const long long MOD=998244353;
int main(){
    string s; int d; cin>>s>>d;
    int m=s.size(), cap=d+1;
    string distinct=s; sort(distinct.begin(),distinct.end());
    distinct.erase(unique(distinct.begin(),distinct.end()),distinct.end());
    int others=26-distinct.size();
    auto enc=[&](const int*r){unsigned long long k=0;for(int j=0;j<=m;j++)k|=(unsigned long long)r[j]<<(4*j);return k;};
    unordered_map<unsigned long long,long long> cur,nxt;
    int r[12],nr[12];
    for(int j=0;j<=m;j++) r[j]=min(j,cap);
    cur[enc(r)]=1;
    long long ans=0;
    while(!cur.empty()){
        nxt.clear();
        for(auto&kv:cur){
            for(int j=0;j<=m;j++) r[j]=(kv.first>>(4*j))&15;
            if(r[m]==d) ans=(ans+kv.second)%MOD;
            for(int ci=0;ci<=(int)distinct.size();ci++){
                long long w; char c;
                if(ci<(int)distinct.size()){w=1;c=distinct[ci];} else {w=others;c='#';}
                if(w==0) continue;
                nr[0]=min(r[0]+1,cap);
                int mn=nr[0];
                for(int j=1;j<=m;j++){
                    nr[j]=min(min(r[j]+1,nr[j-1]+1),r[j-1]+(s[j-1]!=c));
                    if(nr[j]>cap) nr[j]=cap;
                    mn=min(mn,nr[j]);
                }
                if(mn>d) continue;
                long long &t=nxt[enc(nr)];
                t=(t+kv.second*w)%MOD;
            }
        }
        cur.swap(nxt);
    }
    printf("%lld\n",ans%MOD);
}
