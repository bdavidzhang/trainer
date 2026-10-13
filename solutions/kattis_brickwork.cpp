#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
typedef long long ll;
int n,w,W;
vector<u64> R,Bk,RR;
int main(){
    scanf("%d %d",&n,&w);
    vector<char> has(w+1,0);
    for(int i=0;i<n;i++){int b;scanf("%d",&b);has[b]=1;}
    if(has[w]){printf("possible\n1\n%d\n1\n%d\n",w,w);return 0;}
    W=(w>>6)+2;
    R.assign(W+1,0);Bk.assign(W+1,0);
    for(int b=1;b<=w;b++)if(has[b])Bk[b>>6]|=1ULL<<(b&63);
    R[0]=1;
    // unbounded knapsack reachability: R |= Bk << i for each reachable i (ascending)
    u64 lastmask=((w&63)==63)?~0ULL:((1ULL<<((w&63)+1))-1);
    int lastw=w>>6;
    for(int i=0;i<w;i++){
        if(!(R[i>>6]>>(i&63)&1))continue;
        int ws=i>>6,bs=i&63;
        int lim=lastw-ws; // source words 0..lim
        if(bs==0){for(int k=0;k<=lim;k++)R[k+ws]|=Bk[k];}
        else{
            u64 carry=0;
            for(int k=0;k<=lim;k++){u64 v=Bk[k];R[k+ws]|=(v<<bs)|carry;carry=v>>(64-bs);}
        }
        R[lastw]&=lastmask;
    }
    auto reach=[&](int v)->bool{return v>=0&&(R[v>>6]>>(v&63)&1);};
    // reconstruct a representation of t: repeatedly find the largest brick b with R[t-b],
    // by AND-ing the brick bitset with the reversed reachability bitset (RR[j]=R[w-j]) shifted.
    RR.assign(W+2,0);
    for(int v=0;v<=w;v++)if(R[v>>6]>>(v&63)&1){int j=w-v;RR[j>>6]|=1ULL<<(j&63);}
    auto recon=[&](int t)->vector<int>{
        vector<int> res;
        while(t>0){
            int sh=w-t;int ws=sh>>6,bs=sh&63;
            int found=-1;
            for(int k=t>>6;k>=0&&found<0;k--){
                u64 v=RR[k+ws]>>bs;
                if(bs)v|=RR[k+ws+1]<<(64-bs);
                v&=Bk[k];
                while(v){int hb=63-__builtin_clzll(v);int b=k*64+hb;if(b<=t){found=b;break;}v^=1ULL<<hb;}
            }
            res.push_back(found);t-=found;
        }
        return res;
    };
    if(!reach(w)){puts("impossible");return 0;}
    // case A: a usable brick a not dividing w. Take the max count p of a; rest X has no subset summing to a multiple of a.
    for(int a=1;a<w;a++){
        if(!has[a]||w%a==0||!reach(w-a))continue;
        int p=1;while(w-(ll)(p+1)*a>=0&&reach(w-(p+1)*a))p++;
        vector<int> X=recon(w-p*a);
        puts("possible");
        printf("%d\n",(int)X.size()+p);
        for(int i=0;i<p;i++)printf("%d ",a);
        for(int x:X)printf("%d ",x);
        puts("");
        printf("%d\n",(int)X.size()+p);
        for(int x:X)printf("%d ",x);
        for(int i=0;i<p;i++)printf("%d ",a);
        puts("");
        return 0;
    }
    // case B: every usable brick divides w
    vector<int> dv;for(int a=1;a<w;a++)if(has[a]&&w%a==0)dv.push_back(a);
    if(dv.size()<2){puts("impossible");return 0;}
    ll a=dv[0],b=dv[1];ll g=std::gcd(a,b);ll A=a/g,Bq=b/g;ll L=a*Bq;ll k=w/L;
    puts("possible");
    printf("%lld\n",w/b);for(ll i=0;i<w/b;i++)printf("%lld ",b);puts("");
    printf("%lld\n",Bq+(k-1)*A);
    for(ll i=0;i<Bq-1;i++)printf("%lld ",a);
    for(ll i=0;i<(k-1)*A;i++)printf("%lld ",b);
    printf("%lld\n",a);
}
