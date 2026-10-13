#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
struct Ob{ull id,t1,t2,x1,x2;};
int main(){
    int N,Q;
    if(scanf("%d %d",&N,&Q)!=2)return 0;
    vector<Ob> obs;
    unordered_map<ull,int> mp;
    char a[64],b[64],c[64],d[64],e[64];
    for(int i=0;i<N;i++){
        scanf("%63s %63s",a,b);
        ull id=strtoull(a,0,10);
        if(b[0]=='S'){
            scanf("%63s %63s %63s",c,d,e);
            Ob o;o.id=id;o.t1=strtoull(c,0,10);o.t2=o.t1;
            o.x1=strtoull(d,0,16);o.x2=o.x1+strtoull(e,0,10)-1;
            mp[id]=obs.size();obs.push_back(o);
        }else{
            scanf("%63s",c);
            obs[mp[id]].t2=strtoull(c,0,10);
        }
    }
    sort(obs.begin(),obs.end(),[](const Ob&p,const Ob&q){return p.id<q.id;});
    for(int i=0;i<Q;i++){
        scanf("%63s %63s %63s %63s %63s",a,b,c,d,e);
        ull t1=strtoull(b,0,10),t2=strtoull(c,0,10),x1=strtoull(d,0,16),x2=strtoull(e,0,16);
        int k=0;vector<ull> ids;
        for(auto&o:obs){
            if(o.t1<=t2&&o.t2>=t1&&o.x1<=x2&&o.x2>=x1){
                k++;if(ids.size()<20)ids.push_back(o.id);
            }
        }
        printf("%d",k);
        for(ull v:ids)printf(" %llu",v);
        puts("");
    }
}
