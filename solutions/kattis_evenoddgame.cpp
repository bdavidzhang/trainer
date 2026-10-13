#include <bits/stdc++.h>
using namespace std;
// Card types by parity effect: 0 = no-op (+even, *odd), 1 = flip (+odd), 2 = zero (*even).
int A,F,Z;
vector<unsigned char> R; // final parity under optimal play
inline size_t idx(int a,int f,int z,int par,int t){return ((((size_t)a*(F+1)+f)*(Z+1)+z)*2+par)*2+t;}
int main(){
    int n; scanf("%d",&n);
    vector<pair<char,long long>> pool[3];
    auto typ=[](char o,long long x){ if(o=='+') return (x&1)?1:0; return (x&1)?0:2; };
    for(int i=0;i<n;i++){ char o[4]; long long x; scanf("%3s %lld",o,&x); pool[typ(o[0],x)].push_back({o[0],x}); }
    long long x0; scanf("%lld",&x0); int par=x0&1;
    A=pool[0].size();F=pool[1].size();Z=pool[2].size();
    R.assign((size_t)(A+1)*(F+1)*(Z+1)*4,0);
    for(int a=0;a<=A;a++)for(int f=0;f<=F;f++)for(int z=0;z<=Z;z++)for(int p=0;p<2;p++)for(int t=0;t<2;t++){
        if(a+f+z==0){R[idx(a,f,z,p,t)]=p;continue;}
        bool any1=false,any0=false;
        auto take=[&](int v){ if(v)any1=true; else any0=true; };
        if(a) take(R[idx(a-1,f,z,p,1-t)]);
        if(f) take(R[idx(a,f-1,z,p^1,1-t)]);
        if(z) take(R[idx(a,f,z-1,0,1-t)]);
        R[idx(a,f,z,p,t)] = t ? any1 : !any0;
    }
    int cnt[3]={A,F,Z};
    int g; bool myTurn;
    if(R[idx(A,F,Z,par,1)]==1){ puts("me"); g=1; myTurn=true; }
    else { puts("you"); g=0; myTurn=false; }
    fflush(stdout);
    int rem=n;
    auto apply=[&](int ty){ cnt[ty]--; if(ty==1)par^=1; else if(ty==2)par=0; };
    while(rem>0){
        if(myTurn){
            int pick=-1;
            for(int ty=0;ty<3&&pick<0;ty++){
                if(!cnt[ty])continue;
                int c2[3]={cnt[0],cnt[1],cnt[2]}; c2[ty]--;
                int p2= ty==1?par^1:(ty==2?0:par);
                if(R[idx(c2[0],c2[1],c2[2],p2,1-g)]==g) pick=ty;
            }
            if(pick<0){ for(int ty=0;ty<3;ty++) if(cnt[ty]){pick=ty;break;} } // should not happen
            auto c=pool[pick].back(); pool[pick].pop_back();
            printf("%c %lld\n",c.first,c.second); fflush(stdout);
            apply(pick);
        } else {
            char o[4]; long long x; if(scanf("%3s %lld",o,&x)!=2) return 0;
            int ty=typ(o[0],x);
            // remove that exact card from the pool
            auto&v=pool[ty];
            for(size_t i=0;i<v.size();i++) if(v[i].first==o[0]&&v[i].second==x){v[i]=v.back();v.pop_back();break;}
            apply(ty);
        }
        myTurn=!myTurn; rem--;
    }
    return 0;
}
